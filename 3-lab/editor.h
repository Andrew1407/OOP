#pragma once

class Editor
{
public:
	int x1, x2, y1, y2;
	void OnLBdown(HWND);
	virtual void OnLBup(HWND) = 0;
	virtual void OnMouseMove(HWND) = 0;
};

class PointEditor : public Editor
{
	void OnLBup(HWND);
	void OnMouseMove(HWND);
};

class LineEditor : public Editor
{
	void OnLBup(HWND);
	void OnMouseMove(HWND);
};

class RectEditor : public Editor
{
	void OnLBup(HWND);
	void OnMouseMove(HWND);
};

class EllipseEditor : public Editor
{
	void OnLBup(HWND);
	void OnMouseMove(HWND);
};
