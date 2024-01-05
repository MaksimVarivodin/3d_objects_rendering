#pragma once
#include "matrix.h"
using namespace engine_math;
template<class T>
engine_math::matrix<T> engine_math::matrix<T>::transposed()
{
	vector<vector<T>> tr(columns_, vector<T>(rows_));
	for (int i = 0; i < rows_; i++)
		for (int j = 0; j < columns_; j++) {
			T temp = data_[i][j];
			data_[i][j] = data_[j][i];
			data_[j][i] = temp;
		}


	return matrix<T>{tr, columns_, rows_};
}

template<class T>
inline matrix<T> engine_math::matrix<T>::x_rotation(const T& radian_angle)
{

	return matrix<T>(
		vector<vector<T>>{
			{	1, 0, 0	},
			{ 0	,	cosf(radian_angle)	,	-sinf(radian_angle)},
			{ 0	,	sinf(radian_angle)	,	cosf(radian_angle)}
	},
		3,
		3
	);
}

template<class T>
inline matrix<T> engine_math::matrix<T>::y_rotation(const T& radian_angle)
{
	return matrix<T>(
		vector<vector<T>>{
			{	cos(radian_angle)	,	0	,	sin(radian_angle)},
			{					0	,	1	,					0},
			{	-sin(radian_angle)	,	0	,	cos(radian_angle)}
	},
		3,
		3
	);
}

template<class T>
inline matrix<T> engine_math::matrix<T>::z_rotation(const T& radian_angle)
{
	return matrix<T>(
		vector<vector<T>>{
			{	cos(radian_angle)	,	-sin(radian_angle)	,	0	},
			{	sin(radian_angle)	,	cos(radian_angle)	,	0	},
			{					0	,					0	,	1	}
	},
		3,
		3
	);
}


template<class T>
engine_math::matrix<T>& engine_math::matrix<T>::operator=(const matrix& m)
{
	// TODO: вставьте здесь оператор return
	data_ = m.data_;
	rows_ = m.rows_;
	columns_ = m.columns_;
	return *this;
}

template<class T>
inline engine_math::matrix<T>& engine_math::matrix<T>::operator*=(const matrix<T>& m)
{
	vector<vector<T>> new_data(rows_, vector<T>(m.columns_));

	for (size_t i = 0; i < rows_; i++)
		for (size_t j = 0; j < m.columns_; j++)
			for (size_t k = 0; k < columns_; k++)
				new_data[i][j] += data_[i][k] * m(k,j);
	columns_ = m.columns_;
	data_ = new_data;
	return *this;
}

template <class T>
engine_math::matrix<T>& engine_math::matrix<T>::operator/=(const T& value)
{
	for (size_t i = 0; i < rows_; i++)
		for (size_t j = 0; j < columns_; j++)
			data_[i][j] /= value;
	return *this;
}

template<class T>
const T& engine_math::matrix<T>::operator()(const int& row, const int& column) const
{
	if (row < 0 || row >= rows_ || column < 0 || column >= columns_)
		throw exception("out of bounds");
	else
	{
		return data_[row][column];
	}


}

template <class T>
void engine_math::matrix<T>::operator()(const int& row, const int& column, T value)
{
	if (row < 0 || row >= rows_ || column < 0 || column >= columns_)
		throw exception("out of bounds");
	else
	{
		data_[row][column] = value;
	}
}



