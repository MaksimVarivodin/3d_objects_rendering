#pragma once
#include "matrix.h"

template<class Templ>
inline engine_math::matrix<Templ> engine_math::matrix<Templ>::transposed()
{
	matrix<Templ> transposed(columns_, rows_);

	for (int i = 0; i < rows_; i++) 
		for (int j = 0; j < columns_; j++)
			transposed.data_[j][i] = data_[i][j];
	
	return transposed;
}


template<class Templ>
inline engine_math::matrix<Templ>& engine_math::matrix<Templ>::operator=(const matrix<Templ>& m)
{
	// TODO: вставьте здесь оператор return
	data_ = m.data_;
	rows_ = m.rows_;
	columns_ = m.columns_;
	return *this;
}

template<class Templ>
inline engine_math::matrix<Templ> engine_math::matrix<Templ>::operator*(const matrix<Templ>& m)
{
	if (rows_ != m.columns_ && columns_ != m.rows_) 
		return matrix<Templ>();	

	matrix<Templ> result(rows_, m.columns_);

	for (int i = 0; i < rows_; i++) 
		for (int j = 0; j < m.columns_; i++) 
			for (int k = 0; k < columns_; k++)
				result[i][j] += data_[i][k] * m.data_[k][j];		
	
	return result;
}
template<class Templ>
inline Vector3<Templ> engine_math::matrix<Templ>::operator*(const Vector3<Templ>& v)
{
	if (rows_ != 3)
		return Vector3<Templ>();
	return Vector3<Templ>(
		 v.x * data_[0][0] + v.y * data_[1][0] + v.z * data_[2][0],
		 v.x * data_[0][1] + v.y * data_[1][1] + v.z * data_[2][1],
		 v.x * data_[0][2] + v.y * data_[1][2] + v.z * data_[2][2]
		);
}

template<class Templ>
inline engine_math::matrix<Templ>& engine_math::matrix<Templ>::operator*=(const matrix<Templ>& m)
{
	// TODO: вставьте здесь оператор return
	*this = *this->operator*(m);
	return *this;
}
template<class Templ>
inline engine_math::matrix<Templ>& engine_math::matrix<Templ>::operator*=(const Vector3<Templ>& v)
{
	// TODO: вставьте здесь оператор return
	*this = matrix<Templ>(
		vector<vector<Templ>>{
			{	v.x * data_[0][0] + v.y * data_[1][0] + v.z * data_[2][0]	},
			{	v.x * data_[0][1] + v.y * data_[1][1] + v.z * data_[2][1]	},
			{	v.x * data_[0][2] + v.y * data_[1][2] + v.z * data_[2][2]	}
		}
	);
	return *this;
}

template<class Templ>
inline Templ& engine_math::matrix<Templ>::operator()(const int row, const int column)
{
	if (row>= 0 && row < rows_ && column >= 0 && column < columns_)
	// TODO: вставьте здесь оператор return
		return &(data_[row][column]);
	return nullptr;
}



