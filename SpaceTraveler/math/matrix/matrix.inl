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
            table_[i] = data[i].get_radius_direction().get_coordinates();
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
        matrix<T> result(rows_, columns_);
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
        matrix<T> result(rows_, columns_);
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
                    result(i, j) += table_[j][k] * other(k, i);
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
                    result[i][j] += table_[j][k] / other[k][i];
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
        matrix<T> result(rows_, columns_);
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
        matrix<T> result(rows_, columns_);
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
        auto L(identity_matrix(rows_)),
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
        matrix<T> result(rows_, columns_);
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
    matrix<T> matrix<T>::identity_matrix(size_t rows_columns)
    {
        matrix<T> identity(rows_columns, rows_columns);

        for (size_t i(0); i < rows_columns; ++i)
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
        rotation(1, 2) = sin(theta);
        rotation(2, 1) = -sin(theta);
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
        rotation(0, 1) = sin(theta);
        rotation(1, 0) = -sin(theta);
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
        /*if (rows < 4 || columns < 4)
            throw invalid_argument("Rotation matrix must be at least 4x4");

        matrix<T> rotation(rows, columns);
        T FovRad = T(1) / (tan(FOV* T(M_PI) / T(360) ));

        rotation(0, 0) = AspectRatio * FovRad;
        rotation(1, 1) = FovRad;
        rotation(2, 2) = Far / (Far - Near);
        rotation(2, 3) = (-Far * Near) / (Far - Near);
        rotation(3, 2) = T(1);
        
        rotation(3, 3) = T(0);
        return rotation;*/
        if (rows < 4 || columns < 4)
            throw invalid_argument("Projection matrix must be at least 4x4");

        matrix<T> proj(rows, columns);
        T FovRad = T(1) / tan(FOV * T(0.5) * (T(M_PI) / T(180)));

        proj(0, 0) = AspectRatio * FovRad;
        proj(1, 1) = FovRad;
        proj(2, 2) = Far / (Far - Near);
        proj(2, 3) = (-Far * Near) / (Far - Near);
        proj(3, 2) = T(1);
        proj(3, 3) = T(0);
        return proj;
    }

    template <class T>
    matrix<T> matrix<T>::translation_matrix(point<T> translation)
    {
        if (translation.axes() < 1)
            throw invalid_argument("Translation must have at least one axis");
        matrix<T> translation_matrix(identity_matrix(translation.axes()));
        /*
            [1  ][      ][      ][  ]
            [   ][1     ][      ][  ]
            [   ][      ][1     ][  ]
            [tx ][ty    ][tz    ][1 ]
         */
        for (size_t i = 0; i < translation.axes() - 1; i++)
            translation_matrix(translation.axes() - 1,i ) = translation.coordinate(i);

        return translation_matrix;
    }

    template <class T>
    inline matrix<T> matrix<T>::point_at(const point<T>& pos, const point<T>& target, const point<T>& up)
    {
        /*auto forwardDir = direction(target - pos).get_unit_direction().get_end();
        auto a = forwardDir * direction(up).dot_product(forwardDir);
        auto newUpDir = direction(up - a).get_unit_direction();
        auto rightDir = newUpDir.cross_product(forwardDir).get_unit_direction();

        point<T> r = rightDir.get_end();
        point<T> u = newUpDir.get_end();
        point<T> f = forwardDir;

        matrix<T> m = identity_matrix(4);
        
        m(0,0)=r[x]; m(0, 1)=r[y]; m(0, 2)=r[z];m(0, 3)= T(0);
        m(1,0)=u[x]; m(1, 1)=u[y]; m(1, 2)=u[z];m(1, 3)= T(0);
        m(2,0)=f[x]; m(2, 1)=f[y]; m(2, 2)=f[z];m(2, 3)= T(0);
        m(3,0)=pos.coordinate(x);
        m(3,1)=pos.coordinate(y);
        m(3,2)=pos.coordinate(z);
        m(3,3)= T(1);
        return m;*/
        /*
            [ rx  ux  fx  0 ]
            [ ry  uy  fy  0 ]
            [ rz  uz  fz  0 ]
            [ tx  ty  tz  1 ]
         */

        
        auto forwardDir = direction(target - pos).get_unit_direction();
        auto a = forwardDir.get_end() * direction(up).dot_product(forwardDir);
        auto newUpDir = direction(up - a).get_unit_direction();
        auto rightDir = newUpDir.cross_product(forwardDir);

        point<T> r = rightDir.get_end();
        point<T> u = newUpDir.get_end();
        point<T> f = forwardDir.get_end();

        matrix<T> m = identity_matrix(4);
    
        m(0,0)=r[x]; m(0, 1)=u[x]; m(0, 2)=f[x]; m(0, 3)=pos.coordinate(x);
        m(1,0)=r[y]; m(1, 1)=u[y]; m(1, 2)=f[y]; m(1, 3)=pos.coordinate(y);
        m(2,0)=r[z]; m(2, 1)=u[z]; m(2, 2)=f[z]; m(2, 3)=pos.coordinate(z);
        m(3,0)=T(0); m(3, 1)=T(0); m(3, 2)=T(0); m(3, 3)=T(1);
    
        return m;
    }

    template <class T>
    matrix<T> matrix<T>::look_at(const point<T>& pos, const point<T>& target, const point<T>& up)
    {
        /*matrix<T> m = point_at(pos, target, up);
        
        matrix<T> inv = matrix(pos.axes(), pos.axes());
        
        for (int i=0;i<3;++i)
            for (int j=0;j<3;++j)
                inv(i,j) = m(j,i);
        inv(0, 3) = T(0);
        inv(1, 3) = T(0);
        inv(2, 3) = T(0);
/*
        matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
        matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
        matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
                
 #1#
        inv(3, 0 ) = -(m(3, 0) * inv(0, 0) + m(3, 1) * inv(1, 0) + m(3, 2) * inv(2, 0));
        inv(3, 1 ) = -(m(3, 0) * inv(0, 1) + m(3, 1) * inv(1, 1) + m(3, 2) * inv(2, 1));
        inv(3, 2 ) = -(m(3, 0) * inv(0, 2) + m(3, 1) * inv(1, 2) + m(3, 2) * inv(2, 2));
        inv(3, 3 ) = T(1);
        return inv;*/
        /*matrix<T> m = point_at(pos, target, up);
    
        // Быстрое инвертирование для ортонормальной матрицы вида
        matrix<T> inv(4, 4);
    
        // Транспонирование части вращения 3x3
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                inv(i, j) = m(j, i);

        // Вычисление нового смещения
        inv(0, 3) = -(m(0, 0) * m(0, 3) + m(1, 0) * m(1, 3) + m(2, 0) * m(2, 3));
        inv(1, 3) = -(m(0, 1) * m(0, 3) + m(1, 1) * m(1, 3) + m(2, 1) * m(2, 3));
        inv(2, 3) = -(m(0, 2) * m(0, 3) + m(1, 2) * m(1, 3) + m(2, 2) * m(2, 3));
    
        inv(3, 0) = T(0);
        inv(3, 1) = T(0);
        inv(3, 2) = T(0);
        inv(3, 3) = T(1);
    
        return inv;*/

        // Вектор "вперед" (новый Z)
        auto forward = direction<T>(target - pos).get_unit_direction();

        // Вектор "вверх" (новый Y)
        auto a = forward.get_end() * direction<T>(up).dot_product(forward);
        auto up_dir = direction<T>(up - a).get_unit_direction();

        // Вектор "вправо" (новый X)
        auto right_dir = up_dir.cross_product(forward);

        point<T> r = right_dir.get_end();
        point<T> u = up_dir.get_end();
        point<T> f = forward.get_end();

        matrix<T> m(4, 4);

        m(0, 0) = r.coordinate(x); m(0, 1) = r.coordinate(y); m(0, 2) = r.coordinate(z); m(0, 3) = -direction<T>(pos).dot_product(right_dir);
        m(1, 0) = u.coordinate(x); m(1, 1) = u.coordinate(y); m(1, 2) = u.coordinate(z); m(1, 3) = -direction<T>(pos).dot_product(up_dir);
        m(2, 0) = f.coordinate(x); m(2, 1) = f.coordinate(y); m(2, 2) = f.coordinate(z); m(2, 3) = -direction<T>(pos).dot_product(forward);
        m(3, 0) = T(0);            m(3, 1) = T(0);            m(3, 2) = T(0);            m(3, 3) = T(1);

        return m;
    }


    template <class T>
    point<T> point<T>::operator*(const matrix<T>& m) const
    {
        if (axes() != m.columns())
            throw invalid_argument("Point axes must match matrix columns for multiplication.");

        point<T> result(m.rows());
        for (size_t i = 0; i < m.rows(); ++i)
        {
            T sum = T(0);
            for (size_t j = 0; j < axes(); ++j)
            {
                sum += m(i, j) * coordinate(j);
            }
            result[i] = sum;
        }

        // Handle homogeneous coordinate w
        if (result.axes() == 4)
        {
            T w = result.coordinate(3);
            if (w != T(0) && w != T(1))
            {
                for (size_t i = 0; i < 3; ++i)
                {
                    result[i] /= w;
                }
            }
        }
        return result;
    }

    template <class T>
    point<T>& point<T>::operator*=(const matrix<T>& m)
    {
        *this = *this * m;
        return *this;
    }
} // SpaceEngine
#endif
