#include "Header.h"

class Matrix
{
	int _rows = 0;
	int _columns = 0;
	vector<vector<float>> _data;


public:

	int rows()const { return _rows; };
	int columns() const { return _columns; };
	vector<vector<float>> data() const { return _data; };
	
	Matrix operator*(const Matrix& other);

	static Matrix createRotationX(float angle);
	static Matrix createRotationY(float angle);
	static Matrix createRotationZ(float angle);


	Matrix() {};
	Matrix(vector<float> OneRow) {
		_rows = 1;
		_columns = OneRow.size();
		_data = vector<vector<float>>{
			OneRow
		};
	};

	Matrix(vector<vector<float>> v) {
		_rows = v.size();
		int firstSize = v[0].size();
		for (auto var : v)
		{
			if (var.size() != firstSize)
				throw invalid_argument("All rows must have the same number of columns");
		}
		_columns = firstSize;
		_data = v;
	};

	Matrix(const Matrix& other) {
		this->_data = other._data;
		this->_columns = other._columns;
		this->_rows = other._rows;
	};

};

