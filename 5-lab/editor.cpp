#include "framework.h"
#include "resource.h"
#include "shape.h"
#include "editor.h"

void Editor::GetShape(int& shape) { shape = this->shape; }

void Editor::GetCoords(int* CoordsList)
{
	CoordsList[0] = x1;
	CoordsList[1] = y1;
	CoordsList[2] = x2;
	CoordsList[3] = y2;
}

void Editor::SetCoords(const int* coords)
{
	x1 = coords[0];
	y1 = coords[1];
	x2 = coords[2];
	y2 = coords[3];
}

void Editor::OnLBdown(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
}

void Point::OnMouseMove(HWND hWnd)
{
	OnLBup(hWnd);
}

void Point::OnLBup(HWND hWnd)
{
	POINT pt;
	HDC hdc;
	Shape* p = new PointShape;
	hdc = GetDC(hWnd);
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	HBRUSH hBrush, hBrushOld;
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	if (p)
	{
		p->Set(x1, y1, x2, y2);
		p->Show(hdc);
		delete p;
	}

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}

void Line::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPenOld, hPen;
	HDC hdc;
	Shape* p = new LineShape;

	hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 205));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;

	if (p)
	{
		p->Set(x1, y1, x2, y2);
		p->Show(hdc);
		delete p;
	}

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void Line::OnLBup(HWND hWnd)
{
	POINT pt;
	Shape* p = new LineShape;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;

	HDC hdc;
	hdc = GetDC(hWnd);
	if (p)
	{
		p->Set(x1, y1, x2, y2);
		p->Show(hdc);
		delete p;
	}
}

void Rect::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPenOld, hPen;
	HBRUSH hBrush, hBrushOld;
	Shape* p = new RectShape;
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
	if (p)
	{
		p->Set(x1, y1, x2, y2);
		p->Show(hdc);
		delete p;
	}

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void Rect::OnLBup(HWND hWnd)
{
	POINT pt;
	Shape* p = new RectShape;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	HDC hdc;
	hdc = GetDC(hWnd);
	HBRUSH hBrush, hBrushOld;

	hBrush = (HBRUSH)CreateSolidBrush(RGB(240, 230, 140));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	if (p)
	{
		p->Set(x1, y1, x2, y2);
		p->Show(hdc);
		delete p;
	}
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}

void EllipseF::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPenOld, hPen;
	HBRUSH hBrush, hBrushOld;
	HDC hdc;
	Shape* p = new EllipseShape;

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

	if (p)
	{
		p->Set(x1, y1, x2, y2);
		p->Show(hdc);
		delete p;
	}

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void EllipseF::OnLBup(HWND hWnd)
{
	POINT pt;
	Shape* p = new EllipseShape;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	HDC hdc;
	HBRUSH hBrush, hBrushOld;
	hdc = GetDC(hWnd);

	hBrush = (HBRUSH)CreateSolidBrush(RGB(128, 128, 128));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	if (p)
	{
		p->Set(x1, y1, x2, y2);
		p->Show(hdc);
		delete p;
	}

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}

void Point::Show(HDC hdc)
{
	Shape* p = new PointShape;
	HBRUSH hBrush, hBrushOld;
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	if (p)
	{
		p->Set(x1, y1, x2, y2);
		p->Show(hdc);
		delete p;
	}

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}

void Line::Show(HDC hdc)
{
	Shape* p = new LineShape;
	if (p)
	{
		p->Set(x1, y1, x2, y2);
		p->Show(hdc);
		delete p;
	}
}

void Rect::Show(HDC hdc)
{
	Shape* p = new RectShape;
	HBRUSH hBrush, hBrushOld;

	hBrush = (HBRUSH)CreateSolidBrush(RGB(240, 230, 140));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	if (p)
	{
		p->Set(x1, y1, x2, y2);
		p->Show(hdc);
		delete p;
	}
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}

void EllipseF::Show(HDC hdc)
{
	Shape* p = new EllipseShape;

	HBRUSH hBrush, hBrushOld;

	hBrush = (HBRUSH)CreateSolidBrush(RGB(128, 128, 128));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	if (p)
	{
		p->Set(x1, y1, x2, y2);
		p->Show(hdc);
		delete p;
	}
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}

void LineOO::OnLBup(HWND hWnd)
{
	POINT pt;
	Shape* p = new LineShape;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;

	HDC hdc;
	hdc = GetDC(hWnd);

	if (p)
	{
		p->Set(x1, y1, x2, y2);
		p->Show(hdc);
		delete p;
	}

	p = new EllipseShape;
	if (p)
	{
		p->Set(x1, y1, x1 + 10, y1 + 10);
		p->Show(hdc);
		delete p;
	}

	p = new EllipseShape;

	if (p)
	{
		p->Set(x2, y2, x2 + 10, y2 + 10);
		p->Show(hdc);
		delete p;
	}
}

void LineOO::Show(HDC hdc)
{
	Shape* p = new LineShape;
	if (p)
	{
		p->Set(x1, y1, x2, y2);
		p->Show(hdc);
		delete p;
	}

	p = new EllipseShape;
	if (p)
	{
		p->Set(x1, y1, x1 + 10, y1 + 10);
		p->Show(hdc);
		delete p;
	}

	p = new EllipseShape;
	if (p)
	{
		p->Set(x2, y2, x2 + 10, y2 + 10);
		p->Show(hdc);
	}

	delete p;
}

void LineOO::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPenOld, hPen;
	HBRUSH hBrush, hBrushOld;
	Shape* p;

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;

	HDC hdc;
	hdc = GetDC(hWnd);

	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 205));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	p = new LineShape;
	if (p)
	{
		p->Set(x1, y1, x2, y2);
		p->Show(hdc);
		delete p;
	}

	p = new EllipseShape;
	if (p)
	{
		p->Set(x1, y1, x1 + 10, y1 + 10);
		p->Show(hdc);
		delete p;
	}

	p = new EllipseShape;
	if (p)
	{
		p->Set(x2, y2, x2 + 10, y2 + 10);
		p->Show(hdc);
		delete p;
	}

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void Cube::Show(HDC hdc)
{
	Shape* p = new LineShape;
	if (p)
	{
		//first rect
		p->Set(x1, y1, x2, y1);
		p->Show(hdc);

		p->Set(x1, y1, x1, y2);
		p->Show(hdc);

		p->Set(x1, y2, x2, y2);
		p->Show(hdc);

		p->Set(x2, y2, x2, y1);
		p->Show(hdc);

		//second rect
		p->Set(x1 + 30, y1 + 30, x2 + 30, y1 + 30);
		p->Show(hdc);

		p->Set(x1 + 30, y1 + 30, x1 + 30, y2 + 30);
		p->Show(hdc);

		p->Set(x1 + 30, y2 + 30, x2 + 30, y2 + 30);
		p->Show(hdc);

		p->Set(x2 + 30, y2 + 30, x2 + 30, y1 + 30);
		p->Show(hdc);

		//connections

		p->Set(x1, y1, x1 + 30, y1 + 30);
		p->Show(hdc);

		p->Set(x2, y2, x2 + 30, y2 + 30);
		p->Show(hdc);

		p->Set(x2, y1, x2 + 30, y1 + 30);
		p->Show(hdc);

		p->Set(x1, y2, x1 + 30, y2 + 30);
		p->Show(hdc);

		delete p;
	}
}

void Cube::OnLBup(HWND hWnd)
{
	POINT pt;
	Shape* p = new LineShape;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;

	HDC hdc;
	hdc = GetDC(hWnd);

	if (p)
	{
		//first rect
		p->Set(x1, y1, x2, y1);
		p->Show(hdc);

		p->Set(x1, y1, x1, y2);
		p->Show(hdc);

		p->Set(x1, y2, x2, y2);
		p->Show(hdc);

		p->Set(x2, y2, x2, y1);
		p->Show(hdc);

		//second rect
		p->Set(x1 + 30, y1 + 30, x2 + 30, y1 + 30);
		p->Show(hdc);

		p->Set(x1 + 30, y1 + 30, x1 + 30, y2 + 30);
		p->Show(hdc);

		p->Set(x1 + 30, y2 + 30, x2 + 30, y2 + 30);
		p->Show(hdc);

		p->Set(x2 + 30, y2 + 30, x2 + 30, y1 + 30);
		p->Show(hdc);

		//connections

		p->Set(x1, y1, x1 + 30, y1 + 30);
		p->Show(hdc);

		p->Set(x2, y2, x2 + 30, y2 + 30);
		p->Show(hdc);

		p->Set(x2, y1, x2 + 30, y1 + 30);
		p->Show(hdc);

		p->Set(x1, y2, x1 + 30, y2 + 30);
		p->Show(hdc);

		delete p;
	}
}

void Cube::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPenOld, hPen;
	Shape* p;

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;

	HDC hdc;
	hdc = GetDC(hWnd);

	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 205));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	p = new LineShape;

	if (p)
	{
		//first rect
		p->Set(x1, y1, x2, y1);
		p->Show(hdc);

		p->Set(x1, y1, x1, y2);
		p->Show(hdc);

		p->Set(x1, y2, x2, y2);
		p->Show(hdc);

		p->Set(x2, y2, x2, y1);
		p->Show(hdc);

		//second rect
		p->Set(x1 + 30, y1 + 30, x2 + 30, y1 + 30);
		p->Show(hdc);

		p->Set(x1 + 30, y1 + 30, x1 + 30, y2 + 30);
		p->Show(hdc);

		p->Set(x1 + 30, y2 + 30, x2 + 30, y2 + 30);
		p->Show(hdc);

		p->Set(x2 + 30, y2 + 30, x2 + 30, y1 + 30);
		p->Show(hdc);

		//connections

		p->Set(x1, y1, x1 + 30, y1 + 30);
		p->Show(hdc);

		p->Set(x2, y2, x2 + 30, y2 + 30);
		p->Show(hdc);

		p->Set(x2, y1, x2 + 30, y1 + 30);
		p->Show(hdc);

		p->Set(x1, y2, x1 + 30, y2 + 30);
		p->Show(hdc);

		delete p;
	}

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void Point::Pick(HDC hdc)
{
	Shape* p = new PointShape;
	HBRUSH hBrush, hBrushOld;
	hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	if (p)
	{
		p->Set(x1, y1, x2, y2);
		p->Show(hdc);
		delete p;
	}

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}

void Line::Pick(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(0, 1, RGB(255, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Shape* p = new LineShape;
	if (p)
	{
		p->Set(x1, y1, x2, y2);
		p->Show(hdc);
		delete p;
	}
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void Rect::Pick(HDC hdc)
{

	Shape* p = new RectShape;
	HBRUSH hBrush, hBrushOld;
	HPEN hPen, hPenOld;
	hPen = CreatePen(0, 1, RGB(255, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	hBrush = (HBRUSH)CreateSolidBrush(RGB(240, 230, 140));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	if (p)
	{
		p->Set(x1, y1, x2, y2);
		p->Show(hdc);
		delete p;
	}

	SelectObject(hdc, hPenOld);
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void EllipseF::Pick(HDC hdc)
{
	Shape* p = new EllipseShape;

	HBRUSH hBrush, hBrushOld;
	HPEN hPen, hPenOld;
	hPen = CreatePen(0, 1, RGB(255, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	hBrush = (HBRUSH)CreateSolidBrush(RGB(128, 128, 128));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	if (p)
	{
		p->Set(x1, y1, x2, y2);
		p->Show(hdc);
		delete p;
	}
	
	SelectObject(hdc, hPenOld);
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void LineOO::Pick(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(0, 1, RGB(255, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Shape* p = new LineShape;
	if (p)
	{
		p->Set(x1, y1, x2, y2);
		p->Show(hdc);
		delete p;
	}

	p = new EllipseShape;
	if (p)
	{
		p->Set(x1, y1, x1 + 10, y1 + 10);
		p->Show(hdc);
		delete p;
	}

	p = new EllipseShape;
	if (p)
	{
		p->Set(x2, y2, x2 + 10, y2 + 10);
		p->Show(hdc);
	}

	delete p;

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void Cube::Pick(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(0, 1, RGB(255, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	Shape* p = new LineShape;
	if (p)
	{
		//first rect
		p->Set(x1, y1, x2, y1);
		p->Show(hdc);

		p->Set(x1, y1, x1, y2);
		p->Show(hdc);

		p->Set(x1, y2, x2, y2);
		p->Show(hdc);

		p->Set(x2, y2, x2, y1);
		p->Show(hdc);

		//second rect
		p->Set(x1 + 30, y1 + 30, x2 + 30, y1 + 30);
		p->Show(hdc);

		p->Set(x1 + 30, y1 + 30, x1 + 30, y2 + 30);
		p->Show(hdc);

		p->Set(x1 + 30, y2 + 30, x2 + 30, y2 + 30);
		p->Show(hdc);

		p->Set(x2 + 30, y2 + 30, x2 + 30, y1 + 30);
		p->Show(hdc);

		//connections

		p->Set(x1, y1, x1 + 30, y1 + 30);
		p->Show(hdc);

		p->Set(x2, y2, x2 + 30, y2 + 30);
		p->Show(hdc);

		p->Set(x2, y1, x2 + 30, y1 + 30);
		p->Show(hdc);

		p->Set(x1, y2, x1 + 30, y2 + 30);
		p->Show(hdc);

		delete p;
	}

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}
