#include "framework.h"
#include "Шашки.h"
#include "Game.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
//#include <stdio.h>
//#include "Game.cpp"
#define MAX_LOADSTRING 100
#define FALSE false

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HDC hdc;

int* location_of_enemy;
int hod[2];
int window = 2;
int numberPlayer = 1; // номер игрока, который ходит в данный момент
int NumberOfFallenWhiteCheckers = 0;
int NumberOfFallenBlackCheckers = 0;
int count = 0;

//bool znak = true;
bool flag = true; // flag обозначает разрешение выделять шашку


int x = 0; 
int y = 0; // координаты нажатия

int field[8][8] = {                 // игровое поле
   {0, 2, 0, 2, 0, 2, 0, 2},
   {2, 0, 2, 0, 0, 0, 2, 0},
   {0, 2, 0, 2, 0, 2, 0, 2},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 2, 0, 0, 0, 2},
   {1, 0, 1, 0, 1, 0, 1, 0},
   {0, 1, 0, 1, 0, 1, 0, 1},
   {1, 0, 1, 0, 1, 0, 1, 0}
};

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    HWND hWnd = CreateWindowEx(WS_EX_TOPMOST, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 250, 400, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return FALSE;
    }
    SetWindowPos(hWnd,
        HWND_TOP,
        250, 100,
        1300, 856, //815, 856
        NULL);
    Sleep(2000);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}


//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
//HDC return1();
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
        //HDC hdc;
        BITMAP bm;
        RECT rect;
        PAINTSTRUCT ps;
        LOGFONT lf;
        HFONT hFont;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hWnd, &ps);

        if (window == 2) SecondWindow(hdc);
        else if (window == 1) FirstWindow(hdc);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_LBUTTONDOWN:
        
        hod[0] = y;
        hod[1] = x;

        x = LOWORD(lParam) / 100; 
        y = HIWORD(lParam) / 100; 

        if (x < 8 && x >= 0 && y < 8 && y >= 0) leftClickingForTheSecondWindow(hdc, lParam);
        
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_RBUTTONDOWN:

        hod[0] = y;
        hod[1] = x;

        x = LOWORD(lParam) / 100;
        y = HIWORD(lParam) / 100;
        
        if (x < 8 && x >= 0 && y < 8 && y >= 0) rightClickingForTheSecondWindow(hdc, lParam);

        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_KEYDOWN:
        switch (wParam) {
        case VK_LEFT:
            window--;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
    case VK_RIGHT:
        window++;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
