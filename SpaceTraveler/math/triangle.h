#pragma once
#include "engine_math.h"
template <class T>
class triangle
{

	point<T>* a_ = nullptr;
	point<T>* b_ = nullptr;
	point<T>* c_ = nullptr;

	size_t a_index_ = 0;
	size_t b_index_ = 0;
	size_t c_index_ = 0;

	Color outline_ = Color::White;
	Color fill_ = Color(150, 150, 150);

public:
	point<T>* a() { return a_; }
	point<T>* b() { return b_; }
	point<T>* c() { return c_; }

	size_t a_index() { return a_index_; }
	size_t b_index() { return b_index_; }
	size_t c_index() { return c_index_; }

	void a(point<T>* val) { a_ = val; }
	void b(point<T>* val) { b_ = val; }
	void c(point<T>* val) { c_ = val; }

	void a_index(size_t a_ind) { a_index_ = a_ind; }
	void b_index(size_t b_ind) { b_index_ = b_ind; }
	void c_index(size_t c_ind) { c_index_ = c_ind; }


	void outline(const Color& color) { outline_ = color; }
	void fill(const Color& color) { fill_ = color; }

	const Color& outline() const { return outline_; }
	const Color& fill() const { return fill_; }


	point<T> normal(){
		point<T> v_a = point<T>::vector(*a_, *b_);
		point<T> v_b = point<T>::vector(*a_, *c_);
		point<T> normal = point<T>::cross_product(v_a, v_b);
		return normal.normalization();
	}

	point<T> distance(const point<T>& p){
		return point<T>::vector(*a_, p);
	}

	triangle() = default;

	triangle(
		point<T>* a,
		point<T>* b,
		point<T>* c,
		size_t a_ind,
		size_t b_ind,
		size_t c_ind,
		const Color& outline_,
		const Color& fill_)
		: a_(a), b_(b), c_(c),
		a_index_(a_ind),
		b_index_(b_ind),
		c_index_(c_ind),
		outline_(outline_), fill_(fill_)
	{
	}
	triangle(
		point<T>* a,
		point<T>* b,
		point<T>* c,
		size_t a_ind,
		size_t b_ind,
		size_t c_ind)
		: a_(a), b_(b), c_(c),
		a_index_(a_ind),
		b_index_(b_ind),
		c_index_(c_ind)
	{
	}

	bool operator> (const triangle<T>& other) {
		T z1 = em_find_average<T>(a_->z, b_->z, c_->z);
		T z2 = em_find_average<T>(other.a_->z, other.b_->z, other.c_->z);
		return z1 > z2;
	}

	static triangle<T> copy(const triangle<T>& read, const vector<point<T>*> points) {
		return triangle<T>{
			points[read.a_index_],
				points[read.b_index_],
				points[read.c_index_],
				read.a_index_,
				read.b_index_,
				read.c_index_,
				read.outline_,
				read.fill_
		};
	}
	
};



