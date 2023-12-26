#pragma once
#include "Header.h"

namespace engine_math {
	template<class T = float>
	class matrix
	{

		size_t rows_;
		size_t columns_;
		vector<vector<T>> data_;
	public:

		size_t rows()const { return rows_; }

		size_t columns() const { return columns_; }

		/*

		Creates a transposed matrix from current instance.
		@return matrix<T>

		*/
		matrix<T> transposed();

		static matrix<T> projection(
			const T& aspect_ratio,
			const T& fov,
			const T& z_compression,
			const T& z_monitor
		);

		static matrix<T> x_rotation(const T& radian_angle);
		static matrix<T> y_rotation(const T& radian_angle);
		static matrix<T> z_rotation(const T& radian_angle);
		/*

		Creates a link to the current instance,
		initialized by method argument value.
		@return matrix<T>&

		*/
		matrix<T>& operator=(const matrix<T>& m);

		matrix<T>& operator*=(const matrix<T>&);

		matrix<T>& operator/=(const T& value);

		const T& operator()(const int& row, const int& column) const;
		void operator()(const int& row, const int& column, T value);

		matrix<T>(const matrix& m) :
			matrix(m.data_, m.rows_, m.columns_) {}

		matrix<T>(const int& r, const int& c) :
			rows_(r), columns_(c),
			data_(
				vector<vector<T>>(
					rows_, vector<T>(columns_, 0.0f)
				)
			)
		{
		}

		matrix<T>(
			const vector<vector<T>>& d,
			const size_t& rows,
			const size_t& columns)
			: rows_(rows), columns_(columns), data_(d)
		{}

		matrix<T>(const vector<vector<T>>& d, const int& r, const int& c)
			: rows_(r), columns_(c), data_(d) {}

		matrix<T>() : rows_(0), columns_(0), data_() {}
	};

}



