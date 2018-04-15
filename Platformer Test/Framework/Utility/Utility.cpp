#include "Utility.h"

std::string IntToString(int i)
{

	std::stringstream out;
	out << i;
	return out.str();

};


std::string FloatToString(float f)
{

	std::stringstream out;
	out << f;
	return out.str();

};

int StringToInt(std::string s)
{
	int temp;
	std::stringstream(s) >> temp;

	return temp;
};

float StringToFloat(std::string s)
{
	float temp;
	std::stringstream(s) >> temp;

	return temp;
};