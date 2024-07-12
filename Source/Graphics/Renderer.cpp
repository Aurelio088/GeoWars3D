#include <Graphics/Renderer.h>

#include <Shaders/VertexShader.h>
#include <Shaders/PixelShader.h>

Renderer::Renderer(int width, int height, HWND windowHandle)
{
    Initialize(width, height, windowHandle);
}

void Renderer::Initialize(int width, int height, HWND windowHandle)
{
    UINT flags = 0;
#ifdef _DEBUG
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 1;
    swapChainDesc.OutputWindow = windowHandle;
    swapChainDesc.Windowed = TRUE;

    ThrowIfFailed(D3D11CreateDeviceAndSwapChain(nullptr,
                                                D3D_DRIVER_TYPE_HARDWARE,
                                                nullptr,
                                                flags,
                                                featureLevels,
                                                ARRAYSIZE(featureLevels),
                                                D3D11_SDK_VERSION,
                                                &swapChainDesc,
                                                &swapChain,
                                                &device,
                                                &featureLevel,
                                                &immediateContext));

    ComPtr<IDXGIFactory1> factory1;
    ThrowIfFailed(swapChain->GetParent(IID_PPV_ARGS(&factory1)));

    ThrowIfFailed(factory1->MakeWindowAssociation(
        windowHandle, DXGI_MWA_NO_ALT_ENTER));

    ComPtr<ID3D11Texture2D> backBuffer;
    ThrowIfFailed(swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer)));

    ThrowIfFailed(device->CreateRenderTargetView(
        backBuffer.Get(), nullptr, &renderTargetView));

    ThrowIfFailed(device->CreateVertexShader(VSCode,
                                             sizeof(VSCode),
                                             nullptr,
                                             &vertexShader));

    ThrowIfFailed(device->CreatePixelShader(PSCode,
                                            sizeof(PSCode),
                                            nullptr,
                                            &pixelShader));

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {
            "POSITION",
            0,
            DXGI_FORMAT_R32G32B32_FLOAT,
            0,
            0,
            D3D11_INPUT_PER_VERTEX_DATA,
            0,
        },
        {
            "COLOR",
            0,
            DXGI_FORMAT_R32G32B32A32_FLOAT,
            0,
            12,
            D3D11_INPUT_PER_VERTEX_DATA,
            0,
        },
    };

    ThrowIfFailed(device->CreateInputLayout(layout,
                                            ARRAYSIZE(layout),
                                            VSCode,
                                            sizeof(VSCode),
                                            &inputLayout));

    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.ByteWidth = sizeof(shaderConstants);
    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    D3D11_SUBRESOURCE_DATA data = {};
    data.pSysMem = &shaderConstants;

    ThrowIfFailed(device->CreateBuffer(&bufferDesc, &data, &constantBuffer));

    immediateContext->IASetInputLayout(inputLayout.Get());

    immediateContext->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    immediateContext->VSSetShader(vertexShader.Get(), nullptr, 0);

    immediateContext->VSSetConstantBuffers(
        0, 1, constantBuffer.GetAddressOf());

    immediateContext->PSSetShader(pixelShader.Get(), nullptr, 0);

    D3D11_VIEWPORT viewport = {};
    viewport.Width = static_cast<FLOAT>(width);
    viewport.Height = static_cast<FLOAT>(height);
    viewport.MaxDepth = D3D11_MAX_DEPTH;

    immediateContext->RSSetViewports(1, &viewport);

    immediateContext->OMSetRenderTargets(
        1, renderTargetView.GetAddressOf(), nullptr);
}

void Renderer::Clear()
{
    immediateContext->ClearRenderTargetView(
        renderTargetView.Get(), DirectX::Colors::CornflowerBlue);
}

void Renderer::Display()
{
    swapChain->Present(1, 0);
}

void Renderer::SetWorld(const XMMATRIX& world)
{
    shaderConstants.world = XMMatrixTranspose(world);
}

void Renderer::SetView(const XMMATRIX& view)
{
    shaderConstants.view = XMMatrixTranspose(view);
}

void Renderer::SetProjection(const XMMATRIX& projection)
{
    shaderConstants.projection = XMMatrixTranspose(projection);
}

void Renderer::Draw(const Triangle& triangle)
{
    immediateContext->UpdateSubresource(
        constantBuffer.Get(), 0, nullptr, &shaderConstants, 0, 0);

    triangle.Draw(immediateContext.Get());
}

ID3D11Device* Renderer::GetDevice() const
{
    return device.Get();
}

ID3D11DeviceContext* Renderer::GetContext() const
{
    return immediateContext.Get();
}