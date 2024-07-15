#pragma once

#include <System/Win32.h>

#include <wrl/client.h>
#include <d3d11.h>

#include <DirectXMath.h>
#include <DirectXColors.h>

#include <exception>

using Microsoft::WRL::ComPtr;
using namespace DirectX;

inline void ThrowIfFailed(HRESULT hResult)
{
    if (FAILED(hResult))
        throw std::exception();
}