// Lab4.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab4.h"
#include "toolbar.h"
#include "editor.h"
#include "shape_editor.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

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
    LoadStringW(hInstance, IDC_LAB4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB4));

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

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB4);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

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

HWND hwndToolBar;
MyEditor Figure;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_SIZE:
		OnSize(hWnd, hwndToolBar);
		break;

	case WM_CREATE:
	{
		InitCommonControls();

		TBBUTTON tbb[6];

		SendMessage(hwndToolBar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

		ZeroMemory(tbb, sizeof(tbb));
		tbb[0].iBitmap = 0;
		tbb[0].fsState = TBSTATE_ENABLED;
		tbb[0].fsStyle = TBSTYLE_BUTTON;
		tbb[0].idCommand = IDM_POINT;

		tbb[1].iBitmap = 1;
		tbb[1].fsState = TBSTATE_ENABLED;
		tbb[1].fsStyle = TBSTYLE_BUTTON;
		tbb[1].idCommand = IDM_LINE;

		tbb[2].iBitmap = 2;
		tbb[2].fsState = TBSTATE_ENABLED;
		tbb[2].fsStyle = TBSTYLE_BUTTON;
		tbb[2].idCommand = IDM_RECT;

		tbb[3].iBitmap = 3;
		tbb[3].fsState = TBSTATE_ENABLED;
		tbb[3].fsStyle = TBSTYLE_BUTTON;
		tbb[3].idCommand = IDM_ELLIPSE;

		tbb[4].iBitmap = 4;
		tbb[4].fsState = TBSTATE_ENABLED;
		tbb[4].fsStyle = TBSTYLE_BUTTON;
		tbb[4].idCommand = IDM_OOLINE;

		tbb[5].iBitmap = 5;
		tbb[5].fsState = TBSTATE_ENABLED;
		tbb[5].fsStyle = TBSTYLE_BUTTON;
		tbb[5].idCommand = IDM_CUBE;

		hwndToolBar = CreateToolbarEx(hWnd,
			WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
			IDC_MY_TOOLBAR,
			1,
			hInst,
			IDB_BITMAP1,
			tbb,
			0,
			24, 24, 24, 24,
			sizeof(TBBUTTON));
		SendMessage(hwndToolBar, TB_ADDBUTTONS, 6, (LPARAM)&tbb);

		break;
	}

	case WM_NOTIFY:
	{
		TBIconsNotify(lParam);
		break;
	}

	case WM_INITMENUPOPUP:
		Figure.OnInitMenuPopup(hWnd, wParam);
		break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_POINT:
			Figure.Start(new Point);
			TBButtonPressed(hwndToolBar, IDM_POINT);
			break;
		case IDM_LINE:
			Figure.Start(new Line);
			TBButtonPressed(hwndToolBar, IDM_LINE);
			break;
		case IDM_RECT:
			Figure.Start(new Rect);
			TBButtonPressed(hwndToolBar, IDM_RECT);
			break;
		case IDM_ELLIPSE:
			Figure.Start(new EllipseF);
			TBButtonPressed(hwndToolBar, IDM_ELLIPSE);
			break;
		case IDM_OOLINE:
			Figure.Start(new LineOO);
			TBButtonPressed(hwndToolBar, IDM_OOLINE);
			break;
		case IDM_CUBE:
			Figure.Start(new Cube);
			TBButtonPressed(hwndToolBar, IDM_CUBE);
			break;
		}
	}
	break;
	case WM_LBUTTONDOWN:
		Figure.OnLBdown(hWnd);
		break;
	case WM_LBUTTONUP:
		Figure.OnLBup(hWnd);
		break;
	case WM_MOUSEMOVE:
		Figure.OnMouseMove(hWnd);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		Figure.OnPaint(hdc);
		EndPaint(hWnd, &ps);
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
