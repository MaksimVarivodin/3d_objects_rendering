#include "Matrix.h"

Matrix Matrix::createRotationX(float angle)
{
	vector<vector<float>> v = {
		{1, 0, 0},
		{0, cos(angle), -sin(angle)},
		{0, sin(angle), cos(angle)}
	};
	return Matrix(v);
}

Matrix Matrix::createRotationY(float angle)
{
	vector<vector<float>> v = {
		{cos(angle), 0, sin(angle)},
		{0, 1, 0},
		{-sin(angle), 0, cos(angle)}
	};
	return Matrix(v);
}

Matrix Matrix::createRotationZ(float angle)
{
	vector<vector<float>> v = {
		{cos(angle), -sin(angle), 0},
		{sin(angle), cos(angle), 0},
		{0, 0, 1}
	};
	return Matrix(v);
}

Matrix Matrix::operator*(const Matrix& other)
{
    if (this->columns() != other.rows() && this->rows() != other.columns()) {
        throw invalid_argument("different sizes");
    }
    else {
		vector<vector<float>> result(this->rows(), vector<float>(other.columns()));
		for (int i = 0; i <this->rows(); i++) {
			for (int j = 0; j < other.columns(); j++) {				
				for (int k = 0; k < other.rows(); k++) {
					result[i][j] += data()[i][k] * other.data()[k][j];
				}
			}
		}
		return Matrix{result};
    }
    return Matrix{};
}
