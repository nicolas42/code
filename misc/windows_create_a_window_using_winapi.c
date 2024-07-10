// To compile using visual studio from the command line use something like this
// "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
// cl mywindow.c user32.lib gdi32.lib


#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Register the window class
    const char CLASS_NAME[]  = "My Window Class";
    WNDCLASS wc = {0};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                     // Optional window styles
        CLASS_NAME,            // Window class
        "My Window",           // Window text
        WS_OVERLAPPEDWINDOW,   // Window style
        CW_USEDEFAULT,         // X position
        CW_USEDEFAULT,         // Y position
        640,                   // Width
        480,                   // Height
        NULL,                  // Parent window    
        NULL,                  // Menu
        hInstance,             // Instance handle
        NULL                   // Additional application data
        );

    if (hwnd == NULL) {
        return 1;
    }

    // Show the window
    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{


    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:


            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // create a red brush
            HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush); // select the brush into the DC
            RECT rect = { 0, 0, 640, 480 }; // create a rectangle to fill
            FillRect(hdc, &rect, hBrush); // fill the rectangle with the selected brush
            SelectObject(hdc, hOldBrush); // restore the original brush
            DeleteObject(hBrush); // delete the created brush

            EndPaint(hwnd, &ps);
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
