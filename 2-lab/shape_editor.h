#pragma once
#include "editor.h"
#include "shape.h"

class ShapeEditor
{
private:
	Editor* pe = nullptr;
	Shape* shapeList[105];
	int index = 0, shape;
	Shape* ps = nullptr;
	bool flagPaint = false;
	void ClearPointers();
public:
	~ShapeEditor();
	void StartPointEditor(HWND);
	void StartLineEditor(HWND);
	void StartRectEditor(HWND);
	void StartEllipseEditor(HWND);
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
};
