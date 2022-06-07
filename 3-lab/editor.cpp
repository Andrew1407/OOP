#include "framework.h"
#include "resource.h"
#include "editor.h"

void Editor::OnLBdown(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
}

void PointEditor::OnMouseMove(HWND hWnd)
{
	OnLBup(hWnd);
}

void PointEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	HDC hdc;
	hdc = GetDC(hWnd);
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	HBRUSH hBrush, hBrushOld;
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	Ellipse(hdc, x2 - 5, y2 - 5, x2 + 5, y2 + 5);
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}

void LineEditor::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPenOld, hPen;
	HDC hdc;
	hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 205));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void LineEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;

	HDC hdc;
	hdc = GetDC(hWnd);
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

void RectEditor::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPenOld, hPen;
	HBRUSH hBrush, hBrushOld;
	HDC hdc;
	hdc = GetDC(hWnd);

	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 205));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	hBrush = (HBRUSH)CreateSolidBrush(RGB(135, 206, 250));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);

	x2 = pt.x;
	y2 = pt.y;

	Rectangle(hdc, x1, y1, x2, y2);

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void RectEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	HDC hdc;
	hdc = GetDC(hWnd);
	HBRUSH hBrush, hBrushOld;

	hBrush = (HBRUSH)CreateSolidBrush(RGB(240, 230, 140));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, x1, y1, x2, y2);
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}

void EllipseEditor::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPenOld, hPen;
	HBRUSH hBrush, hBrushOld;
	HDC hdc;

	hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);

	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 205));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;

	int _x1 = x1 * 2 - x2;
	int _y1 = y1 * 2 - y2;

	Ellipse(hdc, _x1, _y1, x2, y2);

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);	
}

void EllipseEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	HDC hdc;
	HBRUSH hBrush, hBrushOld;
	hdc = GetDC(hWnd);

	hBrush = (HBRUSH)CreateSolidBrush(RGB(128, 128, 128));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	int _x1 = x1 * 2 - x2;
	int _y1 = y1 * 2 - y2;

	Ellipse(hdc, _x1, _y1, x2, y2);

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}
