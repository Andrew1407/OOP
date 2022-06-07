#include "framework.h"
#include "resource.h"
#include "module2.h"

static INT_PTR CALLBACK Work2Cb(HWND, UINT, WPARAM, LPARAM);

int Work2Func(HINSTANCE hInst, HWND hWnd, int dialog)
{
	switch (dialog)
	{
	case 1:
		dialog = DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2_NEXT), hWnd, Work2Cb);
		break;
	case -1:
		dialog = DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Work2Cb);
		break;
	case 0: return 0;
	}
	Work2Func(hInst, hWnd, dialog);
}

INT_PTR CALLBACK Work2Cb(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return 0;
		case IDNEXT:
			EndDialog(hDlg, 1);
			return 1;
		case IDGOBACK:
			EndDialog(hDlg, -1);
			return -1;
		}
	}
	return 0;
}