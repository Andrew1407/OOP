#pragma once

class Editor
{
protected:
	int x1, x2, y1, y2;
	int shape;
public:
	virtual ~Editor() { }
	void OnLBdown(HWND);
	virtual void OnLBup(HWND) = 0;
	virtual void OnMouseMove(HWND) = 0;
	virtual void Show(HDC) = 0;
	virtual void Pick(HDC) = 0;
	virtual void GetShape(int&);
	void GetCoords(int*);
	void SetCoords(const int*);
};

class Point : virtual public Editor
{
public:
	Point() { shape = 0; }
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void Show(HDC);
	void Pick(HDC);
};

class Line : virtual public Editor
{
public:
	Line() { shape = 1; }
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void Show(HDC);
	void Pick(HDC);
};

class Rect : virtual public Editor
{
public:
	Rect() { shape = 2; }
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void Show(HDC);
	void Pick(HDC);
};

class EllipseF : virtual public Editor
{
public:
	EllipseF() { shape = 3; }
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void Show(HDC);
	void Pick(HDC);
};

class LineOO : public EllipseF, public Line
{
public:
	LineOO() { shape = 4; }
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void Show(HDC);
	void Pick(HDC);
};

class Cube : public Line
{
public:
	Cube() { shape = 5; }
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void Show(HDC);
	void Pick(HDC);
};
