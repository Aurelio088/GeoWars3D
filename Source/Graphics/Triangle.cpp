#include <Graphics/Triangle.h>

Triangle::Triangle(ID3D11Device* device)
{
    Create(device);
}

void Triangle::Create(ID3D11Device* device)
{
    float vertices[] =
    {
         0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    };

    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.ByteWidth = sizeof(vertices);
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA data = {};
    data.pSysMem = vertices;

    ThrowIfFailed(device->CreateBuffer(&bufferDesc, &data, &vertexBuffer));
}

void Triangle::Draw(ID3D11DeviceContext* context) const
{
    UINT stride = sizeof(float) * 7;
    UINT offset = 0;

    context->IASetVertexBuffers(
        0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

    context->Draw(3, 0);
}