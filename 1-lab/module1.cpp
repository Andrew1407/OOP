#include "framework.h"
#include "resource.h"
#include "module1.h"

static int SB_POS;
static INT_PTR CALLBACK    Work1Cb(HWND, UINT, WPARAM, LPARAM);

int Work1Func(HINSTANCE hInst, HWND hWnd, char* strText)
{
	if (DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Work1Cb))
	{
		_itoa_s(::SB_POS, strText, 4, 10);
		InvalidateRect(hWnd, NULL, TRUE);
	}
	int strText_length =
		(SB_POS < 10) ? 2 :
		(SB_POS < 100) ? 3 : 4;
	return strText_length;
}

static INT_PTR  CALLBACK Work1Cb(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		SetScrollRange(GetDlgItem(hDlg, IDC_SCROLLBAR1), SB_CTL, 1, 100, TRUE);
		::SB_POS = GetScrollPos(GetDlgItem(hDlg, IDC_SCROLLBAR1), SB_CTL);
		return 1;
	case WM_COMMAND:
		::SB_POS = GetScrollPos(GetDlgItem(hDlg, IDC_SCROLLBAR1), SB_CTL);
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return 0;
		case IDYES1:
			EndDialog(hDlg, 1);
			return 1;
		default: break;
		}
		return 0;
	case WM_HSCROLL:
		switch (LOWORD(wParam))
		{
		case SB_LINELEFT:
			::SB_POS--;
			break;
		case SB_LINERIGHT:
			::SB_POS++;
			break;
		case SB_THUMBPOSITION:
			::SB_POS = HIWORD(wParam);
			break;
		default: break;
		}
		SetScrollPos(GetDlgItem(hDlg, IDC_SCROLLBAR1), SB_CTL, ::SB_POS, FALSE);
		break;
	default: break;
	}
	return 0;
}

