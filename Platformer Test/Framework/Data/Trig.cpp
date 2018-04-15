#include "Trig.h"

//	Vector

Vec::Vec() :Vec(0.f, 0.f)
{

};

Vec::Vec(float x, float y)
{
	_X = x;
	_Y = y;
};

Vec::Vec(PairFloat p) : Vec(p._A, p._B)
{

};

Vec::Vec(Point p) : Vec((float)p.GetX(), (float)p.GetY())
{

};

Vec Vec::UnitVec()
{
	return Vec(_X, _Y) / Length();
};
float Vec::Length()
{
	return sqrtf((_X * _X) + (_Y * _Y));
};
Vec Vec::Normal()
{
	return Vec(-_Y, _X);
};

float Vec::DotProduct(Vec v2)
{
	return (_X * v2._X) + (_Y * v2._Y);
};

Vec Vec::operator+(const Vec& v)
{
	return Vec(_X + v._X, _Y + v._Y);
};
Vec Vec::operator-(const Vec& v)
{
	return Vec(_X - v._X, _Y - v._Y);
};
Vec Vec::operator*(const int& i)
{
	return Vec(_X * (float)i, _Y * (float)i);
};
Vec Vec::operator*(const float& f)
{
	return Vec(_X * f, _Y * f);
};
Vec Vec::operator*(const Vec& v)
{
	return Vec(_X * v._X, _Y * v._Y);
};
Vec Vec::operator/(const int& i)
{
	return Vec(_X / (float)i, _Y / (float)i);
};
Vec Vec::operator/(const float& f)
{
	return Vec(_X / f, _Y / f);
};
Vec Vec::operator/(const Vec& v)
{
	return Vec(_X / v._X, _Y / v._Y);
};
void Vec::operator+=(const Vec& v)
{
	_X += v._X;
	_Y += v._Y;
};
void Vec::operator-=(const Vec& v)
{
	_X -= v._X;
	_Y -= v._Y;
};
void Vec::operator*=(const int& i)
{
	_X *= (float)i;
	_Y *= (float)i;
};
void Vec::operator*=(const float& f)
{
	_X *= f;
	_Y *= f;
};
void Vec::operator*=(const Vec& v)
{
	_X *= v._X;
	_Y *= v._Y;
};
void Vec::operator/=(const int& i)
{
	_X /= (float)i;
	_Y /= (float)i;
};
void Vec::operator/=(const float& f)
{
	_X /= f;
	_Y /= f;
};
void Vec::operator/=(const Vec& v)
{
	_X /= v._X;
	_Y /= v._Y;
};
bool Vec::operator==(const Vec& v)
{
	return ((_X == v._X) && (_Y == v._Y));
};

//	Point
//	Constructors/Deconstructor

Point::Point()
{
	Set(0, 0);
};
Point::Point(int x, int y)
{
	Set(x, y);
};
Point::Point(float x, float y)
{
	Set(x, y);
};
Point::Point(Vec v)
{
	Set(v._X, v._Y);
};

//	Get/Set

int Point::GetX()
{
	return (int)floorf(_Coords._A);
};
int Point::GetY()
{
	return (int)floorf(_Coords._B);
};
PairInt Point::Get()
{
	return PairInt((int)_Coords._A, (int)_Coords._B);
};
void Point::SetX(int x)
{
	_Coords._A = (float)x;
};
void Point::SetX(float x)
{
	_Coords._A = x;
};
void Point::SetY(int y)
{
	_Coords._B = (float)y;
};
void Point::SetY(float y)
{
	_Coords._B = y;
};
void Point::Set(int x, int y)
{
	SetX(x);
	SetY(y);
};
void Point::Set(float x, float y)
{
	SetX(x);
	SetY(y);
};

void Point::Round()
{
	_Coords._A = floorf(_Coords._A);
	_Coords._B = floorf(_Coords._B);
};

//	Operators

Point Point::operator+(const Point& p)
{
	return Point(_Coords._A + p._Coords._A, _Coords._B + p._Coords._B);
};
Point Point::operator-(const Point& p)
{
	return Point(_Coords._A - p._Coords._A, _Coords._B - p._Coords._B);
};
Point Point::operator*(const int& i)
{
	return Point(_Coords._A * (float)i, _Coords._B * (float)i);
};
Point Point::operator*(const float& f)
{
	return Point(_Coords._A * f, _Coords._B * f);
};
Point Point::operator*(const Point& p)
{
	return Point(_Coords._A * p._Coords._A, _Coords._B * p._Coords._B);
};
Point Point::operator/(const int& i)
{
	return Point(_Coords._A / (float)i, _Coords._B / (float)i);
};
Point Point::operator/(const float& f)
{
	return Point(_Coords._A / f, _Coords._B / f);
};
Point Point::operator/(const Point& p)
{
	return Point(_Coords._A / p._Coords._A, _Coords._B / p._Coords._B);
};
void Point::operator+=(const Point& p)
{
	_Coords.Set(_Coords._A + p._Coords._A, _Coords._B + p._Coords._B);
};
void Point::operator+=(const Vec& v)
{
	_Coords.Set(_Coords._A + v._X, _Coords._B + v._Y);
};
void Point::operator-=(const Point& p)
{
	_Coords.Set(_Coords._A - p._Coords._A, _Coords._B - p._Coords._B);
};
void Point::operator-=(const Vec& v)
{
	_Coords.Set(_Coords._A - v._X, _Coords._B - v._Y);
};
void Point::operator*=(const int& i)
{
	_Coords.Set(_Coords._A * (float)i, _Coords._B * (float)i);
};
void Point::operator*=(const float& f)
{
	_Coords.Set(_Coords._A * f, _Coords._B * f);
};
void Point::operator*=(const Point& p)
{
	_Coords.Set(_Coords._A * p._Coords._A, _Coords._B * p._Coords._B);
};
void Point::operator/=(const int& i)
{
	_Coords.Set(_Coords._A / (float)i, _Coords._B / (float)i);
};
void Point::operator/=(const float& f)
{
	_Coords.Set(_Coords._A / f, _Coords._B / f);
};
void Point::operator/=(const Point& p)
{
	_Coords.Set(_Coords._A / p._Coords._A, _Coords._B / p._Coords._B);
};

bool Point::operator==(Point& p)
{
	return (GetX() == p.GetX()) && (GetY() == p.GetY());
};

//	Angle/Heading Stuff
float DegreeToRad(float d)
{
	return d * Pi / 180.f;
};

float RadToDegree(float r)
{
	return r * 180.f / Pi;
};

float CalcAngle(float startx, float starty, float endx, float endy)
{
	return (float)atan2(endy - starty, endx - startx);
};

float CalcAngle(int startx, int starty, int endx, int endy)
{
	return CalcAngle((float)startx, (float)starty, (float)endx, (float)endy);
};

float CalcAngle(float dx, float dy)
{
	return CalcAngle(0.f, 0.f, dx, dy);
};

float CalcAngle(int dx, int dy)
{
	return CalcAngle((float)dx, (float)dy);
};

float CalcHeading(float startx, float starty, float endx, float endy)
{
	float result = CalcAngle(startx, starty, endx, endy) + (Pi / 2.f);
	if (result < 0.f) result += (Pi * 2.f);
	return result;
};

float CalcHeading(int startx, int starty, int endx, int endy)
{
	return CalcHeading((float)startx, (float)starty, (float)endx, (float)endy);
};

float CalcHeading(float dx, float dy)
{
	return CalcHeading(0.f, 0.f, dx, dy);
};

float CalcHeading(int dx, int dy)
{
	return CalcHeading((float)dx, (float) dy);
};

float CalcSFMLAngle(float startx, float starty, float endx, float endy)
{
	return RadToDegree(CalcAngle(startx, starty, endx, endy));
};
float CalcSFMLAngle(int startx, int starty, int endx, int endy)
{
	return CalcSFMLAngle((float)startx, (float)starty, (float)endx, (float)endy);
};
float CalcSFMLAngle(float dx, float dy)
{
	return CalcSFMLAngle(0.f, 0.f, dx, dy);
};
float CalcSFMLAngle(int dx, int dy)
{
	return CalcSFMLAngle((float)dx, (float)dy);
};

float CalcXComp(float heading)
{
	return sinf(heading);
};

float CalcYComp(float heading)
{
	return cosf(heading - Pi);
};

float CalcDistance(float x1, float y1, float x2, float y2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	return sqrtf((dx * dx) + (dy * dy));
};

float CalcDistance(float dx, float dy)
{
	return CalcDistance(0.f, 0.f, dx, dy);
};

float CalcDistance(int x1, int y1, int x2, int y2)
{
	return CalcDistance((float)x1, (float)y1, (float)x2, (float)y2);
};

float CalcDistance(int dx, int dy)
{
	return CalcDistance((float)dx, (float)dy);
};
