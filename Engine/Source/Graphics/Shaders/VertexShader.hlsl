cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
}

struct VS_INPUT
{
    float4 Position : POSITION;
    float4 Color    : COLOR;
};

struct VS_OUTPUT
{
    float4 Color    : COLOR;
    float4 Position : SV_Position;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    output.Color = input.Color;
    
    return output;
}