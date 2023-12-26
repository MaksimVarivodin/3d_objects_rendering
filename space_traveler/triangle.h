#pragma once
#include "point_impl.h"
template <class T = float>
class triangle
{
public:
	point<T> * a(){return a_;}
	point<T> * b(){return b_;}
	point<T> * c(){return c_;}

	void a(const point<T>& val_a)const {return a_ = new point<T>(a);}
	void b(const point<T>& val_b)const {return b_ = new point<T>(b);}
	void c(const point<T>& val_c)const {return c_ = new point<T>(c);}


	vector<Vertex> to_triangle();
	VertexArray to_line();


private:
	point<T> * a_;
	point<T> * b_;
	point<T> * c_;

	Color fill;
	Color outline;

public:
	triangle(
	point<T> * a,
	point<T> * b,
	point<T> * c	
	):
		a_(a),
		b_(b),
		c_(c){};

	triangle(
	point<T> * a,
	point<T> * b
	):
		triangle(a, b, nullptr){};

	triangle(
	point<T> * a
	):
		triangle(a, nullptr){};

	triangle(
	):
		triangle( nullptr){};


	~triangle()
	{
		a_ = nullptr;
		b_ = nullptr;
		c_ =  nullptr;
	}
};

