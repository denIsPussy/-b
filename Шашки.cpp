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

bool fuflo = true;
int statusOfGame = 0; // 0 - игра идет, 1 - игра закончилась
int* location_of_enemy;
int hod[2];
int window = 2; // 1 - главное меню, 2 - сама игра, 3 - окно об окончании игры
int numberPlayer = 1; // номер игрока, который ходит в данный момент
int NumberOfFallenWhiteCheckers = 0;
int NumberOfFallenBlackCheckers = 0;
int count = 0;

//bool znak = true;
bool flag = true; // flag обозначает разрешение выделять шашку


int x = 0;
int y = 0; // координаты нажатия

//int field[8][8] = {                 // игровое поле
//   {0, 2, 0, 2, 0, 0, 0, 2},
//   {2, 0, 2, 0, 2, 0, 2, 0},
//   {0, 2, 0, 1, 0, 2, 0, 2},
//   {0, 0, 0, 0, 0, 0, 0, 0},
//   {0, 0, 0, 2, 0, 0, 0, 2},
//   {1, 0, 1, 0, 1, 0, 1, 0},
//   {0, 1, 0, 1, 0, 2, 0, 1},
//   {1, 0, 1, 0, 0, 0, 1, 0}
//};

int field[8][8] = {                 // игровое поле
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 3, 0, 2, 0, 2, 0},
   {0, 2, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 2, 0, 2, 0},
   {0, 2, 0, 0, 0, 0, 0, 0},
   {0, 0, 3, 0, 2, 0, 2, 0},
   {0, 0, 0, 1, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0}
};


struct FIELD f = {
    {
       {0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 3, 0, 2, 0, 2, 0},
       {0, 2, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 2, 0, 2, 0},
       {0, 2, 0, 0, 0, 0, 0, 0},
       {0, 0, 3, 0, 2, 0, 2, 0},
       {0, 0, 0, 1, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0}
    },
    countOf(1) + countOf(31) + countOf(33) + countOf(3),
    countOf(2) + countOf(32) + countOf(34) + countOf(4),
    1
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

void dfdf() {

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
    static HWND hBtn; // дескриптор кнопки
    static HWND hEdt1; // дескрипторы поля редактирования

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

        //if (lParam == (LPARAM)hBtn)    // если нажали на кнопку
        //{
        //    TCHAR StrT[20];
        //    char str[20];

        //    // Берем имя из элемента редактирования и помещаем в строку Windows
        //    GetWindowText(hEdt1, StrT, sizeof(StrT));

        //    // Конвертирует строку Windows в строку Си 
        //    // !!!! ВАЖНО - корректно работает ТОЛЬКО для латинских букв!
        //    wcstombs(str, StrT, 20);

        //    // Фокус возвращаем в игру
        //    // нажатия клавиш снова управляют игрой!
        //    SetFocus(hWnd);

        //    // добавляем рекорд в таблицу рекордов
        //    addRecord(str); // новый рекорд просто вставляем снизу в таблицу
        //    //InsertRecord(str); // новый рекорд вставляем в таблицу, сохраняя сортировку
        //    InvalidateRect(hWnd, NULL, TRUE);

    }
    break;
    case WM_CREATE: // сообщение создания окна

        //hInst = ((LPCREATESTRUCT)lParam)->hInstance; // дескриптор приложения
        //// Создаем и показываем поле редактирования - для ввода имени рекордсмена
        //hEdt1 = CreateWindowW(_T("edit"), _T("Noname"),
        //    WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 650, 50, 160, 20,
        //    hWnd, 0, hInst, NULL);
        //ShowWindow(hEdt1, SW_SHOWNORMAL);

        //// Создаем и показываем кнопку
        //hBtn = CreateWindowW(_T("button"), _T("Запомнить!"),
        //    WS_CHILD | WS_VISIBLE | WS_BORDER,
        //    650, 100, 160, 20, hWnd, 0, hInst, NULL);
        //ShowWindow(hBtn, SW_SHOWNORMAL);

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

        if (statusOfGame == 0)
        {
            hod[0] = y;
            hod[1] = x;

            x = LOWORD(lParam) / 100;
            y = HIWORD(lParam) / 100;

            if (x < 8 && x >= 0 && y < 8 && y >= 0) leftClickingForTheSecondWindow(hdc, lParam);
        }

        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_RBUTTONDOWN:
        movement(true);

        if (statusOfGame == 0)
        {
            hod[0] = y;
            hod[1] = x;

            x = LOWORD(lParam) / 100;
            y = HIWORD(lParam) / 100;

            if (x < 8 && x >= 0 && y < 8 && y >= 0) rightClickingForTheSecondWindow(hdc, lParam);
        }

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
        case VK_UP:
            if (fuflo) {
                hEdt1 = CreateWindowW(_T("edit"), _T("Noname"),
                    WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 850, 50, 160, 20,
                    hWnd, 0, hInst, NULL);
                ShowWindow(hEdt1, SW_SHOWNORMAL);

                // Создаем и показываем кнопку
                hBtn = CreateWindowW(_T("button"), _T("Запомнить!"),
                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                    850, 100, 160, 20, hWnd, 0, hInst, NULL);
                ShowWindow(hBtn, SW_SHOWNORMAL);
                //EnableWindow(GetDlgItem(hWnd, 0), false);
                fuflo = !fuflo;
            }
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case VK_DOWN:
            if (!fuflo)
            {
                DestroyWindow(hBtn);
                DestroyWindow(hEdt1);
                fuflo = !fuflo;
            }
            InvalidateRect(hWnd, NULL, TRUE);
            break;	
        case 0x58: 
            saveGame();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case 0x4C:
            loadGame();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case 0x49:
            LoadingTheInitialGame();
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
