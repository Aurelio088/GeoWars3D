#pragma once

#include <Graphics/DirectX.h>
#include <Graphics/Triangle.h>
#include <System/Win32.h>

class Renderer
{
public:
    Renderer() = default;
    Renderer(int width, int height, HWND windowHandle);

    void Initialize(int width, int height, HWND windowHandle);

    void Clear();
    void Display();

    void SetWorld(const XMMATRIX& world);
    void SetView(const XMMATRIX& view);
    void SetProjection(const XMMATRIX& projection);

    void Draw(const Triangle& triangle);

    ID3D11Device* GetDevice() const;
    ID3D11DeviceContext* GetContext() const;

private:
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;

private:
    struct ShaderConstants
    {
        XMMATRIX world      = XMMatrixIdentity();
        XMMATRIX view       = XMMatrixIdentity();
        XMMATRIX projection = XMMatrixIdentity();
    };

    D3D_FEATURE_LEVEL              featureLevel;

    ComPtr<ID3D11Device>           device;
    ComPtr<ID3D11DeviceContext>    immediateContext;
    ComPtr<IDXGISwapChain>         swapChain;
    ComPtr<ID3D11RenderTargetView> renderTargetView;

    ComPtr<ID3D11VertexShader>     vertexShader;
    ComPtr<ID3D11PixelShader>      pixelShader;
    ComPtr<ID3D11InputLayout>      inputLayout;
    ComPtr<ID3D11Buffer>           constantBuffer;

    ShaderConstants                shaderConstants;
};