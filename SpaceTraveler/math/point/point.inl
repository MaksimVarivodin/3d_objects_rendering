#ifndef POINT_INL
#define POINT_INL

namespace engine_lib
{
    using namespace std;


    template <class T, size_t N>
    point<T, N>::point() : coordinates_()
    {
    }

    template <class T, size_t N>
    template <typename... Args>
    point<T, N>::point(Args... args)
    {
        // creating vector of N size
        std::vector<T> temp(N, T{});

        // filling accessible elements
        constexpr size_t num_args = sizeof...(args);
        constexpr size_t copy_count = (num_args < N) ? num_args : N;

        // Используем fold expression для заполнения
        if constexpr (num_args > 0)
        {
            auto values = std::array<T, num_args>{static_cast<T>(args)...};
            std::copy_n(values.begin(), copy_count, temp.begin());
        }

        // Копируем из вектора в массив
        std::copy(temp.begin(), temp.end(), coordinates_.begin());
    }

    template <class T, size_t N>
    point<T, N>::point(const array<T, N>& coordinates)
        : coordinates_(coordinates)
    {
    }


    template <class T, size_t N>
    point<T, N>::point(const point<T, N>& other)
        : coordinates_(other.coordinates_)
    {
    }

    template <class T, size_t N>
    array<T, N> point<T, N>::get_coordinates() const
    {
        return coordinates_;
    }


    template <class T, size_t N>
    size_t point<T, N>::axes() const
    {
        return N;
    }


    template <class T, size_t N>
    T& point<T, N>::operator[](size_t index)
    {
        if (index >= N)
            throw invalid_argument("Index out of range");

        return coordinates_[index];
    }


    template <class T, size_t N>
    T point<T, N>::coordinate(size_t index) const
    {
        if (index >= N)
            return T(0);
        return coordinates_[index];
    }


    template <class T, size_t N>
    void point<T, N>::set(size_t index, T value)
    {
        if (index < N)
            coordinates_[index] = value;
    }


    template <class T, size_t N>
    template <size_t M>
    point<T, N> point<T, N>::operator+(const point<T, M>& other) const
    {
        static_assert(N >= M, "Left side size is less than right side size");

        point<T, N> result(coordinates_);
        for (size_t i = 0; i < N; ++i)
            result[i] += other.coordinate(i);
        return result;
    }


    template <class T, size_t N>
    template <size_t M>
    point<T, N> point<T, N>::operator-(const point<T, M>& other) const
    {
        static_assert(N >= M, "Left side size is less than right side size");

        point<T, N> result(coordinates_);
        for (size_t i = 0; i < N; ++i)
            result[i] -= other.coordinate(i);
        return result;
    }


    template <class T, size_t N>
    template <size_t M>
    point<T, N>& point<T, N>::operator+=(const point<T, M>& other)
    {
        static_assert(N >= M, "Left side size is less than right side size");

        for (size_t i = 0; i < N; ++i)
            coordinates_[i] += other.coordinate(i);
        return *this;
    }


    template <class T, size_t N>
    template <size_t M>
    point<T, N>& point<T, N>::operator-=(const point<T, M>& other)
    {
        static_assert(N >= M, "Left side size is less than right side size");
        for (size_t i = 0; i < N; ++i)
            coordinates_[i] -= other.coordinate(i);
        return *this;
    }


    template <class T, size_t N>
    point<T, N> point<T, N>::operator*(const point<T, N>& other) const
    {
        point<T, N> result;
        for (size_t i = 0; i < N; ++i)
            result[i] = coordinates_[i] * other.coordinate(i);
        return result;
    }


    template <class T, size_t N>
    point<T, N> point<T, N>::operator/(const point<T, N>& other) const
    {
        point<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            T divider(other.coordinate(i));
            if (divider == T(0))
                throw std::invalid_argument("Cannot divide by zero");
            result[i] = coordinates_[i] / divider;
        }

        return result;
    }


    template <class T, size_t N>
    point<T, N> point<T, N>::operator*(T value) const
    {
        point<T, N> result;
        for (size_t i = 0; i < N; ++i)
            result[i] = coordinates_[i] * value;
        return result;
    }


    template <class T, size_t N>
    point<T, N> point<T, N>::operator/(T value) const
    {
        if (value == T(0))
            throw std::invalid_argument("Cannot divide by zero");

        point<T, N> result;
        for (size_t i = 0; i < N; ++i)
            result[i] = coordinates_[i] / value;
        return result;
    }


    template <class T, size_t N>
    point<T, N>& point<T, N>::operator*=(const point<T, N>& other)
    {
        for (size_t i = 0; i < N; ++i)
            coordinates_[i] *= other.coordinate(i);
        return *this;
    }


    template <class T, size_t N>
    point<T, N>& point<T, N>::operator/=(const point<T, N>& other)
    {
        for (size_t i = 0; i < N; ++i)
        {
            T divider(other.coordinate(i));
            if (divider == T(0))
                throw std::invalid_argument("Cannot divide by zero");
            coordinates_[i] /= divider;
        }
        return *this;
    }

    template <class T, size_t N>
    point<T, N>& point<T, N>::operator*=(T value)
    {
        for (T& i : coordinates_)
            i *= value;
        return *this;
    }

    template <class T, size_t N>
    point<T, N>& point<T, N>::operator/=(T value)
    {
        if (value == T(0))
            throw std::invalid_argument("Cannot divide by zero");
        for (T& i : coordinates_)
            i /= value;
        return *this;
    }
}
#endif
