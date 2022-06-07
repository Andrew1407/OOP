#include "framework.h"
#include "resource.h"
#include "shape.h"
#include "my_editor.h"

static const char* ShapesTypes[6]  = { "Точка", "Лінія", "Прямокутник", "Еліпс", "Лінія з кружечками", "Куб" };

MyEditor& MyEditor::GetInstance()
{
	static MyEditor instance;
	return instance;
}

MyEditor::~MyEditor()
{
	for (int i = 0; i < index; i++)
		if (shapeList[i]) delete shapeList[i];
	if (shapeList) delete[] shapeList;
}

void MyEditor::Check(int index)
{
	for (int i = 0; i < 6; checked[i++] = MF_UNCHECKED);
	checked[index] = MF_CHECKED;
}

void MyEditor::Start(Editor* ps)
{
	this->ps = ps;
	ps->GetShape(shape);
	shapeName = ShapesTypes[shape];
	Check(shape);
}

void MyEditor::OnLBdown(HWND hWnd)
{
	if (ps)
	{
		ps->OnLBdown(hWnd);
		flagPaint = true;
	}
}

void MyEditor::OnMouseMove(HWND hWnd)
{

	if (flagPaint)
	{
		InvalidateRect(hWnd, 0, 1);
		PAINTSTRUCT _ps;
		HDC hdc = BeginPaint(hWnd, &_ps);
		OnPaint(hdc);
		if (ps) ps->OnMouseMove(hWnd);
	}

}

void MyEditor::OnLBup(HWND hWnd)
{
	if (ps)
	{
		ps->OnLBup(hWnd);
		shapeList[index++] = ps;
		ps->GetCoords(coords);
		switch (shape)
		{
		case 0:
		{
			coords[2] = -1;
			coords[3] = -1;
			Start(new Point);
		}
			break;
		case 1:
			Start(new Line);
			break;
		case 2:
			Start(new Rect);
			break;
		case 3:
			Start(new EllipseF);
			break;
		case 4:
			Start(new LineOO);
			break;
		case 5:
			Start(new Cube);
			break;
		default: break;
		}
		flagPaint = false;
	}
}

void MyEditor::OnPaint(HDC hdc)
{
	for (int i = 0; i < index; i++)
		if (shapeList[i])
		{
			(i == pick_index) ? shapeList[i]->Pick(hdc) : shapeList[i]->Show(hdc);
		}
}

void MyEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam)
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
		CheckMenuItem(hSubMenu, IDM_OOLINE, checked[4]);
		CheckMenuItem(hSubMenu, IDM_CUBE, checked[5]);
	}
}

void MyEditor::CleanArea(HWND hWnd)
{
	if (!index) return;
	InvalidateRect(hWnd, 0, 1);
	for (int i = 0; i < index; i++)
	{
		if (shapeList[i])
		{
			if (shapeList[i]) delete shapeList[i];
			shapeList[i] = nullptr;
		}
		index = 0;
	}
}

const char* MyEditor::GetShapeName() { return shapeName; }
const int* MyEditor::GetCoords() { return coords; }

void MyEditor::DeleteShape(HWND hWnd, const int pos)
{
	if (index == 0) return;
	delete shapeList[pos];
	for (int i = pos + 1; i < index; i++)
	{
		shapeList[i - 1] = shapeList[i];
	}
	shapeList[index--] = nullptr;

	InvalidateRect(hWnd, 0, 1);
}

void MyEditor::pickShape(HDC hdc, const int idx) 
{ 
	pick_index = idx;
}
