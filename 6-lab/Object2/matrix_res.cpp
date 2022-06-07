#include "framework.h"
#include <string>
#include <ctime>
#include "matrix_res.h"

static int size, min, max;			//income values from "Lab6" window 

void OnCopyData(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	COPYDATASTRUCT* cds; cds = (COPYDATASTRUCT*)lParam;
	long* p = (long*)cds->lpData;
	size = p[0];
	min = p[1];
	max = p[2];
}

int PutTextToClipboard(HWND hWnd, const char* src) 
{
	HGLOBAL hglbCopy; BYTE* pTmp; long len;

	if (src == NULL) return 0; 
	if (src[0] == 0) return 0; 
	len = strlen(src); 
	hglbCopy = GlobalAlloc(GHND, len + 1);
	if (hglbCopy == NULL) return FALSE; 
	pTmp = (BYTE*)GlobalLock(hglbCopy);
	memcpy(pTmp, src, len + 1);     
	GlobalUnlock(hglbCopy); 
	if (!OpenClipboard(hWnd)) 
	{
		GlobalFree(hglbCopy);    
		return 0; 
	} 
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hglbCopy); 
	CloseClipboard(); 
	return 1;
}

int GenerateMatrix(HWND hWnd)
{
	srand(time(0));
	const int _max = max - min + 1;
	std::string mtx = "";
	std::string row = "";
	int x = 20, y = 20;
	int el;
	HDC hdc = GetDC(hWnd);
	for (int i = 0; i < size; i++)
	{
		row = "";
		for (int u = 0; u < size; u++)
		{
			el = rand() % _max + min;
			row += std::to_string(el) + "  ";
		}
		TextOut(hdc, x, y, row.c_str(), row.length());
		y += 20;
		mtx += row + "\n";
	}
	ReleaseDC(hWnd, hdc);
	PutTextToClipboard(hWnd, mtx.c_str());
	return size;
}

