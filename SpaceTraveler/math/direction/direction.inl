#ifndef DIRECTION_INL
#define DIRECTION_INL

namespace SpaceEngine
{
    using namespace std;

    template <class T>
    bool almost_equal(T a, T b,
                      T rel_eps = T(1e-6),
                      T abs_eps = T(1e-12))
    {
        static_assert(std::is_floating_point_v<T>, "floating only");
        if (std::isnan(a) || std::isnan(b)) return false;
        if (std::isinf(a) || std::isinf(b)) return a == b;
        T diff = std::fabs(a - b);
        if (diff <= abs_eps) return true;
        return diff <= rel_eps * std::max(std::fabs(a), std::fabs(b));
    }

    template <class T>
    direction<T>::direction(point<T>& begin, point<T>& end)
        : beginning_(shared_ptr<point<T>>(&begin, [](point<T>*)
          {
          })),
          end_(shared_ptr<point<T>>(&end, [](point<T>*)
          {
          }))
    {
        if (beginning_->axes() != end_->axes())
            throw std::invalid_argument("Beginning and end points must have the same number of axes");
    }

    template <class T>
    point<T> direction<T>::get_beginning() const
    {
        return *beginning_;
    }

    template <class T>
    point<T> direction<T>::get_end() const
    {
        return *end_;
    }

    template <class T>
    point<T> direction<T>::radius_direction() const
    {
        auto begin = get_beginning();

        point<T> radius(get_end());
        for (size_t i = 0; i < begin.axes(); ++i)
            radius[i] -= begin[i];
        return radius;
    }


    template <class T>
    T direction<T>::length() const
    {
        T sum(0);
        for (T i : this->radius_direction().get_coordinates())
            sum += i * i;
        return T(sqrt(sum));
    }

    template <class T>
    T direction<T>::cos_axis_angle(size_t axis) const
    {
        return this->radius_direction().coordinate(axis) / length();
    }

    template <class T>
    T direction<T>::cos_vector_angle(const direction<T>& other) const
    {
        check_compatible(other);
        T sum(0);
        auto a = this->radius_direction();
        auto b = other.radius_direction();
        if (a->axes() != b->axes())
            throw std::invalid_argument("Cosine angle requires directions with the same number of axes");
        for (size_t i = 0; i < a.axes(); ++i)
            sum += a.coordinate(i) * b.coordinate(i);
        return sum / (this->length() * other.length());
    }

    template <class T>
    T direction<T>::projection(const direction<T>& other) const
    {
        check_compatible(other);
        if (other.zero_direction())
            throw std::invalid_argument("Cannot project on zero-direction");
        return dot_product(other) / other.length();
    }

    template <class T>
    T direction<T>::dot_product(const direction<T>& other) const
    {
        check_compatible(other);

        T sum(0);
        auto a = this->radius_direction();
        auto b = other.radius_direction();

        for (size_t i = 0; i < a.axes(); ++i)
            sum += a.coordinate(i) * b.coordinate(i);
        return sum;
    }

    template <class T>
    point<T> direction<T>::cross_product(const direction<T>& other) const
    {
        check_compatible(other);
        auto a = this->radius_direction();
        auto b = other.radius_direction();

        if (a.axes() < 3 || b.axes() < 3)
            throw std::invalid_argument("Cross product is only defined for 3D directions");

        point<T> result(a.axes());
        result[x] = a.coordinate(y) * b.coordinate(z) - a.coordinate(z) * b.coordinate(y);
        result[y] = a.coordinate(z) * b.coordinate(x) - a.coordinate(x) * b.coordinate(z);
        result[z] = a.coordinate(x) * b.coordinate(y) - a.coordinate(y) * b.coordinate(x);
        if (a.axes() > 3)
            result[w] = T(1);
        return result;
    }


    template <class T>
    point<T> direction<T>::ort() const
    {
        auto o = this->radius_direction();
        T l(length());
        if (almost_equal(l, T(0.0)))
            throw std::invalid_argument("Cannot divide by zero");
        return o / l;
    }

    template <class T>
    bool direction<T>::equal(const direction<T>& other) const
    {
        check_compatible(other);
        auto a = this->radius_direction();
        auto b = other.radius_direction();

        for (int i = 0; i < a.axes(); ++i)
            if (a[i] != b[i])
                return false;

        return true;
    }


    template <class T>
    bool direction<T>::orthogonal(const direction<T>& other) const
    {
        return dot_product(other) == 0;
    }

    template <class T>
    bool direction<T>::collinear(const direction<T>& other) const
    {
        check_compatible(other);
        if (zero_direction() || other.zero_direction())
            throw std::invalid_argument("Cannot calculate collinearity with zero-direction");
        auto a = this->radius_direction();
        auto b = other.radius_direction();

        // Найдем первую ненулевую координату в векторе b
        size_t non_zero_index = a.axes();
        for (size_t i = 0; i < a.axes(); ++i)
        {
            if (!almost_equal(b.coordinate(i), T(0.0)))
            {
                non_zero_index = i;
                break;
            }
        }
        
        if (non_zero_index == a.axes())
            return false; // b - нулевой вектор
        
        T division = a.coordinate(non_zero_index) / b.coordinate(non_zero_index);

        for (size_t i = 0; i < a.axes(); ++i)
        {
            T expected = division * b.coordinate(i);
            if (!almost_equal(a.coordinate(i), expected))
                return false;
        }
        return true;
    }


    template <class T>
    bool direction<T>::zero_direction() const
    {
        auto a = this->radius_direction();
        for (T i : a.get_coordinates())
            if (!almost_equal(i, T(0.0)))
                return false;
        return true;
    }

    // ========================= Operator implementations =========================

    template <class T>
    tuple<point<T>, point<T>> direction<T>::operator+(const point<T>& other) const
    {
        auto A = get_beginning();
        auto B = get_end();
        return tuple(A, B + other);
    }

    template <class T>
    tuple<point<T>, point<T>> direction<T>::operator-(const point<T>& other) const
    {
        auto A = get_beginning();
        auto B = get_end();
        return tuple(A, B - other);
    }

    // direction<T> arguments (forward to point versions)
    template <class T>
    tuple<point<T>, point<T>> direction<T>::operator+(const direction<T>& other) const
    {
        auto A = get_beginning();
        auto B = get_end();
        auto C = other.get_beginning();
        auto D = other.get_end();
        return tuple(A, B + (D - C));
    }

    template <class T>
    tuple<point<T>, point<T>> direction<T>::operator-(const direction<T>& other) const
    {
        auto A = get_beginning();
        auto B = get_end();
        auto C = other.get_beginning();
        auto D = other.get_end();
        return tuple(A, B - (D - C));
    }


    // Same-N point element-wise ops
    template <class T>
    tuple<point<T>, point<T>> direction<T>::operator*(const point<T>& other) const
    {
        auto a = get_beginning();
        auto b = get_end();
        return tuple(a / other, b / other);
    }

    template <class T>
    tuple<point<T>, point<T>> direction<T>::operator/(const point<T>& other) const
    {
        auto a = get_beginning();
        auto b = get_end();
        return tuple(a / other, b / other);
    }


    // Same-N direction element-wise ops (forward to point ones)
    template <class T>
    tuple<point<T>, point<T>> direction<T>::operator*(const direction<T>& other) const
    {
        auto A = get_beginning();
        auto B = get_end();
        auto C = other.get_beginning();
        auto D = other.get_end();

        return tuple(A * C, B * D);
    }

    template <class T>
    tuple<point<T>, point<T>> direction<T>::operator/(const direction<T>& other) const
    {
        auto A = get_beginning();
        auto B = get_end();
        auto C = other.get_beginning();
        auto D = other.get_end();

        return tuple(A / C, B / D);
    }


    // Scalar ops
    template <class T>
    tuple<point<T>, point<T>> direction<T>::operator*(T value) const
    {
        auto A = get_beginning();
        auto B = get_end();
        return tuple(A * value, B * value);
    }

    template <class T>
    tuple<point<T>, point<T>> direction<T>::operator/(T value) const
    {
        auto A = get_beginning();
        auto B = get_end();
        return tuple(A / value, B / value);
    }

    template <class T>
    void direction<T>::check_compatible(const direction& other) const
    {
        auto A = get_beginning();
        auto B = get_end();
        auto C = other.get_beginning();
        auto D = other.get_end();
        if (A.axes() != B.axes() ||
            A.axes() != C.axes() ||
            C.axes() != D.axes())
            throw std::invalid_argument("Directions must have the same number of axes");
    }
}
#endif
