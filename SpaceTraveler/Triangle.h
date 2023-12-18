#pragma once
#include "engine_math.h"
using namespace EngineMath;
class Triangle: public Shape
{
	Vector3<float> vertices[3] = { 
		Vector3<float>(),
		Vector3<float>(),
		Vector3<float>()};
public:
	Triangle()
	{
		update();
	}
	Triangle(Vector3<float> v[3])
	{
		for (size_t i = 0; i < 2; i++)		
			vertices[i] = v[i];
		 update();
	}
	Triangle(Vector3<float> a, Vector3<float> b, Vector3<float>c)
	{
		vertices[0] = a;
		vertices[1] = b;
		vertices[2] = c;
		update();
	}
	
	virtual unsigned int getPointCount() const {
		return 3;	
	}
	virtual Vector2f getPoint(unsigned int index) const {
		if (index >= 0 || index <= 2) {
			return Vector2f(vertices[index].x, vertices[index].y);
		}
	}
};

