#pragma once

#include "point.h"
using namespace engine_math;

const point& point::operator+(const point& p) const
{
	point {
		x_ + p.x_,
		y_ + p.y_,
		z_ + p.z_,
		w_ + p.w_
	};
	return p;
}

point& point::operator+=(const point& p)
{
	*this = operator+(p);
	return *this;
}

const point& point::operator-(const point& p) const
{
	return point{
		x_ - p.x_,
		y_ - p.y_,
		z_ - p.z_,
		w_ - p.w_
	};
}

point& point::operator-=(const point& p)
{
	*this = operator-(p);
	return *this;
}

const point& point::operator*(const float& value) const
{
	return point{
		x_ * value,
		y_ * value,
		z_ * value,
		w_ * value
	};
}

point& point::operator*=(const float& value)
{
	*this = operator*(value);
	return *this;
}

const point& point::operator*(const matrix& matrix) const
{
	return point{
		x_ * matrix(0, 0) + y_ * matrix(1, 0) + z_ * matrix(2, 0) + w_ * matrix(3, 0),
		x_ * matrix(0, 1) + y_ * matrix(1, 1) + z_ * matrix(2, 1) + w_ * matrix(3, 1),
		x_ * matrix(0, 2) + y_ * matrix(1, 2) + z_ * matrix(2, 2) + w_ * matrix(3, 2),
		x_ * matrix(0, 3) + y_ * matrix(1, 3) + z_ * matrix(2, 3) + w_ * matrix(3, 3)
	};
}

point& point::operator*=(const matrix& matrix)
{
	*this = operator*(matrix);
	return *this;
}

const point& point::operator*(const point& p) const
{
	return point{
		y_ * p.z_ - z_ * p.y_,
		z_ * p.x_ - x_ * p.z_,
		x_ * p.y_ - y_ * p.x_,
		1
	};
}

point& point::operator*=(const point& p)
{
	*this = operator*(p);
	return *this;
}

const point& point::operator/(const float& value) const
{
	if (value == 0.0f)
		throw exception("division by zero");
	return point{
		x_ / value,
		y_ / value,
		z_ / value,
		w_ / value
	};
}

point& point::operator/=(const float& value)
{
	*this = operator/(value);
	return *this;
}

point& point::precision(const int& precision)
{
	float temp = pow(10, precision);
	return *this = {
		round(x_ *temp) /temp,
		round(y_ *temp) /temp,
		round(z_ *temp) /temp,
		round(w_ *temp) /temp
	};
}

const point& point::vector(const point& p) const
{
	return  p.operator-(*this);
}

const point& engine_math::point::normalized_vector(const point& p) const
{
	point temp = vector(p);
	return temp.normalization();
}

const float& point::scalar(const point& p) const
{
	return	x_ * p.x_
		+	y_ * p.y_
		+	z_ * p.z_;
	
}

const float& point::modulus() const
{
	return sqrtf(
		 x_ * x_
		+	y_ * y_ 
		+	z_ * z_ 	
	);
}

point& point::normalization()
{
	const float length = modulus();
	x_ /= length;
	y_ /= length;
	z_ /= length;
	return *this;
}



