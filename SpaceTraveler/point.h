#pragma once
#include "matrix_impl.h"
template <class T>
class point : public Vector3<T>
{
	
public:
	T w;
	point(
		const T & X_p,
		const T & Y_p,
		const T & Z_p,
		const T & W_p):Vector3<T>(X_p, Y_p, Z_p)
	{
		w = W_p;
	}
	point(
		const T & X_p,
		const T & Y_p,
		const T & Z_p):point<T>(X_p, Y_p, Z_p, T(0))
	{
	}
	point (const point<T> & other ):
		point<T>(other.x, other.y, other.z, other.w){}
	point():point<T>(T(0), T(0), T(0), T(0)){}

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

	T vector_length();
	point<T> normalization();


	static T dot_product(const point<T>& a, const point<T>& b);
	static point<T> cross_product(const point<T>& a, const point<T>& b);

	static point<T> vector(const point<T> & a, const point<T> & b);
	static point<T> normalized_vector(const point<T> & a, const point<T> & b);
};
