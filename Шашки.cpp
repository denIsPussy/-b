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



const int MAX_NUM_RECORDS = 10;
int ccc = 0;
int setTimer = 0;
bool fuflo = true;
int* location_of_enemy;
int hod[2];

int timerDigit = 30;

int window = 1; // 1 - главное меню, 2 - сама игра, 3 - окно об окончании игры
int window_menu = 0; // 0 - нет, 1 - есть
int registration = 1;
int statusOfGame = 0; // 0 - игра идет, 1 - игра закончилась



int numberPlayer = 1; // номер игрока, который ходит в данный момент
int NumberOfFallenWhiteCheckers = 0;
int NumberOfFallenBlackCheckers = 0;

int count = 0;
TCHAR StrT1[20];
char str1[20];
TCHAR StrT2[20];
char str2[20];

//bool znak = true;
bool flag = true; // flag обозначает разрешение выделять шашку

int numRecords = 0;
int numberOfMovesPlayer1 = 0;
int numberOfMovesPlayer2 = 0;
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
   {0, 0, 0, 0, 2, 0, 0, 0},
   {0, 0, 0, 1, 0, 2, 0, 0},
   {3, 0, 0, 0, 0, 0, 0, 0}
};

//{0, 0, 0, 0, 0, 0, 0, 0},
//{ 0, 0, 3, 0, 2, 0, 2, 0 },
//{ 0, 2, 0, 0, 0, 0, 0, 0 },
//{ 0, 0, 0, 0, 2, 0, 2, 0 },
//{ 0, 2, 0, 0, 0, 0, 0, 0 },
//{ 0, 0, 0, 0, 2, 0, 0, 0 },
//{ 0, 0, 0, 1, 0, 2, 0, 0 },
//{ 3, 0, 0, 0, 0, 0, 0, 0 }
struct FIELD f = {
    {
        {0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 2, 0, 0, 0 },
        { 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    countOf(1) + countOf(31) + countOf(33) + countOf(3),
    countOf(2) + countOf(32) + countOf(34) + countOf(4),
    1
};

void RegistrationOfPlayer(HWND hWnd, HINSTANCE hInst, static HWND hEdt1, static HWND hBtn1, static HWND hBtn2, static HWND hEdt2, int n) {
    /*static HWND hBtn1;
    static HWND hEdt1;
    static HWND hBtn2;
    static HWND hEdt2;*/
    if (n == 1) {
        hEdt1 = CreateWindowW(_T("edit"), _T("Player 1"),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 250, 50, 160, 20,
            hWnd, 0, hInst, NULL);
        ShowWindow(hEdt1, SW_SHOWNORMAL);

        // Создаем и показываем кнопку
        hBtn1 = CreateWindowW(_T("button"), _T("Запомнить!"),
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            250, 100, 160, 20, hWnd, 0, hInst, NULL);
        ShowWindow(hBtn1, SW_SHOWNORMAL);
    }
    else if (n == 2) {
        hEdt2 = CreateWindowW(_T("edit"), _T("Player 2"),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 450, 50, 160, 20,
            hWnd, 0, hInst, NULL);
        ShowWindow(hEdt1, SW_SHOWNORMAL);

        // Создаем и показываем кнопку
        hBtn2 = CreateWindowW(_T("button"), _T("Запомнить!"),
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            450, 100, 160, 20, hWnd, 0, hInst, NULL);
        ShowWindow(hBtn1, SW_SHOWNORMAL);
    }
}
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
        815, 856, //(1300)815, 856
        NULL);
    Sleep(2000);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    SetTimer(hWnd, 2, 1000, 0);

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
    static HWND hBtn1; 
    static HWND hEdt1;
    static HWND hBtn2; 
    static HWND hEdt2; 

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
        if (lParam == (LPARAM)hBtn1)    // если нажали на кнопку
        {

            ccc++;
            // Берем имя из элемента редактирования и помещаем в строку Windows
            GetWindowText(hEdt1, StrT1, sizeof(StrT1));

            // Конвертирует строку Windows в строку Си 
            // !!!! ВАЖНО - корректно работает ТОЛЬКО для латинских букв!
            wcstombs(str1, StrT1, 20);

            // Фокус возвращаем в игру
            // нажатия клавиш снова управляют игрой!
            SetFocus(hWnd);

            // добавляем рекорд в таблицу рекордов
            //addRecord(str1); // новый рекорд просто вставляем снизу в таблицу
            InsertRecord(str1, false, 0); // новый рекорд вставляем в таблицу, сохраняя сортировку
            DestroyWindow(hBtn1);
            DestroyWindow(hEdt1);
            hEdt2 = CreateWindowW(_T("edit"), _T("Player 2"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 325, 50, 160, 20,
                hWnd, 0, hInst, NULL);
            ShowWindow(hEdt1, SW_SHOWNORMAL);

            // Создаем и показываем кнопку
            hBtn2 = CreateWindowW(_T("button"), _T("Запомнить!"),
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                325, 100, 160, 20, hWnd, 0, hInst, NULL);
            ShowWindow(hBtn1, SW_SHOWNORMAL);
            InvalidateRect(hWnd, NULL, TRUE);
            //break;
        }
        if (lParam == (LPARAM)hBtn2)    // если нажали на кнопку
        {

            ccc++;


            // Берем имя из элемента редактирования и помещаем в строку Windows
            GetWindowText(hEdt2, StrT2, sizeof(StrT2));

            // Конвертирует строку Windows в строку Си 
            // !!!! ВАЖНО - корректно работает ТОЛЬКО для латинских букв!
            wcstombs(str2, StrT2, 20);

            // Фокус возвращаем в игру
            // нажатия клавиш снова управляют игрой!
            SetFocus(hWnd);

            // добавляем рекорд в таблицу рекордов
            //addRecord(str2); // новый рекорд просто вставляем снизу в таблицу
            InsertRecord(str2, false, 0); // новый рекорд вставляем в таблицу, сохраняя сортировку

            DestroyWindow(hBtn2);
            DestroyWindow(hEdt2);
            window = 2;
            statusOfGame = 0;
            InvalidateRect(hWnd, NULL, TRUE);
            //break;
        }
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
        /*SetTimer(hWnd, 2, 100, 0);*/
        LoadRecordsEncoded();
        
        break;
    case WM_TIMER:
        switch (wParam)
        {
        case 2:

            timerDigit--;
            if (timerDigit == 0) {
                timerDigit = 30;
                Turning_the_board(hWnd);
            }
            /*HPEN hpen1 = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
            SelectObject(hdc, hpen1);
            SetBkMode(hdc, TRANSPARENT);
            Rectangle(hdc, 387 - 4, 770, 420 - 4, 800);
            char nNumberOfFallenWhiteCheckers[5];
            TCHAR  tNumberOfFallenWhiteCheckers[5];
            sprintf(nNumberOfFallenWhiteCheckers, "%d", timerDigit);
            OemToChar(nNumberOfFallenWhiteCheckers, tNumberOfFallenWhiteCheckers);
            TextOut(hdc, 390 - 2, 773, (LPCWSTR)tNumberOfFallenWhiteCheckers, _tcslen(tNumberOfFallenWhiteCheckers));
            DeleteObject(hpen1);*/
        
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hWnd, &ps);
        //mini_menu(hdc);

        if (window == 2) {
            SecondWindow(hdc);
            if (setTimer == 1) {
                SetTimer(hWnd, 2, 1000, 0);
                setTimer = 0;
            }
            HPEN hpen1 = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
            SelectObject(hdc, hpen1);
            //SetBkMode(hdc, TRANSPARENT);
            HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 255));
            SelectObject(hdc, hbrush);
            SetTextColor(hdc, RGB(0, 0, 0));
            Rectangle(hdc, /*387 - 4*/800-37, 770, 800/*420 - 4*/, 800);
            char nNumberOfFallenWhiteCheckers[5];
            TCHAR  tNumberOfFallenWhiteCheckers[5];
            sprintf(nNumberOfFallenWhiteCheckers, "%d", timerDigit);
            OemToChar(nNumberOfFallenWhiteCheckers, tNumberOfFallenWhiteCheckers);
            TextOut(hdc, 800-37 + 7, 775, (LPCWSTR)tNumberOfFallenWhiteCheckers, _tcslen(tNumberOfFallenWhiteCheckers));
            DeleteObject(hpen1);
            DeleteObject(hbrush);
        }
        
        else if (window == 1) {
            FirstWindow(hdc, hWnd, hInst);
            KillTimer(hWnd, 2);
        }
        else if (window == 3) {
            DrawRecords(hdc);
            KillTimer(hWnd, 2);
        }

        //if (registration == 1) RegistrationOfPlayer(hWnd, hInst);


        /*Rectangle(hdc, 770, 0, 800, 20);*/
        HPEN hpen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        SelectObject(hdc, hpen);
        HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, hbrush);
        SetTextColor(hdc, RGB(0, 0, 0));
        Rectangle(hdc, 770, 0, 800, 20);
        Ellipse(hdc, 770 + 7 - 2, 7, 770 + 7 + 6 - 2, 7 + 6);
        Ellipse(hdc, 770 + 14 - 2, 7, 770 + 14 + 6 - 2, 7 + 6);
        Ellipse(hdc, 770 + 21 - 2, 7, 770 + 21 + 6 - 2, 7 + 6);
        DeleteObject(hbrush);
        DeleteObject(hpen);
        if (window_menu == 1) mini_menu(hdc);
        
        EndPaint(hWnd, &ps);


    }
    break;
    case WM_LBUTTONDOWN:

        hod[0] = y;
        hod[1] = x;

        x = LOWORD(lParam);
        y = HIWORD(lParam);

        if (x >= 770 && x <= 800 && y <= 20 && y >= 0) {
            window_menu = !window_menu;
            statusOfGame = !statusOfGame;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }

        if (window == 2) {
            
            if (x >= 310 + 5 && x <= 490 + 5 && y <= 250 + 40 + 30 + 70 && y >= 250 + 40 + 60 && window_menu == 1) {
                window_menu = !window_menu;
                statusOfGame = !statusOfGame;
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
            if (x >= 310 + 5 && x <= 490 + 5 && y <= 250 + 2 * 40 + 2 * 30 + 70 && y >= 250 + 2 * 40 + 30 + 60 && window_menu == 1) {
                window = 3;
                window_menu = 0;
                statusOfGame = 1;
                InsertRecord(str1, true, 1);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
            if (x >= 310 + 5 && x <= 490 + 5 && y <= 250 + 3 * 40 + 3 * 30 + 70 && y >= 250 + 3 * 40 + 2 * 30 + 60 && window_menu == 1) {
                window = 1;
                statusOfGame = 1;
                window_menu = 0; 
                registration = 0;
                InsertRecord(str1, true, 1);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
        }
        else if (window == 3) {
            if (x >= 310 + 5 && x <= 490 + 5 && y <= 250 + 40 + 30 + 70 && y >= 250 + 40 + 60) {
                window = 1;
                window_menu = !window_menu;
                statusOfGame = 1;
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
            if (x >= 310 + 5 && x <= 490 + 5 && y <= 250 + 2 * 40 + 2 * 30 + 70 && y >= 250 + 2 * 40 + 30 + 60) {
                window = 3;
                window_menu = 0;
                statusOfGame = 1;
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
            if (x >= 310 + 5 && x <= 490 + 5 && y <= 250 + 3 * 40 + 3 * 30 + 70 && y >= 250 + 3 * 40 + 2 * 30 + 60) {
                window = 1;
                statusOfGame = 1;
                window_menu = 0;
                registration = 0;

                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
        }
        else if (window == 1) {
            if (x >= 310 + 5 - 10 && x <= 490 + 5 - 10 + 25 && y <= 250 + 40 + 30 + 70 && y >= 250 + 40 + 60) {
                
                if (registration == 1) {
                    //RegistrationOfPlayer(hWnd, hInst, hEdt1, hBtn1, hBtn2, hEdt2, 1);
                    hEdt1 = CreateWindowW(_T("edit"), _T("Player 1"),
                        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 325, 50, 160, 20,
                        hWnd, 0, hInst, NULL);
                    ShowWindow(hEdt1, SW_SHOWNORMAL);

                    hBtn1 = CreateWindowW(_T("button"), _T("Запомнить!"),
                        WS_CHILD | WS_VISIBLE | WS_BORDER,
                        325, 100, 160, 20, hWnd, 0, hInst, NULL);
                    ShowWindow(hBtn1, SW_SHOWNORMAL);

                    /*hEdt2 = CreateWindowW(_T("edit"), _T("Игрок 2"),
                        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 450, 50, 160, 20,
                        hWnd, 0, hInst, NULL);
                    ShowWindow(hEdt1, SW_SHOWNORMAL);

                    hBtn2 = CreateWindowW(_T("button"), _T("Запомнить!"),
                        WS_CHILD | WS_VISIBLE | WS_BORDER,
                        450, 100, 160, 20, hWnd, 0, hInst, NULL);
                    ShowWindow(hBtn1, SW_SHOWNORMAL);*/
                    if (registration == 0) registration = 1;
                    else registration = 0;
                    setTimer = 1;
                    LoadingTheInitialGame();
                    //registration = !registration; 
                }
                //registration = !registration;
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
            if (x >= 310 + 5 - 10 && x <= 490 + 5 - 10 + 25 && y <= 250 + 3 * 40 + 3 * 30 + 70 && y >= 250 + 3 * 40 + 2 * 30 + 60) {
                PostQuitMessage(0);
                break;
            }
            if (x >= 310 + 5 - 10 && x <= 490 + 5 - 10 + 25 && y <= 250 + 2 * 40 + 2 * 30 + 70 && y >= 250 + 2 * 40 + 30 + 60) {
                window = 3;
                statusOfGame = 1;
                window_menu = 0;
                //registration = 0;
            }

        }
        x /= 100;
        y /= 100;
        if (window == 2) {
            if (statusOfGame == 0)
            {

                if (x < 8 && x >= 0 && y < 8 && y >= 0) leftClickingForTheSecondWindow(hdc, lParam, hWnd);
            }
        }
        DestroyWindow(hBtn1);
        DestroyWindow(hEdt1);
        DestroyWindow(hBtn2);
        DestroyWindow(hEdt2);
        registration = 1;
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
                hEdt1 = CreateWindowW(_T("edit"), _T("Игрок 1"),
                    WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 250, 50, 160, 20,
                    hWnd, 0, hInst, NULL);
                ShowWindow(hEdt1, SW_SHOWNORMAL);

                // Создаем и показываем кнопку
                hBtn1 = CreateWindowW(_T("button"), _T("Запомнить!"),
                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                    250, 100, 160, 20, hWnd, 0, hInst, NULL);
                ShowWindow(hBtn1, SW_SHOWNORMAL);

                hEdt2 = CreateWindowW(_T("edit"), _T("Игрок 2"),
                    WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 450, 50, 160, 20,
                    hWnd, 0, hInst, NULL);
                ShowWindow(hEdt1, SW_SHOWNORMAL);

                // Создаем и показываем кнопку
                hBtn2 = CreateWindowW(_T("button"), _T("Запомнить!"),
                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                    450, 100, 160, 20, hWnd, 0, hInst, NULL);
                ShowWindow(hBtn1, SW_SHOWNORMAL);
                
                //EnableWindow(GetDlgItem(hWnd, 0), false);
                fuflo = !fuflo;
            }
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case VK_DOWN:
            if (!fuflo)
            {
                DestroyWindow(hBtn1);
                DestroyWindow(hEdt1);
                DestroyWindow(hBtn2);
                DestroyWindow(hEdt2);
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
        case 0x51:
            window_menu = !window_menu;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        break;
    case WM_DESTROY:
        SaveRecordsEncoded();
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
