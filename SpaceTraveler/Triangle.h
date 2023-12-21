#pragma once
#include "engine_math.h"
using namespace engine_math;
class triangle
{
	int point_indexes_[3];
public:
	const int& a() const { return point_indexes_[0]; }
	const int& b() const { return point_indexes_[1]; }
	const int& c() const { return point_indexes_[2]; }
	
	triangle() :point_indexes_()
	{
	};

	explicit triangle(int ind[3])
	{
		point_indexes_[0] =  ind[0];
		point_indexes_[1] =  ind[1];
		point_indexes_[2] =  ind[2];
	}
	triangle(
		const int& a,
		const int& b,
		const int& c) {
		point_indexes_[0] = a;
		point_indexes_[1] = b;
		point_indexes_[2] = c;
	}

	[[nodiscard]] VertexArray to_triangle_vertex_array(const vector<Vector3f>& points, const Color& fill_color) const;
	[[nodiscard]] VertexArray to_line_vertex_array(const vector<Vector3f>& points, const Color& outline_color) const;
};



