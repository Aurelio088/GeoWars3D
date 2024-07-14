#pragma once

#include <Graphics/Triangle.h>
#include <Core/GameEngine.h>

class GeoWars3D : public GameEngine
{
private:
    void Initialize() override;
    void Update() override;
    void Draw() override;

private:
    Triangle triangle;
};