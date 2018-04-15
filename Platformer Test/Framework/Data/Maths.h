#ifndef MATH_H
#define MATH_H

#include <math.h>

#define Pi 3.14159265358979323846264f

float Strip(float in, float factor = 100.f);

float FRound(float f);

template <class T>
bool IsOdd(T a)
{
	if ((((int)a) % 2) == 0)
		return false;
	return true;
};

template <class T>
bool IsEven(T a)
{
	return !IsOdd(a);
};

template <class T>
T Min(T a, T b)
{
	if (a <= b)
		return a;
	else
		return b;
};

template <class T>
T Max(T a, T b)
{
	if (a >= b)
		return a;
	else
		return b;
};

template <class T>
int Sign(T a)
{
	if (a < 0)
		return -1;
	if (a > 0)
		return 1;

	return 0;
};

template <class T>
T Absolute(T a)
{
	if (a < 0)
		return -a;
	return a;
};

#endif