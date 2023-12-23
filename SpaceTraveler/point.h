#pragma once
#include "header.h"

template <class T = float, double, int, unsigned, long, short>
class point
{

public:
	T* x(){return x_;}
	T* y(){return y_;}
	T* z(){return z_;}
	T* w(){return w_;}

	const T& x()const {return *x_;}
	const T& y()const {return *y_;}
	const T& z()const {return *z_;}
	const T& w()const {return *w_;}

	T* x()const {return x_;}
	T* y()const {return y_;}
	T* z()const {return z_;}
	T* w()const {return w_;}

	void x(const T & val_x){*x_ = val_x;}
	void y(const T & val_y){*y_ = val_y;}
	void z(const T & val_z){*z_ = val_z;}
	void w(const T & val_w){*w_ = val_w;}



	point(
	const T& x,
	const T& y,
	const T& z,
	const T& w
	):
		x_(new T(x)),
		y_(new T(y)),
		z_(new T(z)),
		w_(new T(w))
	{
		
	}
	~point()
	{

	}
private:
	T* x_;
	T* y_;
	T* z_;
	T* w_;
public:

	
	/**
	 * \brief Adds each current coordinate to the same coordinate from the passed point.
	 * \param point: const trans_point<T>&
	 * \return result of addition
	 */
	const point<T>& operator+(const point<T>& p) const;
	
	/**
	 * \brief Does the addition and puts result into current point.
	 * \param point: const trans_point<T>&
	 * \return result of addition
	 */
	point<T>& operator+= (const point<T>& p);
	
	/**
	 * \brief Subtracts each current coordinate to the same coordinate from the passed point.
	 * \param point: const trans_point & 
	 * \return result of subtraction
	 */
	const point<T>& operator-(const point<T> & p) const;
	
	/**
	 * \brief Does the subtraction and puts result into current point.
	 * \param point: const trans_point & 
	 * \return result of subtraction
	 */
	point<T>& operator-=(const point & p);
	
	/**
	 * \brief Multiplies point by value
	 * \param value: const float &
	 * \return result of multiplication
	 */
	const point<T>& operator*(const float & value) const;
	
	/**
	 * \brief Multiplies point by value and puts the result into the current point
	 * \param value: const float &
	 * \return result of multiplication
	 */
	point<T>& operator*= (const float & value);
	

	
	/**
	 * \brief Calculates cross product
	 * \param point: const trans_point & 
	 * \return cross product
	 */
	const point<T>& operator*(const point & p) const;
	
	
	/**
	 * \brief Calculates cross product and puts the result into the current point
	 * \param point: const trans_point &
	 * \return cross product
	 */
	point<T>& operator*= (const point & p);
	
	/**
	 * \brief Divides current coordinates by the passed value
	 * \param value: const float &
	 * \return point divided by value
	 */
	const point<T>& operator/(const float & value) const;
	
	/**
	 * \brief Divides and puts the result into the current point.
	 * \param value: const float &
	 * \return point divided by value
	 */
	point<T>& operator/= (const float & value);
	/**
	 * \brief Calculates calculates precision for the current point.
	 * \param precision: const int & 
	 * \return point with set precise
	 */
	point<T>& precision(const int & precision);
	
	/**
	 * \brief Calculates vector from current point to the passed point.
	 * \param point: const trans_point<T>&
	 * \return normalized vector
	 */
	const point<T>& vector(const point<T>& p) const;


	/// <summary>
	/// Calculates normalized vector from current point to the passed point.
	/// </summary>
	/// <param name="p"></param>
	/// <returns></returns>
	const point<T>& normalized_vector(const point<T>& p) const;
	
	/**
	 * \brief Calculated dot product between current and passed point.
	 * \param point: const trans_point<T>&
	 * \return dot product
	 */
	const float& scalar(const point<T>& p) const;
	
	/**
	 * \brief Calculates length from (0, 0, 0, 0) to the current point.
	 * \return vector length
	 */
	const float& modulus() const;
	
	/**
	 * \brief Normalizes current point as vector.
	 * \return normalized vector
	 */
	point<T>& normalization();
};

