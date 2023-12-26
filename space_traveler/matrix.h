#pragma once
#include "mesh_loader.h"

template <class T = float>
class matrix {

public:
	T** info() { return info_; }
	const size_t& rows() { return rows_; }
	const size_t& columns() { return columns_; }

	matrix<T>& operator=(const matrix<T>& other) = default;
	matrix<T>& operator=(matrix<T>&& other) noexcept = default;

private:
	T** info_;
	size_t rows_;
	size_t columns_;
public:


	static T** alloc_array(const size_t& rows, const size_t& columns)
	{
		int r = rows;
		T** pointer = new T*[r];
		for (size_t i = 0; i < rows; i++)
			pointer[i] = new T[columns];
		return pointer;
	}

	static void clear_array(T** pointer, const size_t& rows, const size_t& columns)
	{
		for (size_t i = 0; i < rows; i++)
			delete[] pointer[i];
		delete[] pointer;
	}


	matrix(T** p, const size_t& r, const size_t& c)
	{
		cout << __FUNCTION__ << endl;
		info_ = p;
		rows_ = r;
		columns_ = c;
	}

	matrix(const matrix<T>& m) :matrix(m.info_, m.rows_, m.columns_)
	{
		cout << __FUNCTION__ << endl;
	}

	matrix() :matrix(nullptr, 0, 0) {}

	~matrix()
	{
		cout << __FUNCTION__ << endl;
		clear_array(info_, rows_, columns_);
	}

	inline matrix<T> operator* (const matrix<T>& t_m) const {
		T** result = alloc_array(rows, columns);

		for (unsigned i = 0; i < rows_; i++)
			for (unsigned j = 0; j < columns_; j++)
				for (unsigned k = 0; k < t_m.columns_; k++)
					result[i][j] += info_[i][k] * t_m.info_[k][j];

		return matrix<T>(result, rows, t_m.columns);
	}

	inline matrix<T> operator*(const T& value) const {
		T** result = alloc_array(rows, columns);

		for (unsigned i = 0; i < rows_; i++)
			for (unsigned j = 0; j < columns_; j++)
				result[i][j] += info_[i][j] * value;

		return matrix<T>(result, rows, columns);

	}

	matrix<T> operator/ (const T& value)const {
		T** result = alloc_array(rows, columns);
		for (unsigned i = 0; i < rows_; i++)
			for (unsigned j = 0; j < columns_; j++)
				result[i][j] += info_[i][j] / value;

		return matrix<T>(result, rows, columns);
	}

	matrix<T>& operator*= (const matrix<T>& t_m) {

		for (unsigned i = 0; i < rows_; i++)
			for (unsigned j = 0; j < columns_; j++) {
				T sum = T(0);
				for (unsigned k = 0; k < rows_; k++)
					sum += info_[i][k] * t_m.info_[k][j];
				info_[i][j] = sum;
			}

		return *this;
	}
	matrix<T>& operator*= (const T& value) {

		for (unsigned i = 0; i < rows_; i++)
			for (unsigned j = 0; j < columns_; j++)
				info_[i][j] *= value;

		return *this;

	}
	matrix<T>& operator/= (const T& value) {
		for (unsigned i = 0; i < rows_; i++)
			for (unsigned j = 0; j < columns_; j++)
				info_[i][j] /= value;

		return *this;
	}

	matrix<T>& precision(const int& precision) {
		T temp = pow(10, precision);

		for (unsigned i = 0; i < rows_; i++)
			for (unsigned j = 0; j < columns_; j++)
				info_[i][j] = round(info_[i][j] * temp) / temp;

		return *this;
	}

	matrix<T>& transposed() {

		for (unsigned i = 0; i < rows_; i++)
			for (unsigned j = 0; j < columns_; j++) {
				T temp = info_[i][j];
				info_[i][j] = info_[i][j];
				info_[i][j] = temp;
			}


		return *this;
	}

	ostream& operator<< (ostream& os) {
		for (size_t i = 0; i < rows_; i++) {
			for (size_t j = 0; j < columns_; j++)
				os << "\t" << info_[i][j] << "\t";
			os << endl;
		}
		return os;
	}

	static matrix<T> projection(
		const T& aspect_ratio,
		const T& fov,
		const T& z_compression,
		const T& z_monitor
	) {
		if (rows < 4 | columns < 4)
			return matrix<T>();
		else {

			T** result = alloc_array(rows, columns);
			result[0][0] = aspect_ratio * fov;
			result[1][1] = fov;
			result[2][2] = z_compression;
			result[2][3] = T(1);
			result[3][2] = (-z_monitor) * z_compression;

			return matrix<T>(result, rows, columns);
		}


	}
	static ostream& print(ostream& os, const matrix<T>& m) {
		for (size_t i = 0; i < m.rows_; i++) {
			for (size_t j = 0; j < m.columns_; j++)
				os << "\t" << m.info_[i][j] << "\t";
			os << endl;
		}
		return os;
	}
	static matrix<T> x_rotation(const T& radian_angle, const size_t& rows, const size_t& columns) {

		if (rows < 3 || columns < 3)
			return matrix<T>();
		else {
			T** result = alloc_array(rows, columns);

			result[0][0] = T(1);
			result[1][1] = cos(radian_angle);
			result[1][2] = -sin(radian_angle);
			result[2][1] = -result[1][2];
			result[2][2] = result[1][1];

			return matrix<T>(result, rows, columns);
		}

	}
	static matrix<T> y_rotation(const T& radian_angle, const size_t& rows, const size_t& columns) {

		if (rows < 3 || columns < 3)
			return matrix<T>{};
		else {
			T** result = alloc_array(rows, columns);

			result[0][0] = cos(radian_angle);
			result[0][2] = sin(radian_angle);
			result[1][1] = T(1);
			result[2][1] = -result[0][2];
			result[2][2] = result[0][0];

			return matrix<T>{result, rows, columns};
		}
	}

	static matrix<T> z_rotation(const T& radian_angle, const size_t& rows, const size_t& columns) {
		if (rows < 3 || columns < 3)
			return matrix<T>{};
		else {
			T** result = alloc_array(rows, columns);

			result[0][0] = cos(radian_angle);
			result[0][1] = -sin(radian_angle);
			result[1][1] = -result[0][1];
			result[1][2] = result[0][0];
			result[2][2] = T(1);

			return matrix<T>{result, rows, columns};
		}
	}


};
