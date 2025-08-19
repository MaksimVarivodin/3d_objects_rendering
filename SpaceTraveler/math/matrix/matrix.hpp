//
// Created by maksymvarivodin on 7/29/24.
//

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "../point/point.hpp"
#include "../direction/direction.hpp"

namespace engine_lib
{
    using namespace std;

    /**
    * @brief Template class representing a matrix of size NxM.
    *
    * @tparam T Type of elements in the matrix.
    * @tparam N Number of rows in the matrix.
    * @tparam M Number of columns in the matrix.
    */
    template <class T, size_t N, size_t M>
    class matrix
    {
    private:
        /*
         * Table containing the elements of the matrix.
         */
        array<array<T, M>, N> table_;

    public:
        /**
         * @brief Default constructor. Initializes the matrix with zeros.
         */
        matrix();

        /**
         * @brief Constructor that initializes the matrix with the given data.
         *
         * @param data Array of arrays representing the matrix elements.
         */
        matrix(const array<array<T, M>, N>& data);


        /**
         * @brief Constructor that initializes the matrix with the given array of points.
         *
         * @param data Array of points representing the matrix elements.
         */
        matrix(const array<point<T, M>, N>& data);

        /**
         * @brief Constructor that initializes the matrix with the given array of directions.
         *
         * @param data Array of directions representing the matrix elements.
         */
        matrix(const array<direction<T, M>, N>& data);


        /**
         * @brief Copy constructor.
         *
         * @param other Matrix to be copied.
         */
        matrix(const matrix& other);

        /**
         * @brief Returns the number of rows in the matrix.
         *
         * @return Number of rows.
         */
        [[nodiscard]] size_t rows() const;

        /**
         * @brief Returns the row at the specified index.
         *
         * @param row Index of the row to retrieve.
         * @return Reference to the row at the specified index.
         */
        const array<T, M>& get_row(size_t row) const;

        /**
         * @brief Returns the entire table of the matrix.
         *
         * @return Constant reference to the table of the matrix.
         */
        const array<array<T, M>, N>& get_table() const;

        /**
         * @brief Returns a reference to the entire table of the matrix.
         *
         * @return Reference to the table of the matrix.
         */
        array<array<T, M>, N>& ref_table();
        /**
         * @brief Returns the number of columns in the matrix.
         *
         * @return Number of columns.
         */
        [[nodiscard]] size_t columns() const;

        /**
         * @brief Access the element at the given row and column.
         *
         * @param row Row index.
         * @param column Column index.
         * @return Reference to the element at the specified position.
         */
        T& operator()(size_t row, size_t column);

        /**
         * @brief Access the element at the given row and column (const version).
         *
         * @param row Row index.
         * @param column Column index.
         * @return Const reference to the element at the specified position.
         */
        const T& operator()(size_t row, size_t column) const;

        /**
         * @brief Find the index of the first non-zero element in the given row.
         *
         * @param row Row index.
         * @return Index of the first non-zero element or N if all elements are zero.
         */
        [[nodiscard]] size_t find_non_zero_value(size_t row) const;

        /**
         * @brief Get the main diagonal elements of the matrix.
         *
         * @return Array containing the main diagonal elements.
         */
        array<T, N> main_diagonal() const;

        /**
         * @brief Get the secondary diagonal elements of the matrix.
         *
         * @return Array containing the secondary diagonal elements.
         */
        array<T, N> secondary_diagonal() const;

        /**
         * @brief Calculate the trace of the matrix.
         *
         * @return Trace of the matrix.
         */
        T trace() const;

        /**
         * @brief Add a scalar value to the matrix.
         * * @param value Scalar value to add.
         * @return New matrix resulting from the addition.
         * @note This operation adds the scalar value to each element of the matrix.
         */
        matrix operator+(T value) const;

        /**
         * @brief Add a scalar value to the matrix (in-place).
         * @param value Scalar value to add.
         * @return Reference to the modified matrix.
         * @note This operation adds the scalar value to each element of the matrix.
         */
        matrix& operator+=(T value);

        /**
         * @brief Subtract a scalar value from the matrix.
         *
         * @param value Scalar value to subtract.
         * @return New matrix resulting from the subtraction.
         */
        matrix operator-(T value) const;

        /**
         * @brief  Subtract a scalar value from the matrix (in-place).
         * @param value Scalar value to subtract.
         * @return Reference to the modified matrix.
         * @note This operation subtracts the scalar value from each element of the matrix.
         */
        matrix& operator-=(T value);

        /**
         * @brief Multiply the matrix by a scalar value.
         *
         * @param value Scalar value.
         * @return New matrix resulting from the multiplication.
         */
        matrix operator*(T value) const;

        /**
         * @brief Multiply the matrix by a scalar value (in-place).
         *
         * @param value Scalar value.
         * @return Reference to the modified matrix.
         */
        matrix& operator*=(T value);

        /**
         * @brief Divide the matrix by a scalar value.
         *
         * @param value Scalar value.
         * @return New matrix resulting from the division.
         */
        matrix operator/(T value) const;

        /**
         * @brief Divide the matrix by a scalar value (in-place).
         *
         * @param value Scalar value.
         * @return Reference to the modified matrix.
         */
        matrix& operator/=(T value);

        /**
         * @brief Multiply the matrix by another matrix.
         *
         * @tparam G Number of columns in the other matrix.
         * @tparam H Number of columns in the resulting matrix.
         * @param other Matrix to multiply with.
         * @return New matrix resulting from the multiplication.
         */
        template <size_t G, size_t H>
        matrix<T, N, H> operator*(const matrix<T, G, H>& other) const;
        /**
         * @brief Multiply the matrix by another matrix.
         *
         * @tparam G Number of columns in the other matrix.
         * @tparam H Number of columns in the resulting matrix.
         * @param other Matrix to multiply with.
         * @return New matrix resulting from the multiplication.
         */
        template <size_t G, size_t H>
        matrix<T, N, H>& operator*=(const matrix<T, G, H>& other);
        /**
        * @brief Divide the matrix by another matrix.
        *
        * @tparam G Number of columns in the other matrix.
        * @tparam H Number of columns in the resulting matrix.
        * @param other Matrix to divide with.
        * @return New matrix resulting from the division.
        */
        template <size_t G, size_t H>
        matrix<T, N, H> operator/(const matrix<T, G, H>& other) const;
        /**
        * @brief Divide the matrix by another matrix.
        *
        * @tparam G Number of columns in the other matrix.
        * @tparam H Number of columns in the resulting matrix.
        * @param other Matrix to divide with.
        * @return New matrix resulting from the division.
        */
        template <size_t G, size_t H>
        matrix<T, N, H>& operator/=(const matrix<T, G, H>& other);
        /**
         * @brief Add another matrix to the current matrix.
         *
         * @param other Matrix to add.
         * @return New matrix resulting from the addition.
         */
        matrix operator+(const matrix& other) const;

        /**
         * @brief Add another matrix to the current matrix (in-place).
         *
         * @param other Matrix to add.
         * @return Reference to the modified matrix.
         */
        matrix& operator+=(const matrix& other);

        /**
         * @brief Subtract another matrix from the current matrix.
         *
         * @param other Matrix to subtract.
         * @return New matrix resulting from the subtraction.
         */
        matrix operator-(const matrix& other) const;

        /**
         * @brief Subtract another matrix from the current matrix (in-place).
         *
         * @param other Matrix to subtract.
         * @return Reference to the modified matrix.
         */
        matrix& operator-=(const matrix& other);

        /**
         * @brief Calculate the transpose of the matrix.
         *
         * @return New matrix resulting from the transpose operation.
         */
        matrix<T, M, N> transposed_matrix() const;

        /**
         * @brief Calculate the minor matrix by removing the given row and column.
         *
         * @param row Row index to remove.
         * @param column Column index to remove.
         * @return New matrix resulting from the minor operation.
         */
        matrix<T, N - 1, M - 1> minor_matrix(size_t row, size_t column) const;

        /**
         * @brief Calculate the minor of the element at the given row and column.
         *
         * @param row Row index.
         * @param column Column index.
         * @return Minor of the specified element.
         */
        T minor(size_t row, size_t column) const;

        /**
         * @brief Perform L decomposition of the matrix.
         *
         * @return New matrix resulting from the L decomposition.
         */
        matrix L_decomposition() const;

        /**
         * @brief Perform U decomposition of the matrix.
         *
         * @return New matrix resulting from the U decomposition.
         */
        matrix U_decomposition() const;

        /**
         * @brief Calculate the algebraic complement of the element at the given row and column.
         *
         * @param row Row index.
         * @param column Column index.
         * @return Algebraic complement of the specified element.
         */
        T algebraic_complement(size_t row, size_t column) const;

        /**
         * @brief Calculate the union matrix of the current matrix.
         *
         * @return New matrix resulting from the union operation.
         */
        matrix union_matrix() const;

        /**
         * @brief Calculate the inverted matrix of the current matrix.
         *
         * @return New matrix resulting from the inversion operation.
         * @throws std::runtime_error If the matrix is not invertible.
         */
        matrix inverted_matrix() const;

        /**
         * @brief Calculate the determinant of the matrix.
         *
         * @return Determinant of the matrix.
         */
        virtual T determinant() const;

        /**
         * @brief Check if the given row index is valid.
         *
         * @param row Row index.
         * @return True if the row index is valid, false otherwise.
         */
        [[nodiscard]] bool is_row_valid(size_t row) const;

        /**
         * @brief Check if the given column index is valid.
         *
         * @param column Column index.
         * @return True if the column index is valid, false otherwise.
         */
        [[nodiscard]] bool is_column_valid(size_t column) const;

        /**
         * @brief Check if the given row is a zero row.
         *
         * @param row Row index.
         * @return True if the row is a zero row, false otherwise.
         */
        [[nodiscard]] bool is_zero_row(size_t row) const;

        /**
         * @brief Check if the given column is a zero column.
         *
         * @param column Column index.
         * @return True if the column is a zero column, false otherwise.
         */
        [[nodiscard]] bool is_zero_column(size_t column) const;

        /**
         * @brief Check if the given row is a non-zero row.
         *
         * @param row Row index.
         * @return True if the row is a non-zero row, false otherwise.
         */
        [[nodiscard]] bool is_non_zero_row(size_t row) const;

        /**
         * @brief Check if the given column is a non-zero column.
         *
         * @param column Column index.
         * @return True if the column is a non-zero column, false otherwise.
         */
        [[nodiscard]] bool is_non_zero_column(size_t column) const;

        /**
         * @brief Check if the matrix is a zero matrix.
         *
         * @return True if the matrix is a zero matrix, false otherwise.
         */
        [[nodiscard]] bool is_zero_matrix() const;

        /**
         * @brief Check if the matrix is a square matrix.
         *
         * @return True if the matrix is a square matrix, false otherwise.
         */
        [[nodiscard]] bool is_square_matrix() const;

        /**
         * @brief Check if the matrix is a vector row.
         *
         * @return True if the matrix is a vector row, false otherwise.
         */
        [[nodiscard]] bool is_vector_row() const;

        /**
         * @brief Check if the matrix is a vector column.
         *
         * @return True if the matrix is a vector column, false otherwise.
         */
        [[nodiscard]] bool is_vector_column() const;

        /**
         * @brief Check if the matrix is a diagonal matrix.
         *
         * @return True if the matrix is a diagonal matrix, false otherwise.
         */
        [[nodiscard]] bool is_diagonal_matrix() const;

        /**
         * @brief Check if the matrix is an identity matrix.
         *
         * @return True if the matrix is an identity matrix, false otherwise.
         */
        [[nodiscard]] bool is_identity_matrix() const;

        /**
         * @brief Check if the matrix is an upper triangular matrix.
         *
         * @return True if the matrix is an upper triangular matrix, false otherwise.
         */
        [[nodiscard]] bool is_upper_triangular_matrix() const;

        /**
         * @brief Check if the matrix is a lower triangular matrix.
         *
         * @return True if the matrix is a lower triangular matrix, false otherwise.
         */
        [[nodiscard]] bool is_lower_triangular_matrix() const;

        /**
         * @brief Check if the matrix is an echelon matrix.
         *
         * @return True if the matrix is an echelon matrix, false otherwise.
         */
        [[nodiscard]] bool is_echelon_matrix() const;

        /**
         * @brief Virtual destructor.
         */
        virtual ~matrix() = default;

        /**
         * @brief Create an identity matrix of size NxM.
         *
         * @return Identity matrix.
         */
        static matrix identity_matrix();
    };

    /**
     * @brief Specialization of the matrix class for 1x1 matrices.
     *
     * @tparam T Type of elements in the matrix.
     */
    template <class T>
    class matrix1x1 final : public matrix<T, 1, 1>
    {
    public:
        /**
         * @brief Default constructor. Initializes the matrix with zeros.
         */
        matrix1x1<T>();

        /**
         * @brief Copy constructor.
         *
         * @param other Matrix to be copied.
         */
        matrix1x1<T>(const matrix1x1<T>& other);

        /**
         * @brief Constructor that initializes the matrix with the given data.
         *
         * @param data Array of arrays representing the matrix elements.
         */
        matrix1x1<T>(const array<array<T, 1>, 1>& data);

        /**
         * @brief Constructor that initializes the matrix with the given data.
         *
         * @param other Matrix to be copied.
         */
        matrix1x1<T>(const matrix<T, 1, 1>& other);

        /**
         * @brief Calculate the determinant of the matrix.
         *
         * @return Determinant of the matrix.
         */
        T determinant() const override;
    };

    /**
 * @brief Specialization of the matrix class for 2x2 matrices.
 *
 * @tparam T Type of elements in the matrix.
 */
    template <class T>
    class matrix2x2 final : public matrix<T, 2, 2>
    {
    public:
        /**
         * @brief Default constructor. Initializes the matrix with zeros.
         */
        matrix2x2<T>();

        /**
         * @brief Copy constructor.
         *
         * @param other Matrix to be copied.
         */
        matrix2x2<T>(const matrix2x2<T>& other);

        /**
         * @brief Constructor that initializes the matrix with the given data.
         *
         * @param data Array of arrays representing the matrix elements.
         */
        matrix2x2<T>(const array<array<T, 2>, 2>& data);

        /**
         * @brief Constructor that initializes the matrix with the given data.
         *
         * @param other Matrix to be copied.
         */
        matrix2x2<T>(const matrix<T, 2, 2>& other);

        /**
         * @brief Calculate the determinant of the matrix.
         *
         * @return Determinant of the matrix.
         */
        T determinant() const override;
    };

    /**
     * @brief Specialization of the matrix class for 3x3 matrices.
     *
     * @tparam T Type of elements in the matrix.
     */
    template <class T>
    class matrix3x3 final : public matrix<T, 3, 3>
    {
    public:
        /**
         * @brief Default constructor. Initializes the matrix with zeros.
         */
        matrix3x3<T>();

        /**
         * @brief Copy constructor.
         *
         * @param other Matrix to be copied.
         */
        matrix3x3<T>(const matrix3x3<T>& other);

        /**
         * @brief Constructor that initializes the matrix with the given data.
         *
         * @param data Array of arrays representing the matrix elements.
         */
        matrix3x3<T>(const array<array<T, 3>, 3>& data);

        /**
         * @brief Constructor that initializes the matrix with the given data.
         *
         * @param other Matrix to be copied.
         */
        matrix3x3<T>(const matrix<T, 3, 3>& other);

        /**
         * @brief Calculate the determinant of the matrix.
         *
         * @return Determinant of the matrix.
         */
        T determinant() const override;
    };

    template <class T, size_t M>
    class matrix1D final : public matrix<T, 1, M>
    {
    public:
        /**
         * @brief Constructor that initializes the matrix with the given direction class.
         *
         * @param data Array of directions representing the matrix elements.
         */
        matrix1D(const direction<T, M>& data);

        /**
         * @brief Constructor that initializes the matrix with the given  point class.
         *
         * @param data Array of points representing the matrix elements.
         */
        matrix1D(const point<T, M>& data);

        /**
         * @brief Constructor that initializes the matrix with the given row of data.
         *
         * @param data Array of arrays representing the matrix elements.
         */
        matrix1D(const array<T, M>& data);

        /**
         * @brief Default constructor. Initializes the matrix with an empty array.
         */
        matrix1D();
        /**
         * @brief Copy constructor.
         *
         * @param other Matrix to be copied.
         */
        template <size_t N>
        matrix1D(const matrix<T, N, M>& other);
    };
} // engine_lib

#endif //MATRIX_HPP
#include "matrix.inl"
