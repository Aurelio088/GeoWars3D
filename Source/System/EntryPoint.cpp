#include <Core/GameEngine.h>
#include <System/Win32.h>

int WINAPI WinMain(_In_ HINSTANCE hInstance,
                   _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR lpCmdLine,
                   _In_ int nShowCmd)
{
    GameEngine game;
    game.Run();

    return 0;
}