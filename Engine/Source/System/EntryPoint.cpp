#include <Core/GameEngine.h>
#include <System/EntryPoint.h>
#include <System/Win32.h>

int WINAPI WinMain(_In_ HINSTANCE hInstance,
                   _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR lpCmdLine,
                   _In_ int nShowCmd)
{
    return main();
}