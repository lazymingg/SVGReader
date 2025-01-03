﻿#include "FigureDraw.h"

using namespace Gdiplus;

#pragma comment(lib, "Gdiplus.lib")
static string svgFile;

// khởi tạo singleton của AttributeFactory
AttributeFactory *AttributeFactory::instance = nullptr;
Defs *Defs::instance = nullptr;

VOID OnPaint(HDC hdc, string filePath)
{
    Graphics graphics(hdc);
    FigureDraw FigureDraw(graphics);
    FigureDraw.loadSVGFile("testSVG/svg-01.svg");
    FigureDraw.draw();
    // test load defs
    //get instance
    Defs *defs = Defs::getInstance();
    //print defs
    std::map<std::string, vector<DefsTag *>> defsMap = defs->getDefsMap();
    for (auto &tag : defsMap)
    {
        std::cout << tag.first << std::endl;
        for (auto &defsTag : tag.second)
        {
            std::cout << defsTag->toString() << std::endl;
        }
    }

}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR cmdline, INT iCmdShow)
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

    svgFile = "testSVG/svg-01.svg";
    if (cmdline != nullptr && strlen(cmdline) > 0) svgFile = cmdline;
    cout << svgFile << endl;

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
        //NULL);                   // Tham số khởi tạo
        (LPVOID)svgFile.c_str()); // Tham số khởi tạo
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
    case WM_CREATE:
    {
        svgFile = reinterpret_cast<LPCSTR>(((LPCREATESTRUCT)lParam)->lpCreateParams);
        return 0;
    }
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        OnPaint(hdc, svgFile);
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}