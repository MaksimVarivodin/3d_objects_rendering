#pragma once
#include "header.h"
namespace engine_math
{
	/**
	 * \brief Matrix for 3-4 dimensional transformations
	 */
	class matrix
	{
		/**
		 * \brief const row count
		 */
		static constexpr unsigned rows_ = 4;

		/**
		 * \brief const columns count
		 */
		static constexpr unsigned columns_ = 4;

		/**
		 * \brief matrix data field
		 */
		float** matrix_ = {};
		/**
		 * \brief Fills matrix to x by columns and to y by rows with passed value
		 * \param x 
		 * \param y 
		 * \param value 
		 */
		void fill_matrix(const unsigned& x, const unsigned& y, const float & value);

	public:
		/**
		 * \return const row count
		 */
		static unsigned rows() {return rows_;}
		/**
		 * \return const columns count
		 */
		static unsigned columns(){ return columns_;}



		matrix& operator=(const matrix& other) = default;
		matrix& operator=(matrix&& other) noexcept = default;

		matrix operator* (const matrix & t_m) const;
		matrix operator* (const float & value) const;

		matrix operator/(const float & value) const;

		matrix& operator*= (const matrix &t_m);
		matrix& operator*= (const float & value);
		matrix& operator/= (const float & value);

		float& operator()(const unsigned & row, const unsigned & column);
		const float& operator()(const unsigned & row, const unsigned & column) const;
		float**& operator()() {return matrix_;}
		const float** get()const {return matrix_;}
		void operator()(const float(& arg)[rows_][columns_]);

		matrix& precision(const int & precision);
		matrix& transposed();

		static matrix projection(
			const float& aspect_ratio,
			const float& fov,
			const float& z_compression,
			const float& z_monitor
			);
		static matrix transposed(matrix t_m);
		static const matrix& x_rotation(const float& radian_angle);
		static const matrix& y_rotation(const float& radian_angle);
		static const matrix& z_rotation(const float& radian_angle);


		

		/**
		 * \brief Constructor with data parameter
		 * \param data 
		 */
		matrix(float**& data):matrix_(data){}
		/**
		 * \brief Default constructor
		 */
		matrix() = default;
		/**
		 * \brief Copy constructor
		 * \param other 
		 */
		matrix(const matrix& other): matrix(){}
		/**
		 * \brief Copy constructor
		 * \param other 
		 */
		matrix(matrix&& other) noexcept = default;	

		~matrix()
		{
			for(int i = 0; i< rows_;i++)
				delete[] matrix_[i];
			delete[] matrix_;
		}
	};

}


