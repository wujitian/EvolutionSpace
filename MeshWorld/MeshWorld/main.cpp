#include <windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxcapi.h>
#include <DirectXMath.h>
#include <wrl.h>
#include "d3dx12.h"
#include <d3dcompiler.h>


using namespace Microsoft::WRL;
using namespace DirectX;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    // Window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "DX12WindowClass";
    RegisterClass(&wc);

    // Create window
    HWND hwnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        "DirectX 12 Mesh Shader",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    ShowWindow(hwnd, nCmdShow);

    // Enable the D3D12 debug layer
    ComPtr<ID3D12Debug> debugController;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
    {
        debugController->EnableDebugLayer();
    }

    /*
    // Enable the DXGI debug layer
    ComPtr<IDXGIInfoQueue> dxgiInfoQueue;
    if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiInfoQueue))))
    {
        dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_SEVERITY_ERROR);
    }
    */
    
    // Initialize DirectX 12
    ComPtr<ID3D12Device> device;
    ComPtr<IDXGIFactory4> dxgiFactory;
    ComPtr<IDXGISwapChain3> swapChain;
    ComPtr<ID3D12CommandQueue> commandQueue;
    ComPtr<ID3D12DescriptorHeap> rtvHeap;
    ComPtr<ID3D12Resource> renderTargets[2];
    ComPtr<ID3D12CommandAllocator> commandAllocator;
    ComPtr<ID3D12GraphicsCommandList> commandList;
    UINT rtvDescriptorSize;
    UINT frameIndex;

    // Create DXGI factory
    CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));

    // Create device
    D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));

    // Create command queue
    D3D12_COMMAND_QUEUE_DESC cqDesc = {};
    cqDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    cqDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    device->CreateCommandQueue(&cqDesc, IID_PPV_ARGS(&commandQueue));

    // Create swap chain
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = 2;
    swapChainDesc.Width = 1280;
    swapChainDesc.Height = 720;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.SampleDesc.Count = 1;
    ComPtr<IDXGISwapChain1> swapChain1;
    dxgiFactory->CreateSwapChainForHwnd(
        commandQueue.Get(),
        hwnd,
        &swapChainDesc,
        nullptr,
        nullptr,
        &swapChain1
    );
    swapChain1.As(&swapChain);
    frameIndex = swapChain->GetCurrentBackBufferIndex();

    // Create RTV descriptor heap
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
    rtvHeapDesc.NumDescriptors = 2;
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
    rtvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    
    // Create frame resources
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvHeap->GetCPUDescriptorHandleForHeapStart());
    for (UINT n = 0; n < 2; n++) {
        swapChain->GetBuffer(n, IID_PPV_ARGS(&renderTargets[n]));
        device->CreateRenderTargetView(renderTargets[n].Get(), nullptr, rtvHandle);
        rtvHandle.Offset(1, rtvDescriptorSize);
    }

    // Create command allocator
    device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));

    // Create command list
    device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList));

    // Reset command list
    commandList->Close();

    // Create fence for synchronization
    ComPtr<ID3D12Fence> fence;
    UINT64 fenceValue = 0;
    device->CreateFence(fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
    HANDLE fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    // Pipeline setup
    ComPtr<ID3D12RootSignature> rootSignature;
    D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc;
    rootSignatureDesc.NumParameters = 0;
    rootSignatureDesc.pParameters = nullptr;
    rootSignatureDesc.NumStaticSamplers = 0;
    rootSignatureDesc.pStaticSamplers = nullptr;
    rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

    ComPtr<ID3DBlob> signature;
    ComPtr<ID3DBlob> error;
    D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
    device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&rootSignature));

    // Compile shaders
    ComPtr<ID3DBlob> vertexShader;
    ComPtr<ID3DBlob> pixelShader;
    ComPtr<ID3DBlob> vertexShaderByteCode;
    ComPtr<ID3DBlob> pixelShaderByteCode;
    
    // Try to compile the vertex shader and display the error message if it fails
    HRESULT hr = D3DCompileFromFile(L"triangle.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", 0, 0, &vertexShader, nullptr);
    if(FAILED(hr)) {
        // If the compilation fails, try to get the error message from the compiler
        ComPtr<ID3DBlob> errorMessage;
        D3DCompileFromFile(L"triangle.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &vertexShader, &errorMessage);

        // Display the error message in a message box
        MessageBoxA(nullptr, (char*)errorMessage->GetBufferPointer(), "Error", MB_OK);
        MessageBoxA(nullptr, "D3DCompileFromFile failed", "Error", MB_OK);
        return false;
    }

    hr = D3DCompileFromFile(L"triangle.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", 0, 0, &pixelShader, nullptr);
    if (FAILED(hr)) {
        // If the compilation fails, try to get the error message from the compiler
        ComPtr<ID3DBlob> errorMessage;
        D3DCompileFromFile(L"triangle.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &pixelShader, &errorMessage);

        // Display the error message in a message box
        MessageBoxA(nullptr, (char*)errorMessage->GetBufferPointer(), "Error", MB_OK);
        MessageBoxA(nullptr, "D3DCompileFromFile failed", "Error", MB_OK);
        return false;
    }

    // Define input layout
    D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    };

    // Describe and create the graphics pipeline state object (PSO)
    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
    psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
    psoDesc.pRootSignature = rootSignature.Get();
    psoDesc.VS = CD3DX12_SHADER_BYTECODE(vertexShader.Get());
    psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShader.Get());
    psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    psoDesc.DepthStencilState.DepthEnable = FALSE;
    psoDesc.DepthStencilState.StencilEnable = FALSE;
    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.SampleDesc.Count = 1;
    ComPtr<ID3D12PipelineState> pipelineState;
    device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pipelineState));

    // Create vertex buffer
    struct Vertex {
        XMFLOAT3 position;
    };
    Vertex triangleVertices[] =
    {
        { { 0.0f, 0.5f, 0.0f } },
        { { 0.25f, -0.43f, 0.0f } },
        { { -0.25f, -0.43f, 0.0f } },
    };

    const UINT vertexBufferSize = sizeof(triangleVertices);

    // Create vertex buffer resource
    ComPtr<ID3D12Resource> vertexBuffer;
    CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
    CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize);
    device->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&vertexBuffer));

    // Copy the triangle data to the vertex buffer
    UINT8* pVertexDataBegin;
    CD3DX12_RANGE readRange(0, 0);
    vertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin));
    memcpy(pVertexDataBegin, triangleVertices, sizeof(triangleVertices));
    vertexBuffer->Unmap(0, nullptr);

    // Initialize the vertex buffer view
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
    vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
    vertexBufferView.StrideInBytes = sizeof(Vertex);
    vertexBufferView.SizeInBytes = vertexBufferSize;

    // Render loop
    while (true) {
        MSG msg = {};
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT) {
                break;
            }
        }
        
        // Record command list
        // Should be moved inside the while loop to avoid unnecessary resetting of command list
        commandAllocator->Reset();
        commandList->Reset(commandAllocator.Get(), nullptr);

        // Set resource barrier
        CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
        commandList->ResourceBarrier(1, &barrier);

        // Set render target
        CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, rtvDescriptorSize);
        commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);
        commandList->SetGraphicsRootSignature(rootSignature.Get());
        
        // Set viewport and scissor
        CD3DX12_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(1280), static_cast<float>(720));
        CD3DX12_RECT scissorRect(0, 0, 1280, 720);
        commandList->RSSetViewports(1, &viewport);
        commandList->RSSetScissorRects(1, &scissorRect);

        // Bind pipeline
        commandList->SetPipelineState(pipelineState.Get());

        // Clear render target
        FLOAT clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
        commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

        // Draw triangle
        commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        commandList->IASetVertexBuffers(0, 1, &vertexBufferView);
        commandList->DrawInstanced(3, 1, 0, 0);

        // Execute command list
        barrier = CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
        commandList->ResourceBarrier(1, &barrier);

        commandList->Close();
        ID3D12CommandList* ppCommandLists[] = { commandList.Get() };
        commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

        // Present frame
        swapChain->Present(1, 0);

        frameIndex = swapChain->GetCurrentBackBufferIndex();

        // Wait for the frame
        const UINT64 currentFenceValue = fenceValue;
        commandQueue->Signal(fence.Get(), currentFenceValue);
        fenceValue++;

        if (fence->GetCompletedValue() < currentFenceValue)
        {
            fence->SetEventOnCompletion(currentFenceValue, fenceEvent);
            WaitForSingleObject(fenceEvent, INFINITE);
        }
    }

    // Clean up
    CloseHandle(fenceEvent);

    return 0;
}