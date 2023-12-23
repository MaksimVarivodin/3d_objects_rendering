#pragma once
#include "engine_math.h"
using namespace engine_math;
class triangle
{
	int point_indexes_[3];
	Color outline_ = Color::White;
	Color fill_ = Color(50, 50, 50);
public:
	const int& a() const { return point_indexes_[0]; }
	const int& b() const { return point_indexes_[1]; }
	const int& c() const { return point_indexes_[2]; }

	int* a_pointer() {return &point_indexes_[0];}
	int* b_pointer() {return &point_indexes_[1];}
	int* c_pointer() {return &point_indexes_[2];}

	const VertexArray & to_line_vertex_array(const vector<point> points) const ;
	void outline(const Color & color){outline_ = color;}
	void fill(const Color & color){fill_ = color;}

	const Color & outline() const {return outline_; }
	const Color & fill() const {return fill_; }

	triangle() :point_indexes_()
	{
	}

	explicit triangle(int ind[3])
	{
		point_indexes_[0] =  ind[0];
		point_indexes_[1] =  ind[1];
		point_indexes_[2] =  ind[2];

	}

	triangle(
		const int& a,
		const int& b,
		const int& c){
		point_indexes_[0] = a;
		point_indexes_[1] = b;
		point_indexes_[2] = c;

	}
	explicit triangle(
		const int& a,
		const int& b,
		const int& c,
		const Color & fill,
		const Color & outline)
	:triangle(a, b, c)
	{
		this->outline_ = outline;
		this->fill_ = fill;
	}
};



