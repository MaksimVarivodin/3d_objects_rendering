//
// Created by maksymvarivodin on 7/26/24.
//

#ifndef DIRECTION_HPP
#define DIRECTION_HPP

#include <memory>
#include "../point/point.hpp"

namespace SpaceEngine
{
    using namespace std;

    /**
    * @class direction
    * @brief A class representing a direction in N-dimensional space.
    *
    * @tparam T The type of the coordinates (e.g., float, double).
    * @note It doesn't store elements, but rather references to two points: the beginning and the end of the direction.
    * @throws invalid_argument If the beginning and end points do not have the same number of axes.
    */
    template <class T>
    class direction
    {
        shared_ptr<point<T>> beginning_; /// The beginning point of the direction.
        shared_ptr<point<T>> end_; /// The end point of the direction.

    public:
        /**
         * @brief Default constructor for the direction class.
         */
        direction() = default;

        direction(point<T>& begin, point<T>& end);

        /**
         * @brief Copy constructor for the direction class.
         *
         * @param other The direction to copy from.
         */
        direction(const direction& other) = delete;

        /**
         * @brief Assignment operator for the direction class.
         *
         * This operator is deleted to prevent assignment of direction objects.
         *
         * @param other The direction to assign from.
         * @return A reference to this direction.
         */
        direction& operator=(const direction& other) = delete;

        /**
         * @brief Retrieves the beginning point of the direction.
         *
         * @return An array representing the beginning point coordinates.
         */
        point<T> get_beginning() const;

        /**
         * @brief Retrieves the end point of the direction.
         *
         * @return An array representing the end point coordinates.
         */
        point<T> get_end() const;

        point<T> radius_direction() const;

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
        point<T> cross_product(const direction& other) const;

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
        point<T> ort() const;


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
         * @brief Checks if this direction is collinear with another direction.
         *
         * @param other The other direction.
         * @return True if the directions are collinear, false otherwise.
         */
        bool collinear(const direction& other) const;

        /**
         * @brief Checks if this direction is coplanar with two other directions.
         *
         * @param b The second direction.
         * @param c The third direction.
         * @return True if the directions are coplanar, false otherwise.
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
        tuple<point<T>, point<T>> operator+(const point<T>& other) const;

        /**
         * @brief Subtracts a point from this direction element-wise and returns a new direction.
         *
         * @tparam M The number of dimensions of the other point (M <= N).
         * @param other The point to subtract.
         * @return A new direction containing the element-wise difference.
         */
        tuple<point<T>, point<T>> operator-(const point<T>& other) const;


        /**
         * @brief Adds a direction to this direction element-wise and returns a new direction.
         *
         * @tparam M The number of dimensions of the other direction (M <= N).
         * @param other The direction to add.
         * @return A new direction containing the element-wise sum.
         */
        tuple<point<T>, point<T>> operator+(const direction<T>& other) const;

        /**
         * @brief Subtracts a direction from this direction element-wise and returns a new direction.
         *
         * @tparam M The number of dimensions of the other direction (M <= N).
         * @param other The direction to subtract.
         * @return A new direction containing the element-wise difference.
         */
        tuple<point<T>, point<T>> operator-(const direction<T>& other) const;


        /**
         * @brief Element-wise multiplication with a point of the same dimension.
         * @param other The point to multiply with.
         * @return A new direction containing the element-wise product.
         */
        tuple<point<T>, point<T>> operator*(const point<T>& other) const;

        /**
         * @brief Element-wise division by a point of the same dimension.
         * @param other The point to divide by.
         * @return A new direction containing the element-wise quotient.
         */
        tuple<point<T>, point<T>> operator/(const point<T>& other) const;


        /**
         * @brief Element-wise multiplication with a direction of the same dimension.
         * @param other The direction to multiply with.
         * @return A new direction containing the element-wise product.
         */
        tuple<point<T>, point<T>> operator*(const direction<T>& other) const;

        /**
         * @brief Element-wise division by a direction of the same dimension.
         * @param other The direction to divide by.
         * @return A new direction containing the element-wise quotient.
         */
        tuple<point<T>, point<T>> operator/(const direction<T>& other) const;


        /**
         * @brief Multiplies all coordinates by a scalar and returns a new direction.
         * @param value The scalar value.
         * @return A new scaled direction.
         */
        tuple<point<T>, point<T>> operator*(T value) const;

        /**
         * @brief Divides all coordinates by a scalar and returns a new direction.
         * @param value The scalar divisor.
         * @return A new scaled direction.
         */
        tuple<point<T>, point<T>> operator/(T value) const;

        void check_compatible(const direction& other) const;
    };
}
#endif //DIRECTION_HPP

#include "direction.inl"
