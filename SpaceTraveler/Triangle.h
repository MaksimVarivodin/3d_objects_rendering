#pragma once
#include "engine_math.h"
template <class T>
class triangle
{

	point<T>* a_ = nullptr;
	point<T>* b_ = nullptr;
	point<T>* c_ = nullptr;

	Color outline_ = Color::White;
	Color fill_ = Color(50, 50, 50);

public:
	point<T>* a(){return a_;}
	point<T>* b(){return b_;}
	point<T>* c(){return c_;}

	void a(point<T>* val){a_ = val;}
	void b(point<T>* val){b_ = val;}
	void c(point<T>* val){c_ = val;}

	void outline(const Color & color){outline_ = color;}
	void fill(const Color & color){fill_ = color;}

	const Color& outline() const {return outline_; }
	const Color& fill() const {return fill_; }


	triangle() = default;

	triangle(
		point<T>* a_, 
		point<T>* b_,
		point<T>* c_,
		const Color& outline_,
		const Color& fill_)
		: a_(a_), b_(b_), c_(c_), outline_(outline_), fill_(fill_)
	{
	}

	bool operator> (const triangle<T>& other){
		T z1 = em_find_average(a_->z, b_->z, c_->z);
		T z2 = em_find_average(other.a_->z, other.b_->z, other.c_->z);
		return z1 > z2;
	}
};



