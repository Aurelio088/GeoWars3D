#pragma once

#include <Graphics/DirectX.h>

class Triangle
{
public:
    Triangle() = default;
    Triangle(ID3D11Device* device);

    void Create(ID3D11Device* device);
    void Draw(ID3D11DeviceContext* context) const;

private:
    ComPtr<ID3D11Buffer> vertexBuffer;
};