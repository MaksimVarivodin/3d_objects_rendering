#pragma once
#include "Header.h"

namespace engine_math {
	template<class T = float>
	class matrix
	{
		int rows_;
		int columns_;
		vector<vector<T>> data_;
	public:

		int rows ()const{return rows_;}
		int columns () const{return columns_;}
		/*
		
		Creates a transposed matrix from current instance.
		@return matrix<T>

		*/
		matrix<T> transposed();

		
		Vector3<T> to_vector3();

		/*
		
		Creates a link to the current instance,
		initialized by method argument value.
		@return matrix<T>&

		*/
		matrix<T>& operator=(const matrix<T>& m);

		matrix<T> operator*(const matrix<T>& m);

		matrix<T> operator/(T value);

		Vector3<T> operator*(const Vector3<T>&);


		matrix<T>& operator*=(const matrix<T>&);

		matrix<T>& operator*=(const Vector3<T>&);

		matrix<T>& operator/=(T value);
		
		T operator()(const int &row, const int& column) const;
		void operator()(const int &row, const int &column, T value);

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

		matrix<T>(const vector<vector<T>>& d){
			rows_ = d.size();
			if (rows_ > 0)
				columns_ = d[0].size();
			else
				columns_ = 0;
			data_ = d;
		}
		
		matrix<T>(const vector<vector<T>>& d, const int& r, const int& c)
		: rows_(r), columns_(c), data_(d){}

		matrix<T>(): rows_(0), columns_(0), data_() {}
	};
	
}



