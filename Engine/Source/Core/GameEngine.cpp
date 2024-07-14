#include <Core/GameEngine.h>

void GameEngine::Run()
{
    window.Initialize(800, 600, L"DirectX Engine");
    renderer.Initialize(800, 600, window.GetHandle());

    Initialize();

    window.Show();
    while (window.IsOpen())
    {
        window.MessageLoop();
        Update();

        renderer.Clear();
        Draw();
        renderer.Display();
    }
}