#ifndef PAIR_H
#define PAIR_H

template <class T>
struct Pair
{
	Pair()
	{

	};
	Pair(T a, T b)
	{
		Set(a, b);
	};

	void Set(T a, T b)
	{
		_A = a;
		_B = b;
	};

	T _A;
	T _B;
};

typedef Pair<float> PairFloat;
typedef Pair<int> PairInt;

#endif