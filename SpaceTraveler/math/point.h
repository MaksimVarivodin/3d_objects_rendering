#pragma once
#include "matrix_impl.h"
template <class T>
class point : public Vector3<T>
{
	
public:
	point(
		const T & X_p,
		const T & Y_p,
		const T & Z_p):Vector3<T>(X_p, Y_p, Z_p)
	{
	}
	point (const point<T> & other ):
		point<T>(other.x, other.y, other.z){}
	point():point<T>(T(0), T(0), T(0)){}

	point<T> operator+(const T& value) const;
	point<T> operator+(const point<T>& other) const;

	point<T> operator-(const T& value) const;
	point<T> operator-(const point<T>& other) const;

	point<T> operator*(const T& value) const;
	point<T> operator/(const T& value) const;

	point<T>& operator+=(const T& value) ;
	point<T>& operator+=(const point<T>& other) ;

	point<T>& operator-=(const T& value) ;
	point<T>& operator-=(const point<T>& other) ;

	point<T>& operator*=(const T& value) ;
	point<T>& operator/=(const T& value) ;

	point<T> operator*(const matrix<T>& m) const;
	point<T>& operator*=(const matrix<T>&m);

	point<T> operator*(const point<T>& p) const;
	point<T>& operator*=(const point<T>& p);

	T vector_length();
	point<T> normalization();

	point<T> projection(
	const  T& aspect_ratio,
	const  T& fov,
	const  T& z_compression,
	const  T& z_monitor);

	Vector2<T> to_Vector2();

	void print();
	template<class U>
	static void print_vector2(const Vector2<U>&);
	static T dot_product(const point<T>& a, const point<T>& b);
	static point<T> cross_product(const point<T>& a, const point<T>& b);

	static point<T> vector(const point<T> & a, const point<T> & b);
	static point<T> normalized_vector(const point<T> & a, const point<T> & b);

};


