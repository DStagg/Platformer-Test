#ifndef SHAPES_H
#define SHAPES_H

#include "Trig.h"

class Circle
{
public:

	Circle();
	Circle(int x, int y, int r);

	bool Contains(int x, int y);
	bool Contains(Point p);
	bool Intersects(Circle c);

	int _X, _Y, _Radius;
};

class AABB
{
public:

	AABB();
	AABB(int x, int y, int w, int h);	//	Defines an axis-aligned bounding box with top-left (x,y) and dimensions (w,h)

	int Left();
	int Right();
	int Top();
	int Bottom();

	int _X, _Y, _Width, _Height;

	bool Contains(int x, int y);
	bool Contains(Point p);
	bool Intersects(AABB box);
};


#endif