#include "MwCompiler.h"

// Compile the HLSL shader from file and return the result in a blob
// If the compilation fails, display the error message in a message box
bool CompileShaderFromFile(const std::wstring& filename, const std::string& entryPoint, const std::string& target, ComPtr<ID3DBlob>& shaderBlob)
{
    HRESULT hr = D3DCompileFromFile(filename.c_str(), nullptr, nullptr, entryPoint.c_str(), target.c_str(), 0, 0, &shaderBlob, nullptr);
    if (FAILED(hr))
    {
        // If the compilation fails, try to get the error message from the compiler
        ComPtr<ID3DBlob> errorBlob;
        D3DCompileFromFile(filename.c_str(), nullptr, nullptr, entryPoint.c_str(), target.c_str(), D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &shaderBlob, &errorBlob);

        // Display the error message in a message box
        if (errorBlob)
        {
            MessageBoxA(nullptr, (char*)errorBlob->GetBufferPointer(), "Error", MB_OK);
        }
        MessageBoxA(nullptr, "D3DCompileFromFile failed", "Error", MB_OK);
        return false;
    }

    return true;
}
