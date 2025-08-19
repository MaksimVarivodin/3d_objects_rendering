//
// Created by maksymvarivodin on 7/29/24.
//
#ifndef MATRIX_INL
#define MATRIX_INL


namespace engine_lib
{
    using namespace std;

    template <class T, size_t N, size_t M>
    matrix<T, N, M>::matrix()
        : table_({})
    {
    }

    template <class T, size_t N, size_t M>
    matrix<T, N, M>::matrix(const array<array<T, M>, N>& data)
        : table_(data)
    {
    }


    template <class T, size_t N, size_t M>
    matrix<T, N, M>::matrix(const array<point<T, M>, N>& data)
    {
        for (int i(0); i < N; ++i)
            assert(data[i].axes() == M, "All rows must have the same size");

        for (int i(0); i < N; ++i)
            this->table_[i] = data[i].get_coordinates();
    }


    template <class T, size_t N, size_t M>
    matrix<T, N, M>::matrix(const array<direction<T, M>, N>& data)
    {
        for (int i(0); i < N; ++i)
            assert(data[i].axes() == M);

        for (int i(0); i < N; ++i)
            this->table_[i] = data[i].get_coordinates();
    }


    template <class T, size_t N, size_t M>
    matrix<T, N, M>::matrix(const matrix<T, N, M>& other)
        : table_(other.table_)
    {
    }

    template <class T, size_t N, size_t M>
    size_t matrix<T, N, M>::rows() const
    {
        return N;
    }

    template <class T, size_t N, size_t M>
    const array<T, M>& matrix<T, N, M>::get_row(size_t row) const
    {
        if (row < N)
            return &table_[row];
    }

    template <class T, size_t N, size_t M>
    const array<array<T, M>, N>& matrix<T, N, M>::get_table() const
    {
        return table_;
    }

    template <class T, size_t N, size_t M>
    array<array<T, M>, N>& matrix<T, N, M>::ref_table()
    {
        return table_;
    }

    template <class T, size_t N, size_t M>
    size_t matrix<T, N, M>::columns() const
    {
        return M;
    }


    template <class T, size_t N, size_t M>
    T& matrix<T, N, M>::operator()(size_t row, size_t column)
    {
        if (!is_row_valid(row))
            throw std::out_of_range("Invalid row index");
        if (!is_column_valid(column))
            throw std::out_of_range("Invalid column index");
        return table_[row][column];
    }

    template <class T, size_t N, size_t M>
    const T& matrix<T, N, M>::operator()(size_t row, size_t column) const
    {
        if (!is_row_valid(row))
            throw std::out_of_range("Invalid row index");
        if (!is_column_valid(column))
            throw std::out_of_range("Invalid column index");
        return table_[row][column];
    }


    template <class T, size_t N, size_t M>
    size_t matrix<T, N, M>::find_non_zero_value(size_t row) const
    {
        T zero(0);
        for (size_t i(0); i < M; ++i)
            if (table_[row][i] != zero)
                return i;
        return M;
    }

    template <class T, size_t N, size_t M>
    array<T, N> matrix<T, N, M>::main_diagonal() const
    {
        array<T, N> result({0});
        for (size_t i(0); i < N; ++i)
            result[i] = table_[i][i];
        return result;
    }

    template <class T, size_t N, size_t M>
    array<T, N> matrix<T, N, M>::secondary_diagonal() const
    {
        array<T, N> result({0});
        for (size_t i(0); i < N; ++i)
            result[i] = table_[N - 1 - i][i];
        return result;
    }

    template <class T, size_t N, size_t M>
    T matrix<T, N, M>::trace() const
    {
        auto diagonal(main_diagonal());
        T sum(0);
        for (auto& value : diagonal)
            sum += value;
        return sum;
    }

    template <class T, size_t N, size_t M>
    matrix<T, N, M> matrix<T, N, M>::operator+(T value) const
    {
        matrix result;
        for (size_t i(0); i < N; ++i)
            for (size_t j(0); j < M; ++j)
                result[i][j] = table_[i][j] + value;
        return result;
    }

    template <class T, size_t N, size_t M>
    matrix<T, N, M>& matrix<T, N, M>::operator+=(T value)
    {
        for (size_t i(0); i < N; ++i)
            for (size_t j(0); j < M; ++j)
                table_[i][j] += value;
        return *this;
    }

    template <class T, size_t N, size_t M>
    matrix<T, N, M> matrix<T, N, M>::operator-(T value) const
    {
        matrix result;
        for (size_t i(0); i < N; ++i)
            for (size_t j(0); j < M; ++j)
                result[i][j] = table_[i][j] - value;
        return result;
    }

    template <class T, size_t N, size_t M>
    matrix<T, N, M>& matrix<T, N, M>::operator-=(T value)
    {
        for (size_t i(0); i < N; ++i)
            for (size_t j(0); j < M; ++j)
                table_[i][j] -= value;
        return *this;
    }

    template <class T, size_t N, size_t M>
    matrix<T, N, M> matrix<T, N, M>::operator*(T value) const
    {
        matrix<T, N, M> result;
        for (size_t i(0); i < N; ++i)
            for (size_t j(0); j < M; ++j)
                result[i][j] = table_[i][j] * value;
        return result;
    }

    template <class T, size_t N, size_t M>
    matrix<T, N, M>& matrix<T, N, M>::operator*=(T value)
    {
        for (size_t i(0); i < N; ++i)
            for (size_t j(0); j < M; ++j)
                table_[i][j] *= value;
        return *this;
    }

    template <class T, size_t N, size_t M>
    matrix<T, N, M> matrix<T, N, M>::operator/(T value) const
    {
        if (value == T(0))
            throw invalid_argument("Division by zero");
        matrix<T, N, M> result;
        for (size_t i(0); i < N; ++i)
            for (size_t j(0); j < M; ++j)
                result[i][j] = table_[i][j] / value;
        return result;
    }

    template <class T, size_t N, size_t M>
    matrix<T, N, M>& matrix<T, N, M>::operator/=(T value)
    {
        if (value == T(0))
            throw invalid_argument("Division by zero");

        for (size_t i(0); i < N; ++i)
            for (size_t j(0); j < M; ++j)
                table_[i][j] /= value;
        return *this;
    }

    template <class T, size_t N, size_t M>
    template <size_t G, size_t H>
    matrix<T, N, H> matrix<T, N, M>::operator*(const matrix<T, G, H>& other) const
    {
        if (M != G)
            throw invalid_argument("Matrices dimensions mismatch");

        matrix<T, N, H> result;

        for (int i(0); i < N; ++i)
            for (int j(0); j < H; ++j)
                for (int k(0); k < M; ++k)
                    result(i, j) += table_[i][k] * other(k, j);
        return result;
    }

    template <class T, size_t N, size_t M>
    template <size_t G, size_t H>
    matrix<T, N, H>& matrix<T, N, M>::operator*=(const matrix<T, G, H>& other)
    {
        *this = this->operator*(other);
        return *this;
    }

    template <class T, size_t N, size_t M>
    template <size_t G, size_t H>
    matrix<T, N, H> matrix<T, N, M>::operator/(const matrix<T, G, H>& other) const
    {
        if (M != G)
            throw invalid_argument("Matrices dimensions mismatch");

        matrix<T, N, H> result({{}});

        for (int i(0); i < N; ++i)
            for (int j(0); j < H; ++j)
                for (int k(0); k < M; ++k)
                {
                    if (other[k][j] == T(0))
                        throw invalid_argument("Division by zero in matrix division");
                    result[i][j] += table_[i][k] / other[k][j];
                }

        return result;
    }

    template <class T, size_t N, size_t M>
    template <size_t G, size_t H>
    matrix<T, N, H>& matrix<T, N, M>::operator/=(const matrix<T, G, H>& other)
    {
        *this = this->operator/(other);
        return *this;
    }

    template <class T, size_t N, size_t M>
    matrix<T, N, M> matrix<T, N, M>::operator+(const matrix<T, N, M>& other) const
    {
        matrix<T, N, M> result;
        for (size_t i(0); i < N; ++i)
            for (size_t j(0); j < M; ++j)
                result.table_[i][j] = table_[i][j] + other.table_[i][j];
        return result;
    }

    template <class T, size_t N, size_t M>
    matrix<T, N, M>& matrix<T, N, M>::operator+=(const matrix<T, N, M>& other)
    {
        for (size_t i(0); i < N; ++i)
            for (size_t j(0); j < M; ++j)
                table_[i][j] += other.table_[i][j];
        return *this;
    }

    template <class T, size_t N, size_t M>
    matrix<T, N, M> matrix<T, N, M>::operator-(const matrix<T, N, M>& other) const
    {
        matrix<T, N, M> result;
        for (size_t i(0); i < N; ++i)
            for (size_t j(0); j < M; ++j)
                result[i][j] = table_[i][j] - other.table_[i][j];
        return result;
    }

    template <class T, size_t N, size_t M>
    matrix<T, N, M>& matrix<T, N, M>::operator-=(const matrix<T, N, M>& other)
    {
        for (size_t i(0); i < N; ++i)
            for (size_t j(0); j < M; ++j)
                table_[i][j] -= other[i][j];
        return *this;
    }

    template <class T, size_t N, size_t M>
    matrix<T, M, N> matrix<T, N, M>::transposed_matrix() const
    {
        matrix<T, M, N> result;
        for (size_t i(0); i < M; ++i)
            for (size_t j(0); j < N; ++j)
                result[i][j] = table_[j][i];
        return result;
    }

    template <class T, size_t N, size_t M>
    matrix<T, N - 1, M - 1> matrix<T, N, M>::minor_matrix(size_t row, size_t column) const
    {
        matrix<T, N - 1, M - 1> minor;
        int i(0);
        // upper half
        for (; i < row; ++i)
        {
            // left rectangle
            for (int j(0); j < column; ++j)
                minor(i, j) = table_[i][j];
            // right rectangle
            for (int k(column + 1); k < M; ++k)
                minor(i, k - 1) = table_[i][k];
        }
        i++;
        // lower half
        for (; i < N; ++i)
        {
            // left rectangle
            for (int j(0); j < column; ++j)
                minor(i - 1, j) = table_[i][j];
            // right rectangle
            for (int k(column + 1); k < M; ++k)
                minor(i - 1, k - 1) = table_[i][k];
        }
        return minor;
    }

    template <class T, size_t N, size_t M>
    T matrix<T, N, M>::minor(size_t row, size_t column) const
    {
        if (!is_row_valid(row))
            throw out_of_range("Row index out of range");
        if (!is_column_valid(column))
            throw out_of_range("Column index out of range");

        return minor_matrix(row, column).determinant();
    }


    template <class T, size_t N, size_t M>
    matrix<T, N, M> matrix<T, N, M>::L_decomposition() const
    {
        static_assert(N == M, "Matrix must be square for LU decomposition");
        auto L(identity_matrix()),
             U(*this);
        for (int i(0); i < N; ++i)
            for (int j(i + 1); j < N; ++j)
            {
                L(j, i) = U(j, i) / U(i, i);
                for (int k(i); k < N; ++k)
                    U(j, k) -= U(i, k) * L(j, i);
            }

        return L;
    }

    template <class T, size_t N, size_t M>
    matrix<T, N, M> matrix<T, N, M>::U_decomposition() const
    {
        assert(N == M, "Matrix must be square for LU decomposition");
        auto U(*this);
        for (int i(0); i < N; ++i)
            for (int j(i + 1); j < N; ++j)
            {
                T temp(U(j, i) / U(i, i));
                for (int k(i); k < N; ++k)
                    U(j, k) -= U(i, k) * temp;
            }

        return U;
    }

    template <class T, size_t N, size_t M>
    T matrix<T, N, M>::algebraic_complement(size_t row, size_t column) const
    {
        if (!is_row_valid(row))
            throw out_of_range("Row index out of range");
        if (!is_column_valid(column))
            throw out_of_range("Column index out of range");

        T m(minor(row, column));
        size_t p(row + 1 + column + 1);

        return m * pow(T(-1), T(p));
    }

    template <class T, size_t N, size_t M>
    matrix<T, N, M> matrix<T, N, M>::union_matrix() const
    {
        static_assert(N == M, "Matrix must be square for union");
        matrix<T, N, M> result;
        for (size_t i(0); i < N; ++i)
            for (size_t j(0); j < M; ++j)
                result(i, j) = algebraic_complement(i, j);
        return result;
    }

    template <class T, size_t N, size_t M>
    matrix<T, N, M> matrix<T, N, M>::inverted_matrix() const
    {
        static_assert(N == M, "Matrix must be square for inverse calculation");
        T det(determinant());
        if (det == T(0))
            throw std::invalid_argument("Matrix is singular (determinant is zero)");

        matrix<T, N, M> inv;
        for (size_t i(0); i < N; ++i)
            for (size_t j(0); j < N; ++j)
                inv(i, j) = algebraic_complement(j, i) / det;
        return inv;
    }


    template <class T, size_t N, size_t M>
    T matrix<T, N, M>::determinant() const
    {
        assert(N == M, "Matrix must be square for determinant calculation");
        auto U(U_decomposition());
        T determinant(1);
        for (int i(0); i < N; ++i)
            determinant *= U(i, i);
        return determinant;
    }


    template <class T, size_t N, size_t M>
    bool matrix<T, N, M>::is_row_valid(size_t row) const
    {
        return row < N;
    }

    template <class T, size_t N, size_t M>
    bool matrix<T, N, M>::is_column_valid(size_t column) const
    {
        return column < M;
    }

    template <class T, size_t N, size_t M>
    bool matrix<T, N, M>::is_zero_row(size_t row) const
    {
        T zero(0);
        for (auto& value : table_[row])
            if (value != zero)
                return false;
        return true;
    }

    template <class T, size_t N, size_t M>
    bool matrix<T, N, M>::is_zero_column(size_t column) const
    {
        T zero(0);
        for (auto& row : table_)
            if (row[column] != zero)
                return false;
        return true;
    }

    template <class T, size_t N, size_t M>
    bool matrix<T, N, M>::is_non_zero_row(size_t row) const
    {
        T zero(0);
        for (auto& value : table_[row])
            if (value == zero)
                return false;
        return true;
    }

    template <class T, size_t N, size_t M>
    bool matrix<T, N, M>::is_non_zero_column(size_t column) const
    {
        T zero(0);
        for (auto& row : table_)
            if (row[column] == zero)
                return false;
        return true;
    }

    template <class T, size_t N, size_t M>
    bool matrix<T, N, M>::is_zero_matrix() const
    {
        T zero(0);
        for (auto& row : table_)
            for (auto& value : row)
                if (value != zero)
                    return false;
        return true;
    }

    template <class T, size_t N, size_t M>
    bool matrix<T, N, M>::is_square_matrix() const
    {
        return N == M;
    }


    template <class T, size_t N, size_t M>
    bool matrix<T, N, M>::is_vector_row() const
    {
        return N == 1;
    }

    template <class T, size_t N, size_t M>
    bool matrix<T, N, M>::is_vector_column() const
    {
        return M == 1;
    }

    template <class T, size_t N, size_t M>
    bool matrix<T, N, M>::is_diagonal_matrix() const
    {
        if (!is_square_matrix())
            return false;
        T zero(0);
        auto diagonal_elements(main_diagonal());
        for (auto& value : diagonal_elements)
            if (value == zero)
                return false;
        for (int i(0); i < N; ++i)
        {
            // upper triangular part
            for (int j(i + 1); j < N; ++j)
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

    template <class T, size_t N, size_t M>
    bool matrix<T, N, M>::is_identity_matrix() const
    {
        if (!is_square_matrix())
            return false;
        T zero(0);
        T one(1);
        auto diagonal_elements(main_diagonal());
        for (auto& value : diagonal_elements)
            if (value == zero)
                return false;
        for (int i(0); i < N; ++i)
        {
            // upper triangular part
            for (int j(i + 1); j < N; ++j)
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

    template <class T, size_t N, size_t M>
    bool matrix<T, N, M>::is_upper_triangular_matrix() const
    {
        T zero(0);
        for (int i(0); i < N; ++i)
        {
            // upper triangular part
            for (int j(i + 1); j < M; ++j)
                if (table_[i][j] != zero)
                    return false;
        }
        return true;
    }

    template <class T, size_t N, size_t M>
    bool matrix<T, N, M>::is_lower_triangular_matrix() const
    {
        T zero(0);
        for (int i(0); i < N; ++i)
        {
            // lower triangular part
            for (int j(0); j < i; ++j)
                if (table_[i][j] != zero)
                    return false;
        }
        return true;
    }

    template <class T, size_t N, size_t M>
    bool matrix<T, N, M>::is_echelon_matrix() const
    {
        T zero(0);
        size_t row(0),
               found_non_zero(M);

        for (; row < N; ++row)
        {
            // here we check if the next line non-zero index
            // is larger than on the previous line
            size_t non_zero(find_non_zero_value(row));
            if (non_zero == M)
                break;
            if (found_non_zero == M || non_zero > found_non_zero)
                found_non_zero = non_zero;
            else if (found_non_zero >= non_zero)
                return false;
        }
        for (; row < N; ++row)
            if (!is_zero_row(row))
                return false;
        return true;
    }

    template <class T, size_t N, size_t M>
    matrix<T, N, M> matrix<T, N, M>::identity_matrix()
    {
        static_assert(N == M, "Matrix dimensions must be equal");
        matrix<T, N, M> identity;

        for (int i(0); i < N; ++i)
            identity(i, i) = T(1);

        return identity;
    }

    template <class T>
    matrix1x1<T>::matrix1x1()
        : matrix<T, 1, 1>()
    {
    }

    template <class T>
    matrix1x1<T>::matrix1x1(const array<array<T, 1>, 1>& data)
        : matrix<T, 1, 1>(data)
    {
    }

    template <class T>
    matrix1x1<T>::matrix1x1(const matrix1x1<T>& other)
        : matrix<T, 1, 1>(other)
    {
    }

    template <class T>
    matrix1x1<T>::matrix1x1(const matrix<T, 1, 1>& other)
        : matrix<T, 1, 1>(other)
    {
    }

    template <class T>
    T matrix1x1<T>::determinant() const
    {
        return (*this)(0, 0);
    }

    template <class T>
    matrix2x2<T>::matrix2x2()
        : matrix<T, 2, 2>()
    {
    }

    template <class T>
    matrix2x2<T>::matrix2x2(const matrix2x2<T>& other)
        : matrix<T, 2, 2>(other)
    {
    }

    template <class T>
    matrix2x2<T>::matrix2x2(const array<array<T, 2>, 2>& data)
        : matrix<T, 2, 2>(data)
    {
    }

    template <class T>
    matrix2x2<T>::matrix2x2(const matrix<T, 2, 2>& other)
        : matrix<T, 2, 2>(other)
    {
    }

    template <class T>
    T matrix2x2<T>::determinant() const
    {
        return matrix<T, 2, 2>::operator()(0, 0) * matrix<T, 2, 2>::operator()(1, 1)
            - matrix<T, 2, 2>::operator()(0, 1) * matrix<T, 2, 2>::operator()(1, 0);
    }

    template <class T>
    matrix3x3<T>::matrix3x3()
        : matrix<T, 3, 3>()
    {
    }

    template <class T>
    matrix3x3<T>::matrix3x3(const matrix3x3<T>& other)
        : matrix<T, 3, 3>(other)
    {
    }

    template <class T>
    matrix3x3<T>::matrix3x3(const array<array<T, 3>, 3>& data)
        : matrix<T, 3, 3>(data)
    {
    }

    template <class T>
    matrix3x3<T>::matrix3x3(const matrix<T, 3, 3>& other)
        : matrix<T, 3, 3>(other)
    {
    }

    template <class T>
    T matrix3x3<T>::determinant() const
    {
        T main_tr1(
              this->operator()(0, 0) *
              this->operator()(1, 1) *
              this->operator()(2, 2)),
          main_tr2(
              this->operator()(2, 1) *
              this->operator()(1, 0) *
              this->operator()(0, 2)),
          main_tr3(
              this->operator()(0, 1) *
              this->operator()(1, 2) *
              this->operator()(2, 0)),
          sec_tr1(
              this->operator()(2, 0) *
              this->operator()(1, 1) *
              this->operator()(0, 2)),
          sec_tr2(
              this->operator()(1, 0) *
              this->operator()(0, 1) *
              this->operator()(2, 2)),
          sec_tr3(
              this->operator()(0, 0) *
              this->operator()(1, 2) *
              this->operator()(2, 1));
        return (main_tr1 + main_tr2 + main_tr3) - (sec_tr1 + sec_tr2 + sec_tr3);
    }

    template <class T, size_t M>
    matrix1D<T, M>::matrix1D(const direction<T, M>& data)
        : matrix<T, 1, M>(array{data})
    {
    }

    template <class T, size_t M>
    matrix1D<T, M>::matrix1D(const array<T, M>& data)
        : matrix<T, 1, M>(array{data})
    {
    }

    template <class T, size_t M>
    matrix1D<T, M>::matrix1D()
        : matrix<T, 1, M>({})
    {
    }

    template <class T, size_t M>
    template <size_t N>
    matrix1D<T, M>::matrix1D(const matrix<T, N, M>& other)
    {
        static_assert(N == 1, "Matrix must have one row");
        matrix<T, 1, M>::ref_table() = other.get_table();        
    }

    template <class T, size_t M>
    matrix1D<T, M>::matrix1D(const point<T, M>& data)
        : matrix<T, 1, M>(array{data})
    {
    }
} // engine_lib
#endif
