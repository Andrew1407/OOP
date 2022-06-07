#pragma once
#include "editor.h"

class MyEditor
{
private:
	MyEditor() { }
	Editor** shapeList = new Editor * [106];
	int index = 0, shape;
	Editor* ps = nullptr;
	bool flagPaint = false;
	int checked[6] = { MF_UNCHECKED , MF_UNCHECKED , MF_UNCHECKED , MF_UNCHECKED, MF_UNCHECKED, MF_UNCHECKED };
	void Check(int);
	const char* shapeName;
	int coords[4] = {0, 0, 0, 0};
	int pick_index = -1;
public:
	static MyEditor& GetInstance();
	~MyEditor();
	void Start(Editor*);
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HDC);
	void OnInitMenuPopup(HWND, WPARAM);
	void CleanArea(HWND);
	const char* GetShapeName();
	const int* GetCoords();
	void DeleteShape(HWND, const int);
	void pickShape(HDC, const int);
};
