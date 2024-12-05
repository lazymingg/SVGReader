#include "FigureDraw.h"

using namespace Gdiplus;

#pragma comment(lib, "Gdiplus.lib")

VOID OnPaint(HDC hdc)
{
    Graphics graphics(hdc);
    FigureDraw FigureDraw(graphics);
    FigureDraw.loadSVGFile("testSVG/sample4.svg");
    FigureDraw.draw();
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
    // Tạo cửa sổ console để xem output
    AllocConsole();
    FILE *stream;
    freopen_s(&stream, "CONOUT$", "w", stdout); // Chuyển hướng std::cout đến console
    freopen_s(&stream, "CONOUT$", "w", stderr); // Chuyển hướng std::cerr đến console
    freopen_s(&stream, "CONIN$", "r", stdin);   // Chuyển hướng std::cin đến console

    HWND hWnd;
    MSG msg;
    WNDCLASS wndClass;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;

    // Khởi tạo GDI+
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = TEXT("GettingStarted");

    RegisterClass(&wndClass);

    hWnd = CreateWindow(
        TEXT("GettingStarted"),  // Tên lớp cửa sổ
        TEXT("SVG Reader"), // Tiêu đề cửa sổ
        WS_OVERLAPPEDWINDOW,     // Kiểu cửa sổ
        CW_USEDEFAULT,           // Vị trí x ban đầu
        CW_USEDEFAULT,           // Vị trí y ban đầu
        CW_USEDEFAULT,           // Kích thước x ban đầu
        CW_USEDEFAULT,           // Kích thước y ban đầu
        NULL,                    // Handle cửa sổ cha
        NULL,                    // Handle menu cửa sổ
        hInstance,               // Handle instance chương trình
        NULL);                   // Tham số khởi tạo

    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    // Vòng lặp xử lý thông điệp
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Đóng GDI+
    GdiplusShutdown(gdiplusToken);

    // Đóng cửa sổ console khi chương trình kết thúc
    FreeConsole();

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        OnPaint(hdc);
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}