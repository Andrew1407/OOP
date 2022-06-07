#include "framework.h"
#include "resource.h"
#include "shape_editor.h"

ShapeEditor::ShapeEditor()
{
	shapeList = new Shape*[106];
	for (int i = 0; i < 106; shapeList[i++] = nullptr);
}

ShapeEditor::~ShapeEditor()
{
	if (pe) delete pe;
	if (ps) delete ps;
	for (int i = 0; i < 106; i++)
		if (shapeList[i]) delete shapeList[i];
	delete[] shapeList;
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

void ShapeEditor::Check(int index)
{
	for (int i = 0; i < 4; checked[i++] = MF_UNCHECKED);
	checked[index] = MF_CHECKED;
}

void ShapeEditor::StartPointEditor(HWND hWnd)
{
	ClearPointers();
	pe = new PointEditor;
	ps = new PointShape;
	shape = 0;
	Check(shape);
}

void ShapeEditor::StartLineEditor(HWND hWnd)
{
	ClearPointers();
	pe = new LineEditor;
	ps = new LineShape;
	shape = 1;
	Check(shape);
}

void ShapeEditor::StartRectEditor(HWND hWnd)
{
	ClearPointers();
	pe = new RectEditor;
	ps = new RectShape;
	shape = 2;
	Check(shape);
}

void ShapeEditor::StartEllipseEditor(HWND hWnd)
{
	ClearPointers();
	pe = new EllipseEditor;
	ps = new EllipseShape;
	shape = 3;
	Check(shape);
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
		case 0:
			ps = new PointShape;
			break;
		case 1:
			ps = new LineShape;
			break;
		case 2:
			ps = new RectShape;
			break;
		case 3:
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
	for (int i = 0; i < 106; i++)
		if (shapeList[i]) shapeList[i]->Show(hdc);
	EndPaint(hWnd, &ps);
}

void ShapeEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam)
{
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1); 
	if ((HMENU)wParam == hSubMenu)
	{
		CheckMenuItem(hSubMenu, IDM_POINT, checked[0]); 
		CheckMenuItem(hSubMenu, IDM_LINE, checked[1]);
		CheckMenuItem(hSubMenu, IDM_RECT, checked[2]);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, checked[3]); 
	}
}
