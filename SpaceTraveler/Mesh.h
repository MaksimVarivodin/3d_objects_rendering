#pragma once
#include "Triangle.h"
class Mesh
{
	vector<Triangle> trians;
public:
	vector<Triangle> getTriangles();
	Mesh() :trians() {};

	Mesh(const vector<Triangle>& tr)
	{
		trians = tr;
	};
};

