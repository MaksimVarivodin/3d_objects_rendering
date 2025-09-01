#ifndef POINT_INL
#define POINT_INL
#include <stdexcept>

namespace SpaceEngine
{
    using namespace std;


    template <class T>
    template <typename... Args>
    point<T>::point(size_t N, Args... args) : coordinates_(N, T{})
    {
        constexpr size_t num_args = sizeof...(args);
        size_t copy_count = std::min(N, num_args);
        size_t i = 0;
        ((i < copy_count ? (void)(coordinates_[i++] = static_cast<T>(args)) : void()), ...);
        if (N > 3 && num_args <= 3)
            coordinates_[3] = static_cast<T>(1);
    }

    template <class T>
    point<T>::point(const vector<T>& coordinates)
        : coordinates_(coordinates)
    {
    }


    template <class T>
    point<T>::point(const point<T>& other)
        : coordinates_(other.coordinates_)
    {
    }

    template <class T>
    vector<T> point<T>::get_coordinates() const
    {
        return coordinates_;
    }


    template <class T>
    size_t point<T>::axes() const
    {
        return coordinates_.size();
    }


    template <class T>
    T& point<T>::operator[](size_t index)
    {
        if (index >= axes())
            throw invalid_argument("Index out of range");

        return coordinates_[index];
    }


    template <class T>
    T point<T>::coordinate(size_t index) const
    {
        if (index >= axes())
            return T(0);
        return coordinates_[index];
    }


    template <class T>
    void point<T>::set(size_t index, T value)
    {
        if (index < axes())
            coordinates_[index] = value;
    }

    template <class T>
    void point<T>::set_axis_count(size_t count)
    {
        coordinates_.resize(count);
    }


    template <class T>
    point<T> point<T>::operator+(const point<T>& other) const
    {
        check_compatible(other);
        point<T> result(coordinates_);
        for (size_t i = 0; i < axes(); ++i)
            result[i] += other.coordinate(i);
        return result;
    }


    template <class T>
    point<T> point<T>::operator-(const point<T>& other) const
    {
        check_compatible(other);

        point<T> result(coordinates_);
        for (size_t i = 0; i < axes(); ++i)
            result[i] -= other.coordinate(i);
        return result;
    }


    template <class T>
    point<T>& point<T>::operator+=(const point<T>& other)
    {
        check_compatible(other);

        for (size_t i = 0; i < axes(); ++i)
            coordinates_[i] += other.coordinate(i);
        return *this;
    }


    template <class T>
    point<T>& point<T>::operator-=(const point<T>& other)
    {
        check_compatible(other);

        for (size_t i = 0; i < axes(); ++i)
            coordinates_[i] -= other.coordinate(i);
        return *this;
    }

    template <class T>
    point<T> point<T>::operator+(T value) const
    {
        point<T> result(*this);
        for (auto& coord : result.coordinates_)
            coord += value;
        return result;
    }

    template <class T>
    point<T>& point<T>::operator+=(T value)
    {
        for (auto& coord : coordinates_)
            coord += value;
        return *this;
    }

    template <class T>
    point<T> point<T>::operator-(T value) const
    {
        point<T> result(*this);
        for (auto& coord : result.coordinates_)
            coord -= value;
        return result;
    }

    template <class T>
    point<T>& point<T>::operator-=(T value)
    {
        for (auto& coord : coordinates_)
            coord -= value;
        return *this;
    }


    template <class T>
    point<T> point<T>::operator*(const point<T>& other) const
    {
        check_compatible(other);

        point<T> result(*this);
        for (size_t i = 0; i < axes(); ++i)
            result[i] *= other.coordinate(i);
        return result;
    }


    template <class T>
    point<T> point<T>::operator/(const point<T>& other) const
    {
        check_compatible(other);

        point<T> result(*this);
        for (size_t i = 0; i < axes(); ++i)
        {
            T divider(other.coordinate(i));
            if (divider == T(0))
                throw std::invalid_argument("Cannot divide by zero");
            result[i] /= divider;
        }

        return result;
    }


    template <class T>
    point<T> point<T>::operator*(T value) const
    {
        point<T> result(*this);
        for (size_t i = 0; i < axes(); ++i)
            result[i] *= value;
        return result;
    }


    template <class T>
    point<T> point<T>::operator/(T value) const
    {
        if (value == T(0))
            throw std::invalid_argument("Cannot divide by zero");

        point<T> result(*this);
        for (size_t i = 0; i < axes(); ++i)
            result[i] /= value;
        return result;
    }


    template <class T>
    point<T>& point<T>::operator*=(const point<T>& other)
    {
        check_compatible(other);

        for (size_t i = 0; i < axes(); ++i)
            coordinates_[i] *= other.coordinate(i);
        return *this;
    }


    template <class T>
    point<T>& point<T>::operator/=(const point<T>& other)
    {
        check_compatible(other);

        for (size_t i = 0; i < axes(); ++i)
        {
            T divider(other.coordinate(i));
            if (divider == T(0))
                throw std::invalid_argument("Cannot divide by zero");
            coordinates_[i] /= divider;
        }
        return *this;
    }

    template <class T>
    point<T>& point<T>::operator*=(T value)
    {
        for (T& i : coordinates_)
            i *= value;
        return *this;
    }

    template <class T>
    point<T>& point<T>::operator/=(T value)
    {
        if (value == T(0))
            throw std::invalid_argument("Cannot divide by zero");
        for (T& i : coordinates_)
            i /= value;
        return *this;
    }

    template <class T>
    bool point<T>::operator!=(const point& other) const
    {
        check_compatible(other);
        size_t it = 0;
        for (const T& el : coordinates_)
        {
            if (el != other.coordinate(it))
                return true;
            ++it;   
        }
        return false;
    }

    template <class T>
    void point<T>::check_compatible(const point& other) const
    {
        if (axes() != other.axes())
            throw std::invalid_argument("Cannot subtract point with fewer dimensions from point with more dimensions");
    }

    template <class T>
    void point_constraints::set_global_zero_axes(size_t axes)
    {
        zero_point.set_axis_count(axes);
    }
}
#endif
