#pragma once
#include "triangle.h"
template <class T>
class light
{
public:
	point<T> direction;



	light(const point<T>& direction)
		: direction(direction)
	{
	}
};

