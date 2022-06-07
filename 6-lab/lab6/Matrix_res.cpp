#include "framework.h"
#include "Resource.h"
#include "matrix_res.h"
#include <string>

static HWND hWndOb2, hWndOb3;

int SendCopyData(HWND hWndDest, HWND hWndSrc, void* lp, long cb)
{
	COPYDATASTRUCT cds;

	cds.dwData = 1;     
	cds.cbData = cb;
	cds.lpData = lp;
	return SendMessage(hWndDest, WM_COPYDATA, (WPARAM)hWndSrc, (LPARAM)&cds);
}

INT_PTR CALLBACK MatrixCb(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_CLOSE:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		case IDC_EXEC:
		{
			hWndOb2 = FindWindow("OBJECT2", NULL);
			if (!hWndOb2)
			{
				WinExec("Object2.exe", SW_SHOW);
				hWndOb2 = FindWindow("OBJECT2", NULL);
			}
			const int len = 10;
			char size[len], min[len], max[len];
			long vals[3];
			GetDlgItemText(hDlg, IDC_MTXSIZE, size, len);
			GetDlgItemText(hDlg, IDC_MIN, min, len);
			GetDlgItemText(hDlg, IDC_MAX, max, len);
			vals[0] = std::stol(size);
			vals[1] = std::stol(min);
			vals[2] = std::stol(max);
			SendCopyData(hWndOb2, hDlg, vals, sizeof(vals));

			hWndOb3 = FindWindow("OBJECT3", NULL);
			if (!hWndOb3)
			{
				WinExec("Object3.exe", SW_SHOW);
				hWndOb3 = FindWindow("OBJECT3", NULL);
			}
			PostMessage(hWndOb3, WM_COMMAND, 10001, vals[0]);
		}
		break;
		default: break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
