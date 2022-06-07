#include "framework.h"
#include "resource.h"
#include "toolbar.h"

static int press[4] = { 0, 0, 0, 0 };

void TBButtonPressed(HWND hwndToolBar, int id)
{
	switch (id)
	{
	case IDM_POINT:
		press[0] = 1;
		break;
	case IDM_LINE:
		press[1] = 1;
		break;
	case IDM_RECT:
		press[2] = 1;
		break;
	case IDM_ELLIPSE:
		press[3] = 1;
		break;
	}

	SendMessage(hwndToolBar, TB_PRESSBUTTON, IDM_POINT, press[0]);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, IDM_LINE, press[1]);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, IDM_RECT, press[2]);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, IDM_ELLIPSE, press[3]);

	for (int i = 0; i < 4; press[i++] = 0);
}

void TBIconsNotify(LPARAM lParam)
{
	LPNMHDR pnmh = (LPNMHDR)lParam;
	LPWSTR pText;

	if (pnmh->code == TTN_NEEDTEXT)
	{
		LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
		switch (lpttt->hdr.idFrom)
		{
		case IDM_POINT:
			pText = (LPWSTR)"Точка";
			break;
		case IDM_LINE:
			pText = (LPWSTR)"Лінія";
			break;
		case IDM_RECT:
			pText = (LPWSTR)"Прямокутник";
			break;
		case IDM_ELLIPSE:
			pText = (LPWSTR)"Еліпс";
			break;
		default: pText = (LPWSTR)"Щось невідоме";
		}
		lstrcpy(lpttt->szText, pText);
	}
}

void OnSize(HWND hWnd, HWND hwndToolBar)
{
	RECT rc, rw;

	if (hwndToolBar)
	{
		GetClientRect(hWnd, &rc);
		GetWindowRect(hwndToolBar, &rw);
		MoveWindow(hwndToolBar, 0, 0, rc.right - rc.left, rw.bottom - rw.top, 0);
	}
}
