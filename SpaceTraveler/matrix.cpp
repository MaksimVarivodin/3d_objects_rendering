#include "matrix.h"

engine_math::matrix engine_math::matrix::operator*(const matrix& t_m) const
{
	matrix result;

	for(unsigned i = 0; i< rows_; i++)
		for(unsigned j = 0; j< columns_; j++)
			for(unsigned k = 0; k < rows_; k++)
				result(i, j) += matrix_[i][k]* t_m.matrix_[k][i];

	return result;
}

engine_math::matrix engine_math::matrix::operator*(const float& value) const
{
	matrix res;

	for (unsigned i = 0; i< rows_; i++)
		for (unsigned j = 0; j < columns_; j++)
			res(i, j) = matrix_[i][j] * value;
	
	return res;
}

engine_math::matrix engine_math::matrix::operator/(const float& value) const
{
	matrix res;
	if (value == 0.0f)
		throw exception("Divide by zero.");
	for (unsigned i = 0; i< rows_; i++)
		for (unsigned j = 0; j < columns_; j++)
			res(i,j) = matrix_[i][j] / value;
	
	return res;
}

engine_math::matrix& engine_math::matrix::operator*=(const matrix& t_m)
{
	*this = this->operator*(t_m);
	return *this;
}

engine_math::matrix& engine_math::matrix::operator*=(const float& value)
{
	*this = this->operator*(value);
	return *this;
}

engine_math::matrix& engine_math::matrix::operator/=(const float& value)
{
	*this = this->operator/(value);
	return *this;
}

float& engine_math::matrix::operator()(const unsigned& row, const unsigned& column)
{
	if (row < rows_ && column < columns_)
		return matrix_[row][column];
	throw exception("index was out of range");
}

const float& engine_math::matrix::operator()(const unsigned& row, const unsigned& column) const
{
	if (row < rows_ && column < columns_)
		return matrix_[row][column];
	throw exception("index was out of range");
}

engine_math::matrix& engine_math::matrix::transposed()
{
	for (unsigned i = 0; i < rows_; i++)
		for (unsigned j = 0 ; j< columns_; j++)
		{
			const float temp = matrix_[i][j];
			matrix_[i][j] = matrix_[j][i];
			matrix_[j][i] = temp;
		}
	return *this;
}

engine_math::matrix engine_math::matrix::projection(
	const float& aspect_ratio,
	const float& fov,
	const float& z_compression,
	const float& z_monitor)
{
	return matrix(
		new   float*[rows_]{
			new   float[columns_]{	aspect_ratio * fov	,	0	,	0							,	0},
			new   float[columns_]{					0	,	fov	,	0							,	0},
			new   float[columns_]{					0	,	0	,	z_compression				,	1},
			new   float[columns_]{					0	,	0	,	-z_monitor * z_compression	,	0}
		}
	);
}

engine_math::matrix engine_math::matrix::transposed(matrix t_m)
{
	return t_m.transposed();
}

const engine_math::matrix& engine_math::matrix::x_rotation(const float& radian_angle)
{
	return matrix (
		new   float*[rows_]{
			new   float[columns_]{1,						0	,					0	, 0},
			new   float[columns_]{0,		cosf(radian_angle)	,	-sinf(radian_angle)	, 0},
			new   float[columns_]{0,		sinf(radian_angle)	,	cosf(radian_angle)	, 0},
			new   float[columns_]{0,						0	,					0	, 0}
		});
}

const engine_math::matrix& engine_math::matrix::y_rotation(const float& radian_angle)
{
	return matrix (
		new   float*[rows_]{
			new   float[columns_]{cosf(radian_angle)	,	0	,	sinf(radian_angle)	, 0},
			new   float[columns_]{				0	,	1	,					0	, 0},
			new   float[columns_]{-sinf(radian_angle),	0	,	cosf(radian_angle)	, 0},
			new   float[columns_]{				0	,	0	,					0	, 0}
		});
}

const engine_math::matrix& engine_math::matrix::z_rotation(const float& radian_angle)
{
	return matrix (
		new   float*[rows_]{
			new   float[columns_]{cosf(radian_angle)	,	-sinf(radian_angle)	,	0	, 0},
			new   float[columns_]{sinf(radian_angle)	,	cosf(radian_angle)	,	0	, 0},
			new   float[columns_]{				0	,					0	,	1	, 0},
			new   float[columns_]{				0	,					0	,	0	, 0}
		});
}
