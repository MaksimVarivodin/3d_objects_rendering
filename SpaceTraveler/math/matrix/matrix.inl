//
// Created by maksymvarivodin on 7/29/24.
//
#ifndef MATRIX_INL
#define MATRIX_INL


namespace SpaceEngine
{
    using namespace std;


    template <class T>
    matrix<T>::matrix(size_t rows, size_t columns)
        : table_(rows, vector<T>(columns)),
          rows_(rows),
          columns_(columns)
    {
        if (rows_ == 0 || columns_ == 0)
            throw invalid_argument("Matrix cannot have zero rows or columns");
        check_validity();
    }

    template <class T>
    matrix<T>::matrix(const vector<vector<T>>& data)
        : table_(data),
          rows_(data.empty() ? 0 : data.size()),
          columns_(data.empty() ? 0 : data[0].size())
    {
        if (rows_ == 0 || columns_ == 0)
            throw invalid_argument("Matrix cannot have zero rows or columns");
        check_validity();
    }

    template <class T>
    matrix<T>::matrix(const vector<point<T>>& data)
        : table_(
              data.empty() ? 0 : data.size(),
              data.empty() ? vector<T>() : vector<T>(data[0].axes())),
          rows_(data.empty() ? 0 : data.size()),
          columns_(data.empty() ? 0 : data[0].axes())
    {
        for (size_t i = 0; i < rows_; i++)
            table_[i] = data[i].get_coordinates();
        check_validity();
    }

    template <class T>
    matrix<T>::matrix(const vector<direction<T>>& data)
        : table_(
              data.empty() ? 0 : data.size(),
              data.empty() ? vector<T>() : vector<T>(data[0].axes())),
          rows_(data.empty() ? 0 : data.size()),
          columns_(data.empty() ? 0 : data[0].axes())
    {
        for (size_t i = 0; i < rows_; i++)
            table_[i] = data[i].radius_direction().get_coordinates();
        check_validity();
    }

    template <class T>
    matrix<T>::matrix(const matrix& other)
        : matrix(other.table_)
    {
    }


    template <class T>
    size_t matrix<T>::rows() const
    {
        return rows_;
    }

    template <class T>
    size_t matrix<T>::columns() const
    {
        return table_.empty() ? 0 : table_[0].size();
    }

    template <class T>
    const vector<T>& matrix<T>::get_row(size_t row) const
    {
        if (row < rows())
            return &table_[row];
    }

    template <class T>
    const vector<vector<T>>& matrix<T>::get_table() const
    {
        return table_;
    }

    template <class T>
    vector<vector<T>>& matrix<T>::ref_table()
    {
        return table_;
    }


    template <class T>
    T& matrix<T>::operator()(size_t row, size_t column)
    {
        if (!is_row_valid(row))
            throw std::out_of_range("Invalid row index");
        if (!is_column_valid(column))
            throw std::out_of_range("Invalid column index");
        return table_[row][column];
    }

    template <class T>
    const T& matrix<T>::operator()(size_t row, size_t column) const
    {
        if (!is_row_valid(row))
            throw std::out_of_range("Invalid row index");
        if (!is_column_valid(column))
            throw std::out_of_range("Invalid column index");
        return table_[row][column];
    }


    template <class T>
    size_t matrix<T>::find_non_zero_value(size_t row) const
    {
        T zero(0);
        for (size_t i(0); i < columns(); ++i)
            if (table_[row][i] != zero)
                return i;
        return columns();
    }

    template <class T>
    vector<T> matrix<T>::main_diagonal() const
    {
        vector<T> result({0});
        for (size_t i(0); i < rows(); ++i)
            result[i] = table_[i][i];
        return result;
    }

    template <class T>
    vector<T> matrix<T>::secondary_diagonal() const
    {
        vector<T> result({0});
        for (size_t i(0); i < rows(); ++i)
            result[i] = table_[rows() - 1 - i][i];
        return result;
    }

    template <class T>
    T matrix<T>::trace() const
    {
        auto diagonal(main_diagonal());
        T sum(0);
        for (auto& value : diagonal)
            sum += value;
        return sum;
    }

    template <class T>
    matrix<T> matrix<T>::operator+(T value) const
    {
        matrix result;
        for (size_t i(0); i < rows(); ++i)
            for (size_t j(0); j < columns(); ++j)
                result[i][j] = table_[i][j] + value;
        return result;
    }

    template <class T>
    matrix<T>& matrix<T>::operator+=(T value)
    {
        for (size_t i(0); i < rows(); ++i)
            for (size_t j(0); j < columns(); ++j)
                table_[i][j] += value;
        return *this;
    }

    template <class T>
    matrix<T> matrix<T>::operator-(T value) const
    {
        matrix result;
        for (size_t i(0); i < rows(); ++i)
            for (size_t j(0); j < columns(); ++j)
                result[i][j] = table_[i][j] - value;
        return result;
    }

    template <class T>
    matrix<T>& matrix<T>::operator-=(T value)
    {
        for (size_t i(0); i < rows(); ++i)
            for (size_t j(0); j < columns(); ++j)
                table_[i][j] -= value;
        return *this;
    }

    template <class T>
    matrix<T> matrix<T>::operator*(T value) const
    {
        matrix<T> result;
        for (size_t i(0); i < rows(); ++i)
            for (size_t j(0); j < columns(); ++j)
                result[i][j] = table_[i][j] * value;
        return result;
    }

    template <class T>
    matrix<T>& matrix<T>::operator*=(T value)
    {
        for (size_t i(0); i < rows(); ++i)
            for (size_t j(0); j < columns(); ++j)
                table_[i][j] *= value;
        return *this;
    }

    template <class T>
    matrix<T> matrix<T>::operator/(T value) const
    {
        if (value == T(0))
            throw invalid_argument("Division by zero");
        matrix<T> result;
        for (size_t i(0); i < rows(); ++i)
            for (size_t j(0); j < columns(); ++j)
                result[i][j] = table_[i][j] / value;
        return result;
    }

    template <class T>
    matrix<T>& matrix<T>::operator/=(T value)
    {
        if (value == T(0))
            throw invalid_argument("Division by zero");

        for (size_t i(0); i < rows(); ++i)
            for (size_t j(0); j < columns(); ++j)
                table_[i][j] /= value;
        return *this;
    }

    template <class T>
    matrix<T> matrix<T>::operator*(const matrix<T>& other) const
    {
        if (columns_ != other.rows_)
            throw invalid_argument("Invalid matrix size");
        matrix<T> result(rows_, other.columns_);

        for (size_t i(0); i < rows(); ++i)
            for (size_t j(0); j < other.columns(); ++j)
                for (size_t k(0); k < columns(); ++k)
                    result(i, j) += table_[i][k] * other(k, j);
        return result;
    }

    template <class T>
    matrix<T>& matrix<T>::operator*=(const matrix<T>& other)
    {
        *this = this->operator*(other);
        return *this;
    }

    template <class T>
    matrix<T> matrix<T>::operator/(const matrix<T>& other) const
    {
        if (!is_square_matrix())
            throw out_of_range("Matrix is not square");

        matrix<T> result({{}});

        for (int i(0); i < rows(); ++i)
            for (int j(0); j < other.columns(); ++j)
                for (int k(0); k < columns(); ++k)
                {
                    if (other[k][j] == T(0))
                        throw invalid_argument("Division by zero in matrix division");
                    result[i][j] += table_[i][k] / other[k][j];
                }

        return result;
    }

    template <class T>
    matrix<T>& matrix<T>::operator/=(const matrix<T>& other)
    {
        *this = this->operator/(other);
        return *this;
    }

    template <class T>
    matrix<T> matrix<T>::operator+(const matrix<T>& other) const
    {
        matrix<T> result;
        for (size_t i(0); i < rows(); ++i)
            for (size_t j(0); j < columns(); ++j)
                result.table_[i][j] = table_[i][j] + other.table_[i][j];
        return result;
    }

    template <class T>
    matrix<T>& matrix<T>::operator+=(const matrix<T>& other)
    {
        for (size_t i(0); i < rows(); ++i)
            for (size_t j(0); j < columns(); ++j)
                table_[i][j] += other.table_[i][j];
        return *this;
    }

    template <class T>
    matrix<T> matrix<T>::operator-(const matrix<T>& other) const
    {
        matrix<T> result;
        for (size_t i(0); i < rows(); ++i)
            for (size_t j(0); j < columns(); ++j)
                result[i][j] = table_[i][j] - other.table_[i][j];
        return result;
    }

    template <class T>
    matrix<T>& matrix<T>::operator-=(const matrix<T>& other)
    {
        for (size_t i(0); i < rows(); ++i)
            for (size_t j(0); j < columns(); ++j)
                table_[i][j] -= other[i][j];
        return *this;
    }

    template <class T>
    matrix<T> matrix<T>::transposed_matrix() const
    {
        matrix<T> result(columns_, rows_);
        for (size_t i(0); i < columns(); ++i)
            for (size_t j(0); j < rows(); ++j)
                result[i][j] = table_[j][i];
        return result;
    }

    template <class T>
    matrix<T> matrix<T>::minor_matrix(size_t row, size_t column) const
    {
        matrix<T> minor(rows_ - 1, columns_ - 1);
        size_t i(0);
        // upper half
        for (; i < row; ++i)
        {
            // left rectangle
            for (size_t j(0); j < column; ++j)
                minor(i, j) = table_[i][j];
            // right rectangle
            for (size_t k(column + 1); k < columns_; ++k)
                minor(i, k - 1) = table_[i][k];
        }
        i++;
        // lower half
        for (; i < rows_; ++i)
        {
            // left rectangle
            for (size_t j(0); j < column; ++j)
                minor(i - 1, j) = table_[i][j];
            // right rectangle
            for (size_t k(column + 1); k < columns_; ++k)
                minor(i - 1, k - 1) = table_[i][k];
        }
        return minor;
    }

    template <class T>
    T matrix<T>::minor(size_t row, size_t column) const
    {
        if (!is_row_valid(row))
            throw out_of_range("Row index out of range");
        if (!is_column_valid(column))
            throw out_of_range("Column index out of range");

        return minor_matrix(row, column).determinant();
    }


    template <class T>
    matrix<T> matrix<T>::L_decomposition() const
    {
        if (!is_square_matrix())
            throw out_of_range("Matrix is not square");
        auto L(identity_matrix()),
             U(*this);
        for (int i(0); i < rows(); ++i)
            for (int j(i + 1); j < rows(); ++j)
            {
                L(j, i) = U(j, i) / U(i, i);
                for (int k(i); k < rows(); ++k)
                    U(j, k) -= U(i, k) * L(j, i);
            }

        return L;
    }

    template <class T>
    matrix<T> matrix<T>::U_decomposition() const
    {
        if (!is_square_matrix())
            throw out_of_range("Matrix is not square");

        auto U(*this);
        for (size_t i(0); i < rows(); ++i)
            for (size_t j(i + 1); j < rows(); ++j)
            {
                T temp(U(j, i) / U(i, i));
                for (size_t k(i); k < rows(); ++k)
                    U(j, k) -= U(i, k) * temp;
            }

        return U;
    }

    template <class T>
    T matrix<T>::algebraic_complement(size_t row, size_t column) const
    {
        if (!is_row_valid(row))
            throw out_of_range("Row index out of range");
        if (!is_column_valid(column))
            throw out_of_range("Column index out of range");

        T m(minor(row, column));
        size_t p(row + 1 + column + 1);

        return m * pow(T(-1), T(p));
    }

    template <class T>
    matrix<T> matrix<T>::union_matrix() const
    {
        if (!is_square_matrix())
            throw out_of_range("Matrix is not square");
        matrix<T> result;
        for (size_t i(0); i < rows(); ++i)
            for (size_t j(0); j < columns(); ++j)
                result(i, j) = algebraic_complement(i, j);
        return result;
    }

    template <class T>
    matrix<T> matrix<T>::inverted_matrix() const
    {
        if (!is_square_matrix())
            throw out_of_range("Matrix is not square");
        T det(determinant());
        if (det == T(0))
            throw std::invalid_argument("Matrix is singular (determinant is zero)");

        matrix<T> inv;
        for (size_t i(0); i < rows(); ++i)
            for (size_t j(0); j < rows(); ++j)
                inv(i, j) = algebraic_complement(j, i) / det;
        return inv;
    }


    template <class T>
    T matrix<T>::determinant() const
    {
        if (!is_square_matrix())
            throw out_of_range("Matrix is not square");
        // Handle special cases for small matrices
        // 1x1
        if (rows_ == 1)
            return table_[0][0];
        // 2x2
        if (rows_ == 2)
            return table_[0][0] * table_[1][1] - table_[0][1] * table_[1][0];
        // 3x3
        // Using Sarrus' rule for 3x3 matrices
        if (rows_ == 3)
            return table_[0][0] * table_[1][1] * table_[2][2]
                + table_[0][1] * table_[1][2] * table_[2][0]
                + table_[0][2] * table_[1][0] * table_[2][1]
                - table_[0][2] * table_[1][1] * table_[2][0]
                - table_[0][1] * table_[1][0] * table_[2][2]
                - table_[0][0] * table_[1][2] * table_[2][1];
        // For larger matrices, use LU decomposition
        // and calculate the product of the diagonal elements of U
        auto U(U_decomposition());
        T determinant(1);
        for (size_t i(0); i < rows(); ++i)
            determinant *= U(i, i);
        return determinant;
    }


    template <class T>
    bool matrix<T>::is_row_valid(size_t row) const
    {
        return row < rows();
    }

    template <class T>
    bool matrix<T>::is_column_valid(size_t column) const
    {
        return column < columns();
    }

    template <class T>
    bool matrix<T>::is_zero_row(size_t row) const
    {
        T zero(0);
        for (auto& value : table_[row])
            if (value != zero)
                return false;
        return true;
    }

    template <class T>
    bool matrix<T>::is_zero_column(size_t column) const
    {
        T zero(0);
        for (auto& row : table_)
            if (row[column] != zero)
                return false;
        return true;
    }

    template <class T>
    bool matrix<T>::is_non_zero_row(size_t row) const
    {
        T zero(0);
        for (auto& value : table_[row])
            if (value == zero)
                return false;
        return true;
    }

    template <class T>
    bool matrix<T>::is_non_zero_column(size_t column) const
    {
        T zero(0);
        for (auto& row : table_)
            if (row[column] == zero)
                return false;
        return true;
    }

    template <class T>
    bool matrix<T>::is_zero_matrix() const
    {
        T zero(0);
        for (auto& row : table_)
            for (auto& value : row)
                if (value != zero)
                    return false;
        return true;
    }

    template <class T>
    bool matrix<T>::is_square_matrix() const
    {
        return rows() == columns();
    }


    template <class T>
    bool matrix<T>::is_vector_row() const
    {
        return rows() == 1;
    }

    template <class T>
    bool matrix<T>::is_vector_column() const
    {
        return columns() == 1;
    }

    template <class T>
    bool matrix<T>::is_diagonal_matrix() const
    {
        if (!is_square_matrix())
            return false;
        T zero(0);
        auto diagonal_elements(main_diagonal());
        for (auto& value : diagonal_elements)
            if (value == zero)
                return false;
        for (int i(0); i < rows(); ++i)
        {
            // upper triangular part
            for (int j(i + 1); j < rows(); ++j)
                if (table_[i][j] != zero)
                    return false;
            // diagonal part
            if (table_[i][i] == zero)
                return false;
            // lower triangular part
            for (int j(0); j < i; ++j)
                if (table_[i][j] != zero)
                    return false;
        }
        return true;
    }

    template <class T>
    bool matrix<T>::is_identity_matrix() const
    {
        if (!is_square_matrix())
            return false;
        T zero(0);
        T one(1);
        auto diagonal_elements(main_diagonal());
        for (auto& value : diagonal_elements)
            if (value == zero)
                return false;
        for (int i(0); i < rows(); ++i)
        {
            // upper triangular part
            for (int j(i + 1); j < rows(); ++j)
                if (table_[i][j] != zero)
                    return false;
            // diagonal part
            if (table_[i][i] != one)
                return false;
            // lower triangular part
            for (int j(0); j < i; ++j)
                if (table_[i][j] != zero)
                    return false;
        }
        return true;
    }

    template <class T>
    bool matrix<T>::is_upper_triangular_matrix() const
    {
        T zero(0);
        for (int i(0); i < rows(); ++i)
        {
            // upper triangular part
            for (int j(i + 1); j < columns(); ++j)
                if (table_[i][j] != zero)
                    return false;
        }
        return true;
    }

    template <class T>
    bool matrix<T>::is_lower_triangular_matrix() const
    {
        T zero(0);
        for (int i(0); i < rows(); ++i)
        {
            // lower triangular part
            for (int j(0); j < i; ++j)
                if (table_[i][j] != zero)
                    return false;
        }
        return true;
    }

    template <class T>
    bool matrix<T>::is_echelon_matrix() const
    {
        T zero(0);
        size_t row(0),
               found_non_zero(columns());

        for (; row < rows(); ++row)
        {
            // here we check if the next line non-zero index
            // is larger than on the previous line
            size_t non_zero(find_non_zero_value(row));
            if (non_zero == columns())
                break;
            if (found_non_zero == columns() || non_zero > found_non_zero)
                found_non_zero = non_zero;
            else if (found_non_zero >= non_zero)
                return false;
        }
        for (; row < rows(); ++row)
            if (!is_zero_row(row))
                return false;
        return true;
    }

    template <class T>
    void matrix<T>::check_validity() const
    {
        if (table_.size() != rows())
            throw std::invalid_argument("Number of rows does not match the size of the table");
        for (const auto& row : table_)
            if (row.size() != columns_)
                throw std::invalid_argument("Number of columns does not match the size of the table");
    }


    template <class T>
    matrix<T> matrix<T>::identity_matrix()
    {
        if (!is_square_matrix())
            throw out_of_range("Matrix is not square");
        matrix<T> identity;

        for (int i(0); i < rows(); ++i)
            identity(i, i) = T(1);

        return identity;
    }

    template <class T>
    matrix<T> matrix<T>::x_rotation_matrix(T theta, size_t rows, size_t columns)
    {
        if (rows < 3 || columns < 3)
            throw invalid_argument("Rotation matrix must be at least 3x3");
        matrix<T> rotation(rows, columns);

        rotation(0, 0) = T(1);
        rotation(1, 1) = cos(theta);
        rotation(1, 2) = -sin(theta);
        rotation(2, 1) = sin(theta);
        rotation(2, 2) = cos(theta);
        if (rows >= 4 && columns >= 4)
            rotation(3, 3) = T(1);
        return rotation;
    }

    template <class T>
    matrix<T> matrix<T>::y_rotation_matrix(T theta, size_t rows, size_t columns)
    {
        if (rows < 3 || columns < 3)
            throw invalid_argument("Rotation matrix must be at least 3x3");
        matrix<T> rotation(rows, columns);

        rotation(0, 0) = cos(theta);
        rotation(0, 2) = sin(theta);
        rotation(2, 0) = -sin(theta);
        rotation(2, 2) = cos(theta);
        rotation(1, 1) = T(1);
        if (rows >= 4 && columns >= 4)
            rotation(3, 3) = T(1);
        return rotation;
    }

    template <class T>
    matrix<T> matrix<T>::z_rotation_matrix(T theta, size_t rows, size_t columns)
    {
        if (rows < 3 || columns < 3)
            throw invalid_argument("Rotation matrix must be at least 3x3");
        matrix<T> rotation(rows, columns);

        rotation(0, 0) = cos(theta);
        rotation(0, 1) = -sin(theta);
        rotation(1, 0) = sin(theta);
        rotation(1, 1) = cos(theta);
        rotation(2, 2) = T(1);
        if (rows >= 4 && columns >= 4)
            rotation(3, 3) = T(1);
        return rotation;
    }

    template <class T>
    matrix<T> matrix<T>::rotation_matrix(point<T> theta, size_t rows, size_t columns)
    {
        if (theta.axes() < 3 || rows < 3 || columns < 3)
            throw invalid_argument("Rotation matrix must be at least 3x3");
        return x_rotation_matrix(theta.coordinate(x), rows, columns) *
            y_rotation_matrix(theta.coordinate(y), rows, columns) *
            z_rotation_matrix(theta.coordinate(z), rows, columns);
    }

    template <class T>
    matrix<T> matrix<T>::projection_matrix(T AspectRatio, T Near, T Far, T FOV, size_t rows, size_t columns)
    {
        
        if (rows < 4 || columns < 4)
            throw invalid_argument("Rotation matrix must be at least 4x4");
        
        matrix<T> rotation(rows, columns);
        T FovRad = T(1) / (tan(FOV / T(360) * T(M_PI)));

        rotation(0, 0) = AspectRatio * FovRad;
        rotation(1, 1) = FovRad;
        rotation(2, 2) = Far / (Far - Near);
        rotation(2, 3) = T(1);
        rotation(3, 2) = (-Far * Near) / (Far - Near);
        
        return rotation;
    }
} // SpaceEngine
#endif
