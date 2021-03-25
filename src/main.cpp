#include <iostream>
#include <string>
#include <windows.h>

namespace {

const std::string& windowClassName = "ClipboardAssistant Monitor Window";
const std::string& windowTitle = "ClipboardAssistant Monitor Window";

LRESULT CALLBACK windowProc(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam) {
    switch (messageCode) {
        case WM_CREATE:
            AddClipboardFormatListener(windowHandle);
            break;
        case WM_CLOSE:
            DestroyWindow(windowHandle);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_CLIPBOARDUPDATE:
            OutputDebugString("ClipboardUpdate");
            break;
    }

    return DefWindowProc(windowHandle, messageCode, wParam, lParam);
}


std::string registerWindowClass(HINSTANCE instanceHandle) {
    WNDCLASS windowClass = {0};
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = windowProc;
    windowClass.hInstance = instanceHandle;
    windowClass.lpszClassName = windowClassName.c_str();
    windowClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClass(&windowClass);

    return windowClassName;
}

}

int WinMain(
    HINSTANCE instanceHandle,
    HINSTANCE previousInstanceHandle,
    LPSTR commandLine,
    int showCmd
) {
    auto className = registerWindowClass(instanceHandle);
    HWND windowHandle = CreateWindowEx(
        0,
        className.c_str(),
        windowTitle.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr,
        nullptr,
        instanceHandle,
        nullptr);

    ShowWindow(windowHandle, showCmd);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
