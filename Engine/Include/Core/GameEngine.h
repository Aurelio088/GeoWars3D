#pragma once

#include <Graphics/Renderer.h>
#include <Graphics/Triangle.h>
#include <System/EntryPoint.h>
#include <System/Window.h>

class GameEngine
{
public:
    void Run();

private:
    virtual void Initialize() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;

protected:
    Renderer renderer;
    Window window;
};