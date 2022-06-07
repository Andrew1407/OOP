#pragma once
#include "editor.h"

class MyEditor
{
private:
	Editor** shapeList = new Editor* [106];
	int index = 0, shape;
	Editor* ps = nullptr;
	bool flagPaint = false;
	int checked[6] = { MF_UNCHECKED , MF_UNCHECKED , MF_UNCHECKED , MF_UNCHECKED, MF_UNCHECKED, MF_UNCHECKED };
	void Check(int);
public:
	~MyEditor();
	void Start(Editor*);
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HDC);
	void OnInitMenuPopup(HWND, WPARAM);
};
