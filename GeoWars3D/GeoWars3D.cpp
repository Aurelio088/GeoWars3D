#include "GeoWars3D.h"

void GeoWars3D::Initialize()
{
    triangle.Create(renderer.GetDevice());
}

void GeoWars3D::Update()
{

}

void GeoWars3D::Draw()
{
    renderer.Draw(triangle);
}