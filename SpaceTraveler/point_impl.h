#include "point.h"
template<class T>
inline point<T> point<T>::operator+(const T & value) const
{
	return point<T>{
		this->x+ value,
		this->y+ value,
		this->z+ value,
		w + value
	};
}

template<class T>
inline point<T> point<T>::operator+(const point<T>& other) const
{
	return point<T>{
		this->x+ other.x,
		this->y+ other.y,
		this->z+ other.z,
		w + other.w
	};
}

template<class T>
inline point<T> point<T>::operator-(const T& value) const
{
	return point<T>{
		this->x- value,
		this->y- value,
		this->z- value,
		w - value
	};
}

template<class T>
inline point<T> point<T>::operator-(const point<T>& other) const
{
	return point<T>{
		this->x- other.x,
		this->y- other.y,
		this->z- other.z,
		w - other.w
	};
}

template<class T>
inline point<T> point<T>::operator*(const T& value) const
{
	return point<T>{
		this->x* value,
		this->y* value,
		this->z* value,
		w * value
	};
}

template<class T>
inline point<T> point<T>::operator/(const T& value) const
{
	return point<T>{
		this->x/ value,
		this->y/ value,
		this->z/ value,
		w / value
	};
}

template<class T>
inline point<T>& point<T>::operator+=(const T& value)
{
	this->x+= value;
	this->y+= value;
	this->z+= value;
	w += value;
	return * this;
}

template<class T>
inline point<T>& point<T>::operator+=(const point<T>& other)
{
	this->x+= other.x;
	this->y+= other.y;
	this->z+= other.z;
	w += other.w;

	return * this;
}

template<class T>
inline point<T>& point<T>::operator-=(const T& value)
{
	this->x-= value;
	this->y-= value;
	this->z-= value;
	w -= value;
	return * this;
}

template<class T>
inline point<T>& point<T>::operator-=(const point<T>& other)
{
	this->x-= other.x;
	this->y-= other.y;
	this->z-= other.z;
	w -= other.w;

	return * this;
}

template<class T>
inline point<T>& point<T>::operator*=(const T& value)
{
	this->x*= value;
	this->y*= value;
	this->z*= value;
	w *= value;
	return * this;

}

template<class T>
inline point<T>& point<T>::operator/=(const T& value)
{
	this->x/= value;
	this->y/= value;
	this->z/= value;
	w /= value;
	return * this;

}

template<class T>
inline point<T> point<T>::operator*(const matrix<T>& m) const
{
	return point<T>(
		this->x* m(0, 0) + this->y* m(1, 0) + this->z* m(2, 0) + w * m(3, 0),
		this->x* m(0, 1) + this->y* m(1, 1) + this->z* m(2, 1) + w * m(3, 1),
		this->x* m(0, 2) + this->y* m(1, 2) + this->z* m(2, 2) + w * m(3, 2),
		this->x* m(0, 3) + this->y* m(1, 3) + this->z* m(2, 3) + w * m(3, 3)
	);
}

template<class T>
inline point<T>& point<T>::operator*=(const matrix<T>& m)
{
	*this = this->operator*(m);
	return *this;
}

template<class T>
inline T point<T>::vector_length()
{
	return T(sqrt(this->x* this->x + this->y* this->y + this->z * this->z+ w * w));
}

template<class T>
inline point<T> point<T>::normalization()
{
	T length = vector_length();
	return operator/(length);
}

template<class T>
inline T point<T>::dot_product(const point<T>& a, const point<T>& b)
{
	return a.x * b.x+ a.y* b.y+ a.z* b.z+ a.w * b.w;
}

template<class T>
inline point<T> point<T>::cross_product(const point<T>& a, const point<T>& b)
{
	return point<T>{
		a.y* b.z- a.z* b.y,
		a.z* b.x- a.x* b.z,
		a.x* b.y- a.y* b.x
	};
}

template<class T>
inline point<T> point<T>::vector(const point<T>& a, const point<T>& b)
{
	return b.operator-(a);
}

template<class T>
inline point<T> point<T>::normalized_vector(const point<T>& a, const point<T>& b)
{
	return vector(a, b).normalization();
}
