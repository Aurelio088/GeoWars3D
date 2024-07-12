#include <Core/GameEngine.h>

void GameEngine::Run()
{
    window.Initialize(800, 600, L"DirectX Engine");
    renderer.Initialize(800, 600, window.GetHandle());

    triangle.Create(renderer.GetDevice());

    window.Show();
    while (window.IsOpen())
    {
        window.MessageLoop();

        renderer.Clear();
        renderer.Draw(triangle);
        renderer.Display();
    }
}