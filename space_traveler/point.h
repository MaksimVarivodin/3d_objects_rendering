#pragma once
#include "header.h"
namespace engine_math {
	/**
	 * \brief Class of four dimensional point.
	 */
	template <class T>
	class point
	{
		// x - coordinate
		T	x_;
		// y - coordinate
		T	y_;
		// z - coordinate
		T	z_;
		// w - coordinate
		T	w_;
	public:
		// reference to x - coordinate
		T&	get_ref_x(){return x_;}
		// reference to y - coordinate
		T&	get_ref_y(){return y_;}
		// reference to z - coordinate
		T&	get_ref_z(){return z_;}
		// reference to w - coordinate
		T&	get_ref_w(){return w_;}
	
		// const reference to value of x - coordinate
		const T&	get_const_x()const {return x_;}
		// const reference to value of y - coordinate
		const T&	get_const_y()const {return y_;}
		// const reference to value of z - coordinate
		const T&	get_const_z()const {return z_;}
		// const reference to value of w - coordinate
		const T&	get_const_w()const {return w_;}

		// const reference to value of x - coordinate
		T*	x()const {return &x_;}
		// const reference to value of y - coordinate
		T*	y()const {return &y_;}
		// const reference to value of z - coordinate
		T*	z()const {return &z_;}
		// const reference to value of w - coordinate
		T*	w()const {return &w_;}
	
		/**
		 * \brief Adds each current coordinate to the same coordinate from the passed point.
		 * \param point: const trans_point&
		 * \return result of addition
		 */
		const point& operator+(const point& point) const;
	
		/**
		 * \brief Does the addition and puts result into current point.
		 * \param point: const trans_point&
		 * \return result of addition
		 */
		point& operator+= (const point& point);
	
		/**
		 * \brief Subtracts each current coordinate to the same coordinate from the passed point.
		 * \param point: const trans_point & 
		 * \return result of subtraction
		 */
		const point& operator-(const point & point) const;
	
		/**
		 * \brief Does the subtraction and puts result into current point.
		 * \param point: const trans_point & 
		 * \return result of subtraction
		 */
		point& operator-=(const point & point);
	
		/**
		 * \brief Multiplies point by value
		 * \param value: const T &
		 * \return result of multiplication
		 */
		const point& operator*(const T & value) const;
	
		/**
		 * \brief Multiplies point by value and puts the result into the current point
		 * \param value: const T &
		 * \return result of multiplication
		 */
		point& operator*= (const T & value);
	
		/**
		 * \brief Calculates cross product
		 * \param point: const trans_point & 
		 * \return cross product
		 */
		const point& operator*(const point & point) const;
	
	
		/**
		 * \brief Calculates cross product and puts the result into the current point
		 * \param point: const trans_point &
		 * \return cross product
		 */
		point& operator*= (const point & point);
	
		/**
		 * \brief Divides current coordinates by the passed value
		 * \param value: const T &
		 * \return point divided by value
		 */
		const point& operator/(const T & value) const;
	
		/**
		 * \brief Divides and puts the result into the current point.
		 * \param value: const T &
		 * \return point divided by value
		 */
		point& operator/= (const T & value);
		/**
		 * \brief Calculates calculates precision for the current point.
		 * \param precision: const int & 
		 * \return point with set precise
		 */
		point& precision(const int & precision);
	
		/**
		 * \brief Calculates vector from current point to the passed point.
		 * \param point: const trans_point&
		 * \return normalized vector
		 */
		const point& vector(const point& p) const;


		/// <summary>
		/// Calculates normalized vector from current point to the passed point.
		/// </summary>
		/// <param name="p"></param>
		/// <returns></returns>
		const point& normalized_vector(const point& p) const;
	
		/**
		 * \brief Calculated dot product between current and passed point.
		 * \param point: const trans_point&
		 * \return dot product
		 */
		const T& scalar(const point& point) const;
	
		/**
		 * \brief Calculates length from (0, 0, 0, 0) to the current point.
		 * \return vector length
		 */
		const T& modulus() const;
	
		/**
		 * \brief Normalizes current point as vector.
		 * \return normalized vector
		 */
		point& normalization();

		const Vector2f & to_Vector2f() const {return Vector2f{x_, y_};}
	
		/**
		 * \brief Constructor with all parameters
		 * \param x 
		 * \param y 
		 * \param z 
		 * \param w 
		 */
		point( 
			const T& x,
			const T& y,
			const T& z,
			const T& w)
		: x_(x), y_(y), z_(z), w_(w){}
	
		/**
		 * \brief Constructor with x, y, z parameters
		 * \param x 
		 * \param y 
		 * \param z 
		 */
		point( 
			const T& x,
			const T& y,
			const T& z)
		: point(x, y, z, 0){}
	
		/**
		 * \brief Constructor with x, y parameters
		 * \param x 
		 * \param y 
		 */
		point( 
			const T& x,
			const T& y)
		: point(x, y, 0){}
	
		/**
		 * \brief Constructor with x parameter
		 * \param x 
		 */
		point(
			const T& x)
		: point(x, 0){}
	
		/**
		 * \brief Default constructor
		 */
		point()
		:point(0){}
	
	};
}

