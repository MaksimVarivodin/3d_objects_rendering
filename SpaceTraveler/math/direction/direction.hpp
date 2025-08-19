//
// Created by maksymvarivodin on 7/26/24.
//

#ifndef DIRECTION_HPP
#define DIRECTION_HPP

#include <array>
#include "../point/point.hpp"

namespace engine_lib
{
    using namespace std;

    /**
    * @class direction
    * @brief A class representing a direction in N-dimensional space, inheriting from the point class.
    *
    * @tparam T The type of the coordinates (e.g., float, double).
    * @tparam N The number of dimensions.
    */
    template <class T, size_t N>
    class direction : public point<T, N>
    {
        array<T, N> beginning_; /// The beginning point of the direction.
        array<T, N> end_; /// The end point of the direction.

    public:
        /**
         * @brief Default constructor for the direction class.
         */
        direction();
        /**
         * @brief Initializer list constructor for the direction class.
         *
         * This constructor initializes a direction from initializer list.
         */
        direction(initializer_list<T> init);
        /**
         * @brief Constructs a direction from a single point.
         *
         * @param direction_point The point representing the direction.
         */
        direction(const point<T, N>& direction_point);

        /**
         * @brief Constructs a direction from two points.
         *
         * @param a The starting point.
         * @param b The ending point.
         */
        direction(const point<T, N>& a, const point<T, N>& b);

        /**
         * @brief Constructs a direction from an array of direction coordinates.
         *
         * @param direction_coordinates The array representing the direction coordinates.
         */
        direction(const array<T, N>& direction_coordinates);

        /**
         * @brief Constructs a direction from two arrays of coordinates.
         *
         * @param a The array representing the starting point coordinates.
         * @param b The array representing the ending point coordinates.
         */
        direction(const array<T, N>& a, const array<T, N>& b);

        /**
         * @brief Copy constructor for the direction class.
         *
         * @param other The direction to copy from.
         */
        direction(const direction& other);
        /**
         * @brief Retrieves the beginning point of the direction.
         *
         * @return An array representing the beginning point coordinates.
         */
        array<T, N> get_beginning() const;

        /**
         * @brief Retrieves the end point of the direction.
         *
         * @return An array representing the end point coordinates.
         */
        array<T, N> get_end() const;

        /**
         * @brief Calculates the length of the direction.
         *
         * @return The length of the direction.
         */
        T length() const;

        /**
         * @brief Calculates the cosine of the angle between the direction and a specified axis.
         *
         * @param axis The axis to calculate the angle with.
         * @return The cosine of the angle.
         */
        T cos_axis_angle(size_t axis) const;

        /**
         * @brief Calculates the cosine of the angle between this direction and another direction.
         *
         * @param other The other direction.
         * @return The cosine of the angle.
         */
        T cos_vector_angle(const direction& other) const;

        /**
         * @brief Projects this direction onto another direction.
         *
         * @param other The other direction.
         * @return The projection of this direction onto the other direction.
         */
        T projection(const direction& other) const;

        /**
         * @brief Calculates the dot product of this direction and another direction.
         *
         * @param other The other direction.
         * @return The dot product.
         */
        T dot_product(const direction& other) const;

        /**
         * @brief Calculates the cross product of this direction and another direction.
         *
         * @param other The other direction.
         * @return The cross product.
         */
        direction cross_product(const direction& other) const;

        /**
         * @brief Calculates the mixed product of this direction and two other directions.
         *
         * @param b The second direction.
         * @param c The third direction.
         * @return The mixed product.
         */
        T mixed_product(const direction& b, const direction& c) const;

        /**
         * @brief Returns the orthogonal direction of this direction.
         *
         * @return The orthogonal direction.
         */
        direction ort() const;

        /**
         * @brief Returns a reference to the orthogonal direction of this direction.
         *
         * @return A reference to the orthogonal direction.
         */
        direction& ort();

        /**
         * @brief Checks if this direction is a zero direction.
         *
         * @return True if this is a zero direction, false otherwise.
         */
        [[nodiscard]] bool zero_direction() const;

        /**
         * @brief Checks if this direction is equal to another direction.
         *
         * @param other The other direction.
         * @return True if the directions are equal, false otherwise.
         */
        bool equal(const direction& other) const;

        /**
         * @brief Checks if this direction is orthogonal to another direction.
         *
         * @param other The other direction.
         * @return True if the directions are orthogonal, false otherwise.
         */
        bool orthogonal(const direction& other) const;

        /**
         * @brief Checks if this direction is colinear with another direction.
         *
         * @param other The other direction.
         * @return True if the directions are colinear, false otherwise.
         */
        bool collinear(const direction& other) const;

        /**
         * @brief Checks if this direction is complanar with two other directions.
         *
         * @param b The second direction.
         * @param c The third direction.
         * @return True if the directions are complanar, false otherwise.
         */
        bool coplanar(const direction& b, const direction& c) const;

        // ========================= Operator overloads mirroring point =========================
        /**
         * @brief Adds a point to this direction element-wise and returns a new direction.
         *
         * @tparam M The number of dimensions of the other point (M <= N).
         * @param other The point to add.
         * @return A new direction containing the element-wise sum.
         */
        template <size_t M>
        direction operator+(const point<T, M>& other) const;

        /**
         * @brief Subtracts a point from this direction element-wise and returns a new direction.
         *
         * @tparam M The number of dimensions of the other point (M <= N).
         * @param other The point to subtract.
         * @return A new direction containing the element-wise difference.
         */
        template <size_t M>
        direction operator-(const point<T, M>& other) const;

        /**
         * @brief Adds a point to this direction in-place (element-wise).
         *
         * Executes the parent method and then updates the beginning and end fields.
         *
         * @tparam M The number of dimensions of the other point (M <= N).
         * @param other The point to add.
         * @return A reference to this direction.
         */
        template <size_t M>
        direction& operator+=(const point<T, M>& other);

        /**
         * @brief Subtracts a point from this direction in-place (element-wise).
         *
         * Executes the parent method and then updates the beginning and end fields.
         *
         * @tparam M The number of dimensions of the other point (M <= N).
         * @param other The point to subtract.
         * @return A reference to this direction.
         */
        template <size_t M>
        direction& operator-=(const point<T, M>& other);

        /**
         * @brief Adds a direction to this direction element-wise and returns a new direction.
         *
         * @tparam M The number of dimensions of the other direction (M <= N).
         * @param other The direction to add.
         * @return A new direction containing the element-wise sum.
         */
        template <size_t M>
        direction operator+(const direction<T, M>& other) const;

        /**
         * @brief Subtracts a direction from this direction element-wise and returns a new direction.
         *
         * @tparam M The number of dimensions of the other direction (M <= N).
         * @param other The direction to subtract.
         * @return A new direction containing the element-wise difference.
         */
        template <size_t M>
        direction operator-(const direction<T, M>& other) const;

        /**
         * @brief Adds a direction to this direction in-place (element-wise).
         *
         * Executes the parent method and then updates the beginning and end fields.
         *
         * @tparam M The number of dimensions of the other direction (M <= N).
         * @param other The direction to add.
         * @return A reference to this direction.
         */
        template <size_t M>
        direction& operator+=(const direction<T, M>& other);

        /**
         * @brief Subtracts a direction from this direction in-place (element-wise).
         *
         * Executes the parent method and then updates the beginning and end fields.
         *
         * @tparam M The number of dimensions of the other direction (M <= N).
         * @param other The direction to subtract.
         * @return A reference to this direction.
         */
        template <size_t M>
        direction& operator-=(const direction<T, M>& other);

        /**
         * @brief Element-wise multiplication with a point of the same dimension.
         * @param other The point to multiply with.
         * @return A new direction containing the element-wise product.
         */
        direction operator*(const point<T, N>& other) const;

        /**
         * @brief Element-wise division by a point of the same dimension.
         * @param other The point to divide by.
         * @return A new direction containing the element-wise quotient.
         */
        direction operator/(const point<T, N>& other) const;

        /**
         * @brief In-place element-wise multiplication with a point of the same dimension.
         *
         * Executes the parent method and then updates the beginning and end fields.
         *
         * @param other The point to multiply with.
         * @return A reference to this direction.
         */
        direction& operator*=(const point<T, N>& other);

        /**
         * @brief In-place element-wise division by a point of the same dimension.
         *
         * Executes the parent method and then updates the beginning and end fields.
         *
         * @param other The point to divide by.
         * @return A reference to this direction.
         */
        direction& operator/=(const point<T, N>& other);

        /**
         * @brief Element-wise multiplication with a direction of the same dimension.
         * @param other The direction to multiply with.
         * @return A new direction containing the element-wise product.
         */
        direction operator*(const direction<T, N>& other) const;

        /**
         * @brief Element-wise division by a direction of the same dimension.
         * @param other The direction to divide by.
         * @return A new direction containing the element-wise quotient.
         */
        direction operator/(const direction<T, N>& other) const;

        /**
         * @brief In-place element-wise multiplication with a direction of the same dimension.
         *
         * Executes the parent method and then updates the beginning and end fields.
         *
         * @param other The direction to multiply with.
         * @return A reference to this direction.
         */
        direction& operator*=(const direction<T, N>& other);

        /**
         * @brief In-place element-wise division by a direction of the same dimension.
         *
         * Executes the parent method and then updates the beginning and end fields.
         *
         * @param other The direction to divide by.
         * @return A reference to this direction.
         */
        direction& operator/=(const direction<T, N>& other);

        /**
         * @brief Multiplies all coordinates by a scalar and returns a new direction.
         * @param value The scalar value.
         * @return A new scaled direction.
         */
        direction operator*(T value) const;

        /**
         * @brief Divides all coordinates by a scalar and returns a new direction.
         * @param value The scalar divisor.
         * @return A new scaled direction.
         */
        direction operator/(T value) const;

        /**
         * @brief Scales this direction by a scalar in-place.
         *
         * Executes the parent method and then updates the beginning and end fields.
         *
         * @param value The scalar value.
         * @return A reference to this direction.
         */
        direction& operator*=(T value);

        /**
         * @brief Divides this direction by a scalar in-place.
         *
         * Executes the parent method and then updates the beginning and end fields.
         *
         * @param value The scalar divisor.
         * @return A reference to this direction.
         */
        direction& operator/=(T value);
    };
}
#endif //DIRECTION_HPP

#include "direction.inl"
