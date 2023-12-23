#pragma once
#include "matrix.h"
namespace engine_math {
	/**
	 * \brief Class of four dimensional point.
	 */
	class point
	{
		// x - coordinate
		float	x_;
		// y - coordinate
		float	y_;
		// z - coordinate
		float	z_;
		// w - coordinate
		float	w_;
	public:
		// reference to x - coordinate
		float&	x(){return x_;}
		// reference to y - coordinate
		float&	y(){return y_;}
		// reference to z - coordinate
		float&	z(){return z_;}
		// reference to w - coordinate
		float&	w(){return w_;}
	
		// const reference to value of x - coordinate
		const float&	x_ref()const {return x_;}
		// const reference to value of y - coordinate
		const float&	y_ref()const {return y_;}
		// const reference to value of z - coordinate
		const float&	z_ref()const {return z_;}
		// const reference to value of w - coordinate
		const float&	w_ref()const {return w_;}

		// const reference to value of x - coordinate
		float*	x()const {
			return x_;}
		// const reference to value of y - coordinate
		float*	y()const {return &y_;}
		// const reference to value of z - coordinate
		float*	z()const {return &z_;}
		// const reference to value of w - coordinate
		float*	w()const {return &w_;}
	
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
		 * \param value: const float &
		 * \return result of multiplication
		 */
		const point& operator*(const float & value) const;
	
		/**
		 * \brief Multiplies point by value and puts the result into the current point
		 * \param value: const float &
		 * \return result of multiplication
		 */
		point& operator*= (const float & value);
	
		/**
		 * \brief Multiplication of matrix on vector
		 * \param matrix: const trans_matrix &
		 * \return matrix * vector
		 */
		const point& operator*(const matrix & matrix) const;
	
		/**
		 * \brief Multiplies vector by matrix and sets the result to the current point
		 * \param matrix: const trans_matrix & 
		 * \return matrix * vector
		 */
		point& operator*= (const matrix & matrix);
	
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
		 * \param value: const float &
		 * \return point divided by value
		 */
		const point& operator/(const float & value) const;
	
		/**
		 * \brief Divides and puts the result into the current point.
		 * \param value: const float &
		 * \return point divided by value
		 */
		point& operator/= (const float & value);
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
		const float& scalar(const point& point) const;
	
		/**
		 * \brief Calculates length from (0, 0, 0, 0) to the current point.
		 * \return vector length
		 */
		const float& modulus() const;
	
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
			const float& x,
			const float& y,
			const float& z,
			const float& w)
		: x_(x), y_(y), z_(z), w_(w){}
	
		/**
		 * \brief Constructor with x, y, z parameters
		 * \param x 
		 * \param y 
		 * \param z 
		 */
		point( 
			const float& x,
			const float& y,
			const float& z)
		: point(x, y, z, 0){}
	
		/**
		 * \brief Constructor with x, y parameters
		 * \param x 
		 * \param y 
		 */
		point( 
			const float& x,
			const float& y)
		: point(x, y, 0){}
	
		/**
		 * \brief Constructor with x parameter
		 * \param x 
		 */
		point(
			const float& x)
		: point(x, 0){}
	
		/**
		 * \brief Default constructor
		 */
		point()
		:point(0){}
	
	};
}

