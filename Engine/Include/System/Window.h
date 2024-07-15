#pragma once

#include <System/Win32.h>
#include <string>

class Window
{
public:
    Window() = default;
    Window(int width, int height, const std::wstring& title);

    void Initialize(int width, int height, const std::wstring& title);
    void MessageLoop();

    void Show() const;
    bool IsOpen() const;

    HWND GetHandle() const;

    virtual ~Window();

private:
    static LRESULT CALLBACK HandleMessage(
        HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;

private:
    HWND handle;
};