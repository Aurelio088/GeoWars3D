#include <System/Window.h>

Window::Window(int width, int height, const std::wstring& title)
    : handle(nullptr)
{
    Initialize(width, height, title);
}

void Window::Initialize(int width, int height, const std::wstring& title)
{
    WNDCLASSEX windowClass = {};
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.lpfnWndProc = HandleMessage;
    windowClass.hInstance = GetModuleHandle(nullptr);
    windowClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.lpszClassName = L"AppWindow";
    windowClass.hIconSm = windowClass.hIcon;

    RegisterClassEx(&windowClass);

    RECT rect = { 0, 0, width, height };

    DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    DWORD exStyle = WS_EX_APPWINDOW;

    AdjustWindowRectEx(&rect, style, FALSE, exStyle);

    width = rect.right - rect.left;
    height = rect.bottom - rect.top;

    SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);

    int x = std::max<int>((rect.right - rect.left - width) / 2, 0);
    int y = std::max<int>((rect.bottom - rect.top - height) / 2, 0);

    handle = CreateWindowEx(exStyle,
                            windowClass.lpszClassName,
                            title.c_str(),
                            style,
                            x,
                            y,
                            width,
                            height,
                            nullptr,
                            nullptr,
                            windowClass.hInstance,
                            nullptr);
}

void Window::MessageLoop()
{
    MSG msg = {};
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Window::Show() const
{
    ShowWindow(handle, SW_SHOWDEFAULT);
}

bool Window::IsOpen() const
{
    return IsWindowVisible(handle);
}

HWND Window::GetHandle() const
{
    return handle;
}

Window::~Window()
{
    DestroyWindow(handle);
}

LRESULT CALLBACK Window::HandleMessage(
    HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_KEYDOWN && wParam == VK_ESCAPE)
    {
        DestroyWindow(hWnd);
        return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}