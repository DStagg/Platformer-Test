#ifndef TRIG_H
#define TRIG_H

#include "Maths.h"
#include "Pair.h"

class Point;

class Vec
{
public:

	Vec();
	Vec(float x, float y);
	Vec(PairFloat p);
	Vec(Point p);

	Vec UnitVec();
	float Length();
	Vec Normal();						//	Returns the left-hand normal (-input._Y, input._X)
	float DotProduct(Vec v2);			//	Returns the dot product of two vectors (v1._X * v2._X) + (v1._Y * v2._Y)

	Vec operator+(const Vec& v);
	Vec operator-(const Vec& v);
	Vec operator*(const int& i);
	Vec operator*(const float& f);
	Vec operator*(const Vec& v);
	Vec operator/(const int& i);
	Vec operator/(const float& f);
	Vec operator/(const Vec& v);
	void operator+=(const Vec& v);
	void operator-=(const Vec& v);
	void operator*=(const int& i);
	void operator*=(const float& f);
	void operator*=(const Vec& v);
	void operator/=(const int& i);
	void operator/=(const float& f);
	void operator/=(const Vec& v);

	bool operator==(const Vec& v);

	float _X, _Y;

};

class Point
{
public:

	Point();
	Point(int x, int y);
	Point(float x, float y);
	Point(Vec v);

	int GetX();
	int GetY();
	PairInt Get();
	void SetX(int x);
	void SetX(float x);
	void SetY(int y);
	void SetY(float y);
	void Set(int x, int y);
	void Set(float x, float y);

	void Round();

	Point operator+(const Point& p);
	Point operator-(const Point& p);
	Point operator*(const int& i);
	Point operator*(const float& f);
	Point operator*(const Point& p);
	Point operator/(const int& i);
	Point operator/(const float& f);
	Point operator/(const Point& p);
	void operator+=(const Point& p);
	void operator+=(const Vec& v);
	void operator-=(const Point& p);
	void operator-=(const Vec& v);
	void operator*=(const int& i);
	void operator*=(const float& f);
	void operator*=(const Point& p);
	void operator/=(const int& i);
	void operator/=(const float& f);
	void operator/=(const Point& p);

	bool operator==(Point& p);

protected:

	PairFloat _Coords;
};

float DegreeToRad(float d);
float RadToDegree(float r);

float CalcAngle(float startx, float starty, float endx, float endy);
float CalcAngle(int startx, int starty, int endx, int endy);
float CalcAngle(float dx, float dy);
float CalcAngle(int dx, int dy);
//	Returns the angle between a vector and the x-axis in radians
//	Right is 0, Down is Pi/2, Left is Pi, Up is -Pi/2
//	Top half of semicircle is -Pi to 0, Bottom half is Pi to 0 (both left to right)

float CalcHeading(float startx, float starty, float endx, float endy);
float CalcHeading(int startx, int starty, int endx, int endy);
float CalcHeading(float dx, float dy);
float CalcHeading(int dx, int dy);
//	Returns the heading of a vector relative to the y-axis in radians
//	Right is 1.5 Pi, Down is Pi, Right is 0.f Pi, Up is 0

float CalcSFMLAngle(float startx, float starty, float endx, float endy);
float CalcSFMLAngle(int startx, int starty, int endx, int endy);
float CalcSFMLAngle(float dx, float dy);
float CalcSFMLAngle(int dx, int dy);
//	Up is 0, Right is 90, Down is 180, Left is 270
//	Just returns CalcHeading()

float CalcXComp(float heading);
//	Calculates the x-axis component of a given heading (i.e. sin(heading))

float CalcYComp(float heading);
//	Calculates the y-axis component of a given heading (i.e. cos(heading))
//	Offset by Pi/2 (90deg) to work.

float CalcDistance(float x1, float y1, float x2, float y2);
float CalcDistance(float dx, float dy);
float CalcDistance(int x1, int y1, int x2, int y2);
float CalcDistance(int dx, int dy);
//	Calculates the distance between two points. Always positive.

#endif