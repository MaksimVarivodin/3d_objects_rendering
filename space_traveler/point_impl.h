#pragma once

#include "point.h"
using namespace engine_math;

template <class T>
const point<T>& point<T>::operator+(const point<T>& p) const
{
	point<T> {
		x_ + p.x_,
		y_ + p.y_,
		z_ + p.z_,
		w_ + p.w_
	};
	return p;
}
template <class T>
point<T>& point<T>::operator+=(const point<T>& p)
{
	*this = operator+(p);
	return *this;
}
template <class T>
const point<T>& point<T>::operator-(const point<T>& p) const
{
	return point<T>{
		x_ - p.x_,
		y_ - p.y_,
		z_ - p.z_,
		w_ - p.w_
	};
}
template <class T>
point<T>& point<T>::operator-=(const point<T>& p)
{
	*this = operator-(p);
	return *this;
}
template <class T>
const point<T>& point<T>::operator*(const T& value) const
{
	return point<T>{
		x_ * value,
		y_ * value,
		z_ * value,
		w_ * value
	};
}
template <class T>
point<T>& point<T>::operator*=(const T& value)
{
	*this = operator*(value);
	return *this;
}
template <class T>
const point<T>& point<T>::operator*(const point<T>& p) const
{
	return point<T>{
		y_ * p.z_ - z_ * p.y_,
		z_ * p.x_ - x_ * p.z_,
		x_ * p.y_ - y_ * p.x_,
		1
	};
}
template <class T>
point<T>& point<T>::operator*=(const point<T>& p)
{
	*this = operator*(p);
	return *this;
}
template <class T>
const point<T>& point<T>::operator/(const T& value) const
{
	if (value == 0.0f)
		throw exception("division by zero");
	return point<T>{
		x_ / value,
		y_ / value,
		z_ / value,
		w_ / value
	};
}
template <class T>
point<T>& point<T>::operator/=(const T& value)
{
	*this = operator/(value);
	return *this;
}
template <class T>
point<T>& point<T>::precision(const int& precision)
{
	float temp = pow(10, precision);
	return *this = {
		round(x_ *temp) /temp,
		round(y_ *temp) /temp,
		round(z_ *temp) /temp,
		round(w_ *temp) /temp
	};
}
template <class T>
const point<T>& point<T>::vector(const point<T>& p) const
{
	return  p.operator-(*this);
}
template <class T>
const point<T>& engine_math::point<T>::normalized_vector(const point<T>& p) const
{
	point<T> temp = vector(p);
	return temp.normalization();
}
template <class T>
const T& point<T>::scalar(const point<T>& p) const
{
	return	x_ * p.x_
		+	y_ * p.y_
		+	z_ * p.z_;
	
}
template <class T>
const T& point<T>::modulus() const
{
	return sqrtf(
		 x_ * x_
		+	y_ * y_ 
		+	z_ * z_ 	
	);
}
template <class T>
point<T>& point<T>::normalization()
{
	const float length = modulus();
	x_ /= length;
	y_ /= length;
	z_ /= length;
	return *this;
}



