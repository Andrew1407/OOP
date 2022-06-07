#pragma once

class Shape {
protected:
	int x1, x2, y1, y2;
public:
	virtual ~Shape() { }
	void Set(int, int, int, int);
	virtual void Show(HDC) = 0;
};

class PointShape : virtual public Shape
{
public:
	void Show(HDC);
};

class LineShape : virtual public Shape
{
public:
	void Show(HDC);
};

class RectShape : virtual public Shape
{
public:
	void Show(HDC);
};

class EllipseShape : virtual public Shape
{
public:
	void Show(HDC);
};

class LineOOShape : public EllipseShape, public LineShape
{
public:
	void Show(HDC);
};

class CubeShape : public LineShape
{
public:
	void Show(HDC);
};
