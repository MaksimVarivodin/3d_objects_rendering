#include "point.h"
template<class T>
inline point<T> point<T>::operator+(const T& value) const
{
	return point<T>{
		this->x + value,
			this->y + value,
			this->z + value
	};
}

template<class T>
inline point<T> point<T>::operator+(const point<T>& other) const
{
	return point<T>{
		this->x + other.x,
			this->y + other.y,
			this->z + other.z
	};
}

template<class T>
inline point<T> point<T>::operator-(const T& value) const
{
	return point<T>{
		this->x - value,
			this->y - value,
			this->z - value
	};
}

template<class T>
inline point<T> point<T>::operator-(const point<T>& other) const
{
	return point<T>{
		this->x - other.x,
			this->y - other.y,
			this->z - other.z
	};
}

template<class T>
inline point<T> point<T>::operator*(const T& value) const
{
	return point<T>{
		this->x* value,
			this->y* value,
			this->z* value
	};
}

template<class T>
inline point<T> point<T>::operator/(const T& value) const
{
	return point<T>{
		this->x / value,
			this->y / value,
			this->z / value
	};
}

template<class T>
inline point<T>& point<T>::operator+=(const T& value)
{
	this->x += value;
	this->y += value;
	this->z += value;
	return *this;
}

template<class T>
inline point<T>& point<T>::operator+=(const point<T>& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;

	return *this;
}

template<class T>
inline point<T>& point<T>::operator-=(const T& value)
{
	this->x -= value;
	this->y -= value;
	this->z -= value;
	return *this;
}

template<class T>
inline point<T>& point<T>::operator-=(const point<T>& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;

	return *this;
}

template<class T>
inline point<T>& point<T>::operator*=(const T& value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
	return *this;

}

template<class T>
inline point<T>& point<T>::operator/=(const T& value)
{
	this->x /= value;
	this->y /= value;
	this->z /= value;
	return *this;

}

template<class T>
inline point<T> point<T>::operator*(const matrix<T>& m) const
{
	return point<T>(
		this->x * m(0, 0) + this->y * m(1, 0) + this->z * m(2, 0),
		this->x * m(0, 1) + this->y * m(1, 1) + this->z * m(2, 1),
		this->x * m(0, 2) + this->y * m(1, 2) + this->z * m(2, 2)
	);
}

template<class T>
inline point<T>& point<T>::operator*=(const matrix<T>& m)
{
	*this = this->operator*(m);
	return *this;
}

template<class T>
inline point<T> point<T>::operator*(const point<T>& p) const
{
	return point<T>(
		this->x * p.x,
		this->y * p.y,
		this->z * p.z
	);
}

template<class T>
inline point<T>& point<T>::operator*=(const point<T>& p)
{
	this->x *= p.x;
	this->y *= p.y;
	this->z *= p.z;
	return *this;
}

template<class T>
inline T point<T>::vector_length()
{
	return T(sqrt(this->x * this->x + this->y * this->y + this->z * this->z));
}

template<class T>
inline point<T> point<T>::normalization()
{
	T length = vector_length();
	operator/=(length);
	return *this;
}

template<class T>
inline point<T> point<T>::projection(const  T& aspect_ratio, const  T& fov, const T& z_compression, const  T& z_monitor)
{
	point<T> result{
		aspect_ratio * fov * this->x,
		fov * this->y,
		z_compression * (this->z - z_monitor)
	};
	if (this->z != T(0))
		result /= this->z;
	return result;
}
template<class T>
Vector2<T> point<T>::to_Vector2() {
	return Vector2<T>{
		(T)this->x,
		(T)this->y
	};
}
template<class T>
inline void point<T>::print()
{
	string type_name{ typeid(T).name() };
	cout << "point<"
		+ type_name
		+ ">: {"
		<< this->x
		<< ", "
		<< this->y
		<< ", "
		<< this->z
		<< "}"
		<< endl;
}

template<class T>
template<class U>
inline void point<T>::print_vector2(const Vector2<U>& vec)
{
	string type_name{ typeid(U).name() };
	cout << "point<"
		+ type_name
		+ ">: {"
		<< vec.x
		<< ", "
		<< vec.y
		<< "}"
		<< endl;
}

template<class T>
inline T point<T>::dot_product(const point<T>& a, const point<T>& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

template<class T>
inline point<T> point<T>::cross_product(const point<T>& a, const point<T>& b)
{
	return point<T>{
		a.y* b.z - a.z * b.y,
			a.z* b.x - a.x * b.z,
			a.x* b.y - a.y * b.x
	};
}

template<class T>
inline point<T> point<T>::vector(const point<T>& a, const point<T>& b)
{
	return a.operator-(b);
}

template<class T>
inline point<T> point<T>::normalized_vector(const point<T>& a, const point<T>& b)
{
	return vector(a, b).normalization();
}
