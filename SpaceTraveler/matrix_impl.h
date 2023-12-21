#pragma once
#include "matrix.h"

template<class T>
engine_math::matrix<T> engine_math::matrix<T>::transposed()
{
	matrix<T> transposed(columns_, rows_);

	for (int i = 0; i < rows_; i++) 
		for (int j = 0; j < columns_; j++)
			transposed.data_[j][i] = data_[i][j];
	
	return transposed;
}

template <class T>
Vector3<T> engine_math::matrix<T>::to_vector3()
{
			if (rows_ == 3 and columns_ == 1)
				return Vector3<T>(
				data_[0][0],
				data_[1][0],
				data_[2][0]
				);
			return Vector3<T>();
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
inline engine_math::matrix<T> engine_math::matrix<T>::operator*(const matrix& m)
{
	if (rows_ != m.columns_ && columns_ != m.rows_) 
		return matrix<T>();	

	matrix<T> result(rows_, m.columns_);

	for (int i = 0; i < rows_; i++) 
		for (int j = 0; j < m.columns_; i++) 
			for (int k = 0; k < columns_; k++)
				result[i][j] += data_[i][k] * m.data_[k][j];		
	
	return result;
}

template <class T>
engine_math::matrix<T> engine_math::matrix<T>::operator/(T value)
{
	matrix result(rows_, columns_);

	for (int i = 0; i< rows_; i++)
		for (int j = 0 ; j< columns_; j++)		
			result.operator()(i, j, operator()(i, j) / value);
		
		
	
	return result;
}

template<class T>
inline Vector3<T> engine_math::matrix<T>::operator*(const Vector3<T>& v)
{
	if (rows_ != 3)
		return Vector3<T>();
	return Vector3<T>(
		 v.x * data_[0][0] + v.y * data_[1][0] + v.z * data_[2][0],
		 v.x * data_[0][1] + v.y * data_[1][1] + v.z * data_[2][1],
		 v.x * data_[0][2] + v.y * data_[1][2] + v.z * data_[2][2]
		);
}

template<class T>
inline engine_math::matrix<T>& engine_math::matrix<T>::operator*=(const matrix<T>& m)
{
	// TODO: вставьте здесь оператор return
	*this = *this->operator*(m);
	return *this;
}
template<class T>
inline engine_math::matrix<T>& engine_math::matrix<T>::operator*=(const Vector3<T>& v)
{
	// TODO: вставьте здесь оператор return
	*this = matrix<T>(
		vector<vector<T>>{
			{	v.x * data_[0][0] + v.y * data_[1][0] + v.z * data_[2][0]	},
			{	v.x * data_[0][1] + v.y * data_[1][1] + v.z * data_[2][1]	},
			{	v.x * data_[0][2] + v.y * data_[1][2] + v.z * data_[2][2]	}
		}
	);
	return *this;
}

template <class T>
engine_math::matrix<T>& engine_math::matrix<T>::operator/=(T value)
{
	*this = this->operator/(value);
	return *this;
}

template<class T>
T engine_math::matrix<T>::operator()(const int& row, const int& column) const
{
	if (row < 0 ||  row >= rows_ || column < 0 || column >= columns_)
		throw exception("out of bounds");
	else
	{
		return data_[row][column];
	}
		
	
}

template <class T>
void engine_math::matrix<T>::operator()(const int& row, const int& column, T value)
{
	if (row < 0 ||  row >= rows_ || column < 0 || column >= columns_)
		throw exception("out of bounds");
	else
	{
		data_[row][column] = value;
	}
}



