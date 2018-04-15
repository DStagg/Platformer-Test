#include "Shapes.h"

//	Circles

Circle::Circle() : Circle(0, 0, 1)
{

};

Circle::Circle(int x, int y, int r)
{
	_X = x;
	_Y = y;
	_Radius = r;
};

bool Circle::Contains(int x, int y)
{
	int dX = x - _X;
	int dY = y - _Y;
	return (int)sqrtf(((float)dX * (float)dX) + ((float)dY * (float)dY)) <= _Radius;
}

bool Circle::Contains(Point p)
{
	return Contains(p.GetX(), p.GetY());
};

bool Circle::Intersects(Circle c)
{
	int dX = c._X - _X;
	int dY = c._Y - _Y;
	return (int)sqrtf(((float)dX * (float)dX) + ((float)dY * (float)dY)) <= _Radius + c._Radius;
};

//	AABBs

AABB::AABB()
{
	_X = 0;
	_Y = 0;
	_Width = 1;
	_Height = 1;
}

AABB::AABB(int x, int y, int w, int h)
{
	_X = x;
	_Y = y;
	_Width = w;
	_Height = h;
};

int AABB::Top()
{
	return _Y;
};
int AABB::Bottom()
{
	return _Y + _Height - 1;
};
int AABB::Left()
{
	return _X;
};
int AABB::Right()
{
	return _X + _Width - 1;
};

bool AABB::Contains(int x, int y)
{
	if ((x < _X) || (x > Right()))
		return false;
	if ((y < _Y) || (y > Bottom()))
		return false;
	return true;
};

bool AABB::Contains(Point p)
{
	return Contains(p.GetX(), p.GetY());
};

bool AABB::Intersects(AABB box)
{
	if (box.Right() < _X)
		return false;
	if (box._X > Right())
		return false;
	if (box.Bottom() < _Y)
		return false;
	if (box._Y > Bottom())
		return false;
	return true;
};