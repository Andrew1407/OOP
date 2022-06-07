#include "framework.h"
#include "shape.h"

void Shape::Set(int x1, int y1, int x2, int y2)
{
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

void PointShape::Show(HDC hdc)
{
	HBRUSH hBrush, hBrushOld;
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	Ellipse(hdc, x2 - 5, y2 - 5, x2 + 5, y2 + 5);
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}

void LineShape::Show(HDC hdc)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

void  RectShape::Show(HDC hdc)
{
	HBRUSH hBrush, hBrushOld;
	hBrush = (HBRUSH)CreateSolidBrush(RGB(240, 230, 140));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	Rectangle(hdc, x1, y1, x2, y2);

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}

void EllipseShape::Show(HDC hdc)
{
	HBRUSH hBrush, hBrushOld;
	hBrush = (HBRUSH)CreateSolidBrush(RGB(128, 128, 128));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	int _x1 = x1 * 2 - x2;
	int _y1 = y1 * 2 - y2;

	Ellipse(hdc, _x1, _y1, x2, y2);

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}
