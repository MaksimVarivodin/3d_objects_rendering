//
// Created by maksymvarivodin on 7/26/24.
//

#ifndef POINT_HPP
#define POINT_HPP

#include <vector>

namespace SpaceEngine
{
    using namespace std;

    template <class T>
    class matrix;
    /**
     * @enum axis
     * @brief Represents the axes in a 2D, 3D, or 4D space.
     *
     * This enum is used to specify the axis for various operations in the SpaceEngine::point class.
     */
    enum axis: unsigned char
    {
        x, //!< Represents the x-axis.
        y, //!< Represents the y-axis.
        z, //!< Represents the z-axis.
        w //!< Represents the w-axis
    };

    /**
     * @class point
     * @brief A template class for a point with N dimensions.
     *
     * This class provides a basic implementation of a point with N dimensions.
     * It supports basic arithmetic operations such as addition, subtraction,
     * multiplication, and division. The class also provides access to individual
     * coordinates and the ability to set coordinates.
     *
     * @param T The type of the coordinates.
     *
     * @throws invalid_argument If an index is out of range or if division by zero is attempted.
     */
    template <class T>
    class point
    {
        /**
         * @param coordinates_ array of coordinates for the point.
         */
        vector<T> coordinates_;

    public:
        /**
         * @brief Default constructor for the point class.
         *
         * This constructor initializes a point with an empty array of coordinates.
         */

        point() = default;

        /**
         * @brief Initializer list constructor for the point class.
         *
         * This constructor initializes a point from initializer list.
         */
        template <typename... Args>
        point(size_t N, Args... args);

        /**
         * @brief Constructor for the point class that takes an array of coordinates.
         *
         * This constructor initializes a point with the given array of coordinates.
         *
         * @param coordinates The array of coordinates to initialize the point with.
         */

        point(const vector<T>& coordinates);


        /**
         * @brief Copy constructor for the point class.
         *
         * This constructor initializes a point with a copy of the coordinates of another point.
         *
         * @param other The point whose coordinates will be copied.
         */
        point(const point& other);


        /**
         *  @brief Gets the coordinates of the point.
         *
         * @tparam T The type of the coordinates (e.g., float, double).
         * @tparam N The number of dimensions.
         * @return An array containing the coordinates of the point.
         */
        vector<T> get_coordinates() const;

        /**
         * @brief Returns the number of dimensions of the point.
         *
         * This function returns the number of dimensions of the point.
         *
         * @return The number of dimensions of the point.
         */
        [[nodiscard]] size_t axes() const;


        /**
         * @brief Accesses an individual coordinate of the point.
         *
         * This function allows access to individual coordinates of the point.
         * If the index is out of range, an exception of type invalid_argument is thrown.
         *
         * @param index The index of the coordinate to access.
         * @return The value of the coordinate at the given index.
         */
        T& operator[](size_t index);


        /**
         * @brief Accesses an individual coordinate of the point.
         *
         * This function allows access to individual coordinates of the point.
         * If the index is out of range, the function returns a default-constructed value of type T.
         *
         * @param index The index of the coordinate to access.
         * @return The value of the coordinate at the given index, or a default-constructed value of type T if the index is out of range.
         */
        T coordinate(size_t index) const;

        /**
         * @brief Sets the value of an individual coordinate of the point.
         *
         * This function allows setting the value of individual coordinates of the point.
         * If the index is out of range, nothing happens.
         *
         * @param index The index of the coordinate to set.
         * @param value The value to set for the coordinate.
         */
        void set(size_t index, T value);


        /**
         * @brief Adds another point to this point.
         *
         * This function adds another point to this point, element-wise.
         * If the number of dimensions of the other point is less than the number of dimensions of this point,
         * an exception of type invalid_argument is thrown.
         *
         * @param other The point to add to this point.
         * @return A new point that is the result of adding this point and the other point.
         */
        point operator+(const point& other) const;


        /**
         * @brief Subtracts another point from this point.
         *
         * This function subtracts another point from this point, element-wise.
         * If the number of dimensions of the other point is less than the number of dimensions of this point,
         * an exception of type invalid_argument is thrown.
         *
         * @param other The point to subtract from this point.
         * @return A new point that is the result of subtracting this point and the other point.
         */
        point operator-(const point& other) const;


        /**
         * @brief Adds another point to this point in-place.
         *
         * This function adds another point to this point, element-wise, and modifies this point in-place.
         * If the number of dimensions of the other point is less than the number of dimensions of this point,
         * an exception of type invalid_argument is thrown.
         *
         * @param other The point to add to this point.
         * @return A reference to this point, which has been modified in-place.
         */

        point& operator+=(const point& other);


        /**
         * @brief Subtracts another point from this point in-place.
         *
         * This function subtracts another point from this point, element-wise, and modifies this point in-place.
         * If the number of dimensions of the other point is less than the number of dimensions of this point,
         * an exception of type invalid_argument is thrown.
         *
         * @param other The point to subtract from this point.
         * @return A reference to this point, which has been modified in-place.
         */
        point& operator-=(const point& other);


        /**
         * @brief Adds a scalar value to each coordinate of the point.
         * @param value The value to add to each coordinate.
         * @return A new point with the added value.
         */
        point operator+(T value) const;

        /**
         * @brief Adds a scalar value to each coordinate of the point in-place.
         * @param value The value to add to each coordinate.
         * @return A reference to the modified point.
         */
        point& operator+=(T value);

        /**
         * @brief Subtracts a scalar value from each coordinate of the point.
         * @param value The value to subtract from each coordinate.
         * @return A new point with the subtracted value.
         */
        point operator-(T value) const;

        /**
         * @brief Subtracts a scalar value from each coordinate of the point in-place.
         * @param value The value to subtract from each coordinate.
         * @return A reference to the modified point.
         */
        point& operator-=(T value);

        /**
         * @brief Multiplies this point by another point.
         *
         * This function multiplies this point by another point, element-wise.
         * The result is a new point with coordinates that are the products of the corresponding coordinates of this point and the other point.
         *
         * @param other The point to multiply this point by.
         * @return A new point that is the result of multiplying this point and the other point.
         */
        point operator*(const point& other) const;

        /**
         * @brief Multiplies this point by a matrix.
         *
         * This function multiplies this point by a matrix.
         * The result is a new point with coordinates that are the products of the corresponding coordinates of this point and the matrix.
         *
         * @param m The matrix to multiply this point by.
         * @return A new point that is the result of multiplying this point and the matrix.
         */
        point operator*(const matrix<T>& m) const;


        /**
         * @brief Divides this point by another point.
         *
         * This function divides this point by another point, element-wise.
         * The result is a new point with coordinates that are the quotients of the corresponding coordinates of this point and the other point.
         * If the denominator is zero for any coordinate, an exception of type invalid_argument is thrown.
         *
         * @param other The point to divide this point by.
         * @return A new point that is the result of dividing this point and the other point.
         */
        point operator/(const point& other) const;


        /**
         * @brief Multiplies this point by a scalar.
         *
         * This function multiplies this point by a scalar, element-wise.
         * The result is a new point with coordinates that are the products of the corresponding coordinates of this point and the scalar.
         *
         * @param value The scalar to multiply this point by.
         * @return A new point that is the result of multiplying this point and the scalar.
         */
        point operator*(T value) const;


        /**
         * @brief Divides this point by a scalar.
         *
         * This function divides this point by a scalar, element-wise.
         * The result is a new point with coordinates that are the quotients of the corresponding coordinates of this point and the scalar.
         * If the denominator is zero, an exception of type invalid_argument is thrown.
         *
         * @param value The scalar to divide this point by.
         * @return A new point that is the result of dividing this point and the scalar.
         */
        point operator/(T value) const;


        /**
         * @brief Multiplies this point by another point in-place.
         *
         * This function multiplies this point by another point, element-wise, and modifies this point in-place.
         * The result is a new point with coordinates that are the products of the corresponding coordinates of this point and the other point.
         *
         * @param other The point to multiply this point by.
         * @return A reference to this point, which has been modified in-place.
         */
        point& operator*=(const point& other);

        /** 
         * @brief Multiplies this point by a matrix in-place.
         *
         * This function multiplies this point by a matrix and modifies this point in-place.
         * The result is a new point with coordinates that are the products of the corresponding coordinates of this point and the matrix.
         *
         * @param m The matrix to multiply this point by.
         * @return A reference to this point, which has been modified in-place.
         */
        point& operator*=(const matrix<T>& m);
        /**
         * @brief Divides this point by another point in-place.
         *
         * This function divides this point by another point, element-wise, and modifies this point in-place.
         * The result is a new point with coordinates that are the quotients of the corresponding coordinates of this point and the other point.
         * If the denominator is zero for any coordinate, an exception of type invalid_argument is thrown.
         *
         * @param other The point to divide this point by.
         * @return A reference to this point, which has been modified in-place.
         */
        point& operator/=(const point& other);


        /**
         * @brief Multiplies each coordinate of the point by the given value.
         * @param value The value to multiply each coordinate by.
         * @return A reference to the modified point.
         */
        point& operator*=(T value);


        /**
         * @brief Divides each coordinate of the point by the given value.
         * @param value The value to divide each coordinate by.
         * @return A reference to the modified point.
         * @throws std::invalid_argument if the given value is zero.
         */
        point& operator/=(T value);


        void check_compatible(const point& other) const;
    };
} // SpaceEngine


#endif //POINT_HPP
#include "point.inl"
