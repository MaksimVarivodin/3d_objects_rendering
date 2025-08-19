#ifndef DIRECTION_INL
#define DIRECTION_INL

namespace engine_lib
{
    using namespace std;

    template <class T, size_t N>
    direction<T, N>::direction()
        : point<T, N>()
    {
    }

    template <class T, size_t N>
    direction<T, N>::direction(initializer_list<T> init)
        : point<T, N>(init),
          beginning_({0}),
          end_(point<T, N>::get_coordinates())
    {
    }

    template <class T, size_t N>
    direction<T, N>::direction(const point<T, N>& direction_point)
        : point<T, N>(direction_point),
          beginning_({0}),
          end_(direction_point.get_coordinates())
    {
    }

    template <class T, size_t N>
    direction<T, N>::direction(const point<T, N>& a, const point<T, N>& b)
        : point<T, N>(b - a),
          beginning_(a.get_coordinates()),
          end_(b.get_coordinates())
    {
    }

    template <class T, size_t N>
    direction<T, N>::direction(const array<T, N>& direction_coordinates)
        : direction(point<T, N>(direction_coordinates))
    {
    }

    template <class T, size_t N>
    direction<T, N>::direction(const array<T, N>& a, const array<T, N>& b)
        : direction(point<T, N>(a), point<T, N>(b))
    {
    }

    template <class T, size_t N>
    direction<T, N>::direction(const direction<T, N>& other)
        : point<T, N>(other.get_coordinates()),
          beginning_(other.beginning_),
          end_(other.end_)
    {
    }

    template <class T, size_t N>
    array<T, N> direction<T, N>::get_beginning() const
    {
        return beginning_;
    }

    template <class T, size_t N>
    array<T, N> direction<T, N>::get_end() const
    {
        return end_;
    }


    template <class T, size_t N>
    T direction<T, N>::length() const
    {
        T sum(0);
        for (T i : this->get_coordinates())
            sum += i * i;
        return T(sqrt(sum));
    }

    template <class T, size_t N>
    T direction<T, N>::cos_axis_angle(size_t axis) const
    {
        return this->coordinate(axis) / length();
    }

    template <class T, size_t N>
    T direction<T, N>::cos_vector_angle(const direction<T, N>& other) const
    {
        T sum(0);
        for (size_t i = 0; i < N; ++i)
            sum += this->coordinate(i) * other.coordinate(i);
        return sum / (this->length() * other.length());
    }

    template <class T, size_t N>
    T direction<T, N>::projection(const direction<T, N>& other) const
    {
        if (other.zero_direction())
            throw std::invalid_argument("Cannot project on zero-direction");
        return dot_product(other) / other.length();
    }

    template <class T, size_t N>
    direction<T, N> direction<T, N>::cross_product(const direction<T, N>& other) const
    {
        static_assert(N >= 3, "Cross product only defined for 3D vectors");
        direction<T, N> result;
        result[x] = this->coordinate(y) * other.coordinate(z) - this->coordinate(z) * other.coordinate(y);
        result[y] = this->coordinate(z) * other.coordinate(x) - this->coordinate(x) * other.coordinate(z);
        result[z] = this->coordinate(x) * other.coordinate(y) - this->coordinate(y) * other.coordinate(x);
        result.beginning_ = {0};
        result.end_ = result.get_coordinates();
        return result;
    }


    template <class T, size_t N>
    direction<T, N> direction<T, N>::ort() const
    {
        array<T, N> ort_coordinates;
        T l(length());
        for (size_t i = 0; i < N; ++i)
            ort_coordinates[i] = this->coordinates_[i] / l;
        return direction<T, N>(ort_coordinates);
    }

    template <class T, size_t N>
    direction<T, N>& direction<T, N>::ort()
    {
        T l(length());
        for (T& i : this->get_coordinates())
            i /= l;
        beginning_ = array<T, N>({0});
        end_ = this->get_coordinates();
        return *this;
    }

    template <class T, size_t N>
    bool direction<T, N>::equal(const direction<T, N>& other) const
    {
        for (int i = 0; i < N; ++i)
            if (this->coordinate[i] != other.coordinate(i))
                return false;
        return true;
    }


    template <class T, size_t N>
    bool direction<T, N>::orthogonal(const direction<T, N>& other) const
    {
        return dot_product(other) == 0;
    }

    template <class T, size_t N>
    bool direction<T, N>::collinear(const direction<T, N>& other) const
    {
        if (zero_direction() || other.zero_direction())
            throw std::invalid_argument("Cannot calculate colinearity with zero-direction");
        T division(this->coordinate(0) / other.coordinate(0));
        for (int i = 1; i < N; ++i)
        {
            T division2 = this->coordinate(i) / other.coordinate(i);
            if (division != division2)
                return false;
        }
        return true;
    }


    template <class T, size_t N>
    T direction<T, N>::dot_product(const direction<T, N>& other) const
    {
        T sum(0);
        for (size_t i = 0; i < N; ++i)
            sum += this->coordinate(i) * other.coordinate(i);
        return sum;
    }


    template <class T, size_t N>
    bool direction<T, N>::zero_direction() const
    {
        for (T i : this->coordinates_)
            if (i != 0)
                return false;
        return true;
    }

    // ========================= Operator implementations =========================

    // Point<T, M> arguments
    template <class T, size_t N>
    template <size_t M>
    direction<T, N> direction<T, N>::operator+(const point<T, M>& other) const
    {
        point<T, N> p = point<T, N>::template operator+<M>(other);
        direction<T, N> res(p);
        res.beginning_ = beginning_;
        for (size_t i = 0; i < N; ++i)
            res.end_[i] = res.beginning_[i] + res.coordinate(i);
        return res;
    }

    template <class T, size_t N>
    template <size_t M>
    direction<T, N> direction<T, N>::operator-(const point<T, M>& other) const
    {
        point<T, N> p = point<T, N>::template operator-<M>(other);
        direction<T, N> res(p);
        res.beginning_ = beginning_;
        for (size_t i = 0; i < N; ++i)
            res.end_[i] = res.beginning_[i] + res.coordinate(i);
        return res;
    }

    template <class T, size_t N>
    template <size_t M>
    direction<T, N>& direction<T, N>::operator+=(const point<T, M>& other)
    {
        point<T, N>::template operator+=<M>(other);
        for (size_t i = 0; i < N; ++i)
            end_[i] = beginning_[i] + this->coordinate(i);
        return *this;
    }

    template <class T, size_t N>
    template <size_t M>
    direction<T, N>& direction<T, N>::operator-=(const point<T, M>& other)
    {
        point<T, N>::template operator-=<M>(other);
        for (size_t i = 0; i < N; ++i)
            end_[i] = beginning_[i] + this->coordinate(i);
        return *this;
    }

    // direction<T, M> arguments (forward to point versions)
    template <class T, size_t N>
    template <size_t M>
    direction<T, N> direction<T, N>::operator+(const direction<T, M>& other) const
    {
        const point<T, M>& as_point = static_cast<const point<T, M>&>(other);
        return this->template operator+<M>(as_point);
    }

    template <class T, size_t N>
    template <size_t M>
    direction<T, N> direction<T, N>::operator-(const direction<T, M>& other) const
    {
        const point<T, M>& as_point = static_cast<const point<T, M>&>(other);
        return this->template operator-<M>(as_point);
    }

    template <class T, size_t N>
    template <size_t M>
    direction<T, N>& direction<T, N>::operator+=(const direction<T, M>& other)
    {
        const point<T, M>& as_point = static_cast<const point<T, M>&>(other);
        this->template operator+=<M>(as_point);
        return *this;
    }

    template <class T, size_t N>
    template <size_t M>
    direction<T, N>& direction<T, N>::operator-=(const direction<T, M>& other)
    {
        const point<T, M>& as_point = static_cast<const point<T, M>&>(other);
        this->template operator-=<M>(as_point);
        return *this;
    }

    // Same-N point element-wise ops
    template <class T, size_t N>
    direction<T, N> direction<T, N>::operator*(const point<T, N>& other) const
    {
        point<T, N> p = point<T, N>::operator*(other);
        direction<T, N> res(p);
        // Умножаем обе точки вектора
        for (size_t i = 0; i < N; ++i)
        {
            res.beginning_[i] = beginning_[i] * other.coordinate(i);
            res.end_[i] = end_[i] * other.coordinate(i);
        }
        return res;
    }

    template <class T, size_t N>
    direction<T, N> direction<T, N>::operator/(const point<T, N>& other) const
    {
        // Проверяем деление на ноль
        for (size_t i = 0; i < N; ++i)
        {
            if (other.coordinate(i) == T(0))
            {
                throw std::invalid_argument("Cannot divide by zero");
            }
        }

        point<T, N> p = point<T, N>::operator/(other);
        direction<T, N> res(p);
        // Делим обе точки вектора
        for (size_t i = 0; i < N; ++i)
        {
            res.beginning_[i] = beginning_[i] / other.coordinate(i);
            res.end_[i] = end_[i] / other.coordinate(i);
        }
        return res;
    }

    template <class T, size_t N>
    direction<T, N>& direction<T, N>::operator*=(const point<T, N>& other)
    {
        point<T, N>::operator*=(other);
        // Умножаем обе точки вектора
        for (size_t i = 0; i < N; ++i)
        {
            beginning_[i] *= other.coordinate(i);
            end_[i] *= other.coordinate(i);
        }
        return *this;
    }

    template <class T, size_t N>
    direction<T, N>& direction<T, N>::operator/=(const point<T, N>& other)
    {
        // Проверяем деление на ноль
        for (size_t i = 0; i < N; ++i)
        {
            if (other.coordinate(i) == T(0))
            {
                throw std::invalid_argument("Cannot divide by zero");
            }
        }

        point<T, N>::operator/=(other);
        // Делим обе точки вектора
        for (size_t i = 0; i < N; ++i)
        {
            beginning_[i] /= other.coordinate(i);
            end_[i] /= other.coordinate(i);
        }
        return *this;
    }

    // Same-N direction element-wise ops (forward to point ones)
    template <class T, size_t N>
    direction<T, N> direction<T, N>::operator*(const direction<T, N>& other) const
    {
        point<T, N> p = point<T, N>::operator*(other);
        direction<T, N> res(p);
        // Умножаем обе точки вектора
        for (size_t i = 0; i < N; ++i)
        {
            res.beginning_[i] = beginning_[i] * other.coordinate(i);
            res.end_[i] = end_[i] * other.coordinate(i);
        }
        return res;
    }

    template <class T, size_t N>
    direction<T, N> direction<T, N>::operator/(const direction<T, N>& other) const
    {
        // Проверяем деление на ноль
        for (size_t i = 0; i < N; ++i)
        {
            if (other.coordinate(i) == T(0))
            {
                throw std::invalid_argument("Cannot divide by zero");
            }
        }

        point<T, N> p = point<T, N>::operator/(other);
        direction<T, N> res(p);
        // Делим обе точки вектора
        for (size_t i = 0; i < N; ++i)
        {
            res.beginning_[i] = beginning_[i] / other.coordinate(i);
            res.end_[i] = end_[i] / other.coordinate(i);
        }
        return res;
    }

    template <class T, size_t N>
    direction<T, N>& direction<T, N>::operator*=(const direction<T, N>& other)
    {
        point<T, N>::operator*=(other);
        // Умножаем обе точки вектора
        for (size_t i = 0; i < N; ++i)
        {
            beginning_[i] *= other.coordinate(i);
            end_[i] *= other.coordinate(i);
        }
        return *this;
    }

    template <class T, size_t N>
    direction<T, N>& direction<T, N>::operator/=(const direction<T, N>& other)
    {
        // Проверяем деление на ноль
        for (size_t i = 0; i < N; ++i)
        {
            if (other.coordinate(i) == T(0))
            {
                throw std::invalid_argument("Cannot divide by zero");
            }
        }

        point<T, N>::operator/=(other);
        // Делим обе точки вектора
        for (size_t i = 0; i < N; ++i)
        {
            beginning_[i] /= other.coordinate(i);
            end_[i] /= other.coordinate(i);
        }
        return *this;
    }

    // Scalar ops
    template <class T, size_t N>
    direction<T, N> direction<T, N>::operator*(T value) const
    {
        point<T, N> p = point<T, N>::operator*(value);
        direction<T, N> res(p);
        // Умножаем обе точки вектора на скаляр
        for (size_t i = 0; i < N; ++i)
        {
            res.beginning_[i] = beginning_[i] * value;
            res.end_[i] = end_[i] * value;
        }
        return res;
    }

    template <class T, size_t N>
    direction<T, N> direction<T, N>::operator/(T value) const
    {
        if (value == T(0))
        {
            throw std::invalid_argument("Cannot divide by zero");
        }

        point<T, N> p = point<T, N>::operator/(value);
        direction<T, N> res(p);
        // Делим обе точки вектора на скаляр
        for (size_t i = 0; i < N; ++i)
        {
            res.beginning_[i] = beginning_[i] / value;
            res.end_[i] = end_[i] / value;
        }
        return res;
    }

    template <class T, size_t N>
    direction<T, N>& direction<T, N>::operator*=(T value)
    {
        point<T, N>::operator*=(value);
        // Умножаем обе точки вектора на скаляр
        for (size_t i = 0; i < N; ++i)
        {
            beginning_[i] *= value;
            end_[i] *= value;
        }
        return *this;
    }

    template <class T, size_t N>
    direction<T, N>& direction<T, N>::operator/=(T value)
    {
        if (value == T(0))
        {
            throw std::invalid_argument("Cannot divide by zero");
        }

        point<T, N>::operator/=(value);
        // Делим обе точки вектора на скаляр
        for (size_t i = 0; i < N; ++i)
        {
            beginning_[i] /= value;
            end_[i] /= value;
        }
        return *this;
    }
}
#endif
