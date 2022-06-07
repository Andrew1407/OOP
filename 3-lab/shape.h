#pragma once

class Shape {
protected:
	int x1, x2, y1, y2;
public:
	void Set(int, int, int, int);
	virtual void Show(HDC) = 0;
};

class PointShape : public Shape
{
public:
	void Show(HDC);
};

class LineShape : public Shape
{
public:
	void Show(HDC);
};

class RectShape : public Shape
{
public:
	void Show(HDC);
};

class EllipseShape : public Shape
{
public:
	void Show(HDC);
};
