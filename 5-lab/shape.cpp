#include "framework.h"
#include "shape.h"

void Shape::Set(int x1, int y1, int x2 = 0, int y2 = 0)
{
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

void PointShape::Show(HDC hdc)
{
	Ellipse(hdc, x2 - 5, y2 - 5, x2 + 5, y2 + 5);
}

void LineShape::Show(HDC hdc)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

void  RectShape::Show(HDC hdc)
{
	Rectangle(hdc, x1, y1, x2, y2);
}

void EllipseShape::Show(HDC hdc)
{
	int _x1 = x1 * 2 - x2;
	int _y1 = y1 * 2 - y2;

	Ellipse(hdc, _x1, _y1, x2, y2);
}

void LineOOShape::Show(HDC hdc)
{
	LineShape::Show(hdc);
	EllipseShape::Set(x1 - 10, y1 - 10, x1 + 10, y1 + 10);
	EllipseShape::Show(hdc);
	EllipseShape::Set(x2 - 10, y2 - 10, x2 + 10, y2 + 10);
	EllipseShape::Show(hdc);
}

void CubeShape::Show(HDC hdc)
{
	LineShape::Set(x1, y1, x2, y1);
	LineShape::Show(hdc);

	LineShape::Set(x1, y1, x1, y2);
	LineShape::Show(hdc);

	LineShape::Set(x1, y2, x2, y2);
	LineShape::Show(hdc);

	LineShape::Set(x2, y2, x2, y1);
	LineShape::Show(hdc);

	//second rect
	LineShape::Set(x1 + 30, y1 + 30, x2 + 30, y1 + 30);
	LineShape::Show(hdc);

	LineShape::Set(x1 + 30, y1 + 30, x1 + 30, y2 + 30);
	LineShape::Show(hdc);

	LineShape::Set(x1 + 30, y2 + 30, x2 + 30, y2 + 30);
	LineShape::Show(hdc);

	LineShape::Set(x2 + 30, y2 + 30, x2 + 30, y1 + 30);
	LineShape::Show(hdc);

	//connections

	LineShape::Set(x1, y1, x1 + 30, y1 + 30);
	LineShape::Show(hdc);

	LineShape::Set(x2, y2, x2 + 30, y2 + 30);
	LineShape::Show(hdc);

	LineShape::Set(x2, y1, x2 + 30, y1 + 30);
	LineShape::Show(hdc);

	LineShape::Set(x1, y2, x1 + 30, y2 + 30);
	LineShape::Show(hdc);
}
