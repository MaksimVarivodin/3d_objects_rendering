#include "engine_math.h"

int EngineMath::findMaximum(const int& a, const int& b, const int& c)
{
	//cout << "Biggest ->";
	if (a > c) {
		if (a >= b) {
			//cout << a<< endl;
			return a;
		}
		//cout << b << endl;
		return b;
	}
	else if (b > c) {
		//cout << b << endl;
		return b;
	}
	//cout << c << endl;
	return c;
}

int EngineMath::findMinimum(const int& a, const int& b, const int& c)
{
	//cout << "Smallest->";
	if (b < a) {
		if (b <= c) {
			//cout << b << endl;
			return b;
		}
		//cout << c << endl;
		return c;
	}
	else if (c < a) {
		//cout << c << endl;
		return c;
	}
	//cout << a << endl;
	return a;
}

int EngineMath::findAverage(const int& a, const int& b, const int& c)
{
	//cout << "Average-> " << (a + b + c) / 3 << endl;
	return (a + b + c) / 3;
}
