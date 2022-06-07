#include "framework.h"
#include "shape_editor.h"

ShapeEditor::~ShapeEditor()
{
	if (pe) delete pe;
	if (ps) delete ps;
	for (int i = 0; i < 105; i++)
		if (shapeList[i]) delete shapeList[i];
}

void ShapeEditor::ClearPointers()
{
	if (pe)
	{
		delete pe;
		pe = nullptr;
	}
	if (ps)
	{
		delete ps;
		ps = nullptr;
	}
}

void ShapeEditor::StartPointEditor(HWND hWnd)
{
	ClearPointers();
	pe = new PointEditor;
	ps = new PointShape;
	shape = 1;
	SetWindowTextA(hWnd, "Point");
}

void ShapeEditor::StartLineEditor(HWND hWnd)
{
	ClearPointers();
	pe = new LineEditor;
	ps = new LineShape;
	shape = 2;
	SetWindowTextA(hWnd, "Line");
}

void ShapeEditor::StartRectEditor(HWND hWnd)
{
	ClearPointers();
	pe = new RectEditor;
	ps = new RectShape;
	shape = 3;
	SetWindowTextA(hWnd, "Rectangle");
}

void ShapeEditor::StartEllipseEditor(HWND hWnd)
{
	ClearPointers();
	pe = new EllipseEditor;
	ps = new EllipseShape;
	shape = 4;
	SetWindowTextA(hWnd, "Ellipse");
}

void ShapeEditor::OnLBdown(HWND hWnd)
{
	if (pe)
	{
		pe->OnLBdown(hWnd);
		flagPaint = true;
	}
}

void ShapeEditor::OnMouseMove(HWND hWnd)
{
	
	if (flagPaint)
	{
		InvalidateRect(hWnd, 0, 1);
		OnPaint(hWnd);
		if (pe) pe->OnMouseMove(hWnd);
	}
}

void ShapeEditor::OnLBup(HWND hWnd)
{
	if (pe)
	{
		pe->OnLBup(hWnd);
		ps->Set(pe->x1, pe->y1, pe->x2, pe->y2);
		shapeList[index++] = ps;
		switch (shape)
		{
		case 1:
			ps = new PointShape;
			break;
		case 2:
			ps = new LineShape;
			break;
		case 3:
			ps = new RectShape;
			break;
		case 4:
			ps = new EllipseShape;
			break;
		default: break;
		}
		flagPaint = false;
	}
}

void ShapeEditor::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	for (int i = 0; i < 105; i++)
		if (shapeList[i]) shapeList[i]->Show(hdc);
	EndPaint(hWnd, &ps);
}
