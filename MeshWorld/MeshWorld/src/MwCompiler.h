//*********************************************************
// MeshWorld\MeshWorld\src\MwCompiler.h
//
// Copyright (c) Fabio Kong. All rights reserved.
//
// This file contains declarations of helper functions for compiling HLSL shaders.
//
//*********************************************************

#include <string>
#include <windows.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

bool CompileShaderFromFile(const std::wstring& filename, const std::string& entryPoint, const std::string& target, ComPtr<ID3DBlob>& shaderBlob);