#pragma once

#include <Graphics/Renderer.h>
#include <Graphics/Triangle.h>
#include <System/Window.h>

class GameEngine
{
public:
    void Run();

private:
    Triangle triangle;

    Renderer renderer;
    Window window;
};