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
    direction<T>::direction(const point<T>& beginning, const point<T>& end)
        : beginning_(make_shared<point<T>>(beginning)),
          end_(make_shared<point<T>>(end))
    {
        if (beginning_->axes() != end_->axes())
            throw std::invalid_argument("Beginning and end points must have the same number of axes");
        set_cached_values(beginning_, end_);
    }

    template <class T>
    direction<T>::direction(const point<T>& end)
        : beginning_(shared_ptr<point<T>>(&point_constraints::zero_point<T>, [](point<T>*)
          {
          })),
          end_(make_shared<point<T>>(end)),
          cachedLength_(-1)
    {
        if (beginning_->axes() != end_->axes())
            throw std::invalid_argument("Beginning and end points must have the same number of axes");
        set_cached_values(beginning_, end_);
    }

    template <class T>
    direction<T>::direction(point<T>* end)
        : beginning_(shared_ptr<point<T>>(&point_constraints::zero_point<T>, [](point<T>*)
          {
          })),
          end_(shared_ptr<point<T>>(end, [](point<T>*)
          {
          }))
    {
        if (beginning_->axes() != end_->axes())
            throw std::invalid_argument("Beginning and end points must have the same number of axes");
        set_cached_values(beginning_, end_);
    }


    template <class T>
    direction<T>::direction(point<T>* begin, point<T>* end)
        : beginning_(shared_ptr<point<T>>(begin, [](point<T>*)
          {
          })),
          end_(shared_ptr<point<T>>(end, [](point<T>*)
          {
          }))
    {
        if (beginning_->axes() != end_->axes())
            throw std::invalid_argument("Beginning and end points must have the same number of axes");
        set_cached_values(beginning_, end_);
    }

    template <class T>
    direction<T>::direction(const shared_ptr<point<T>>& begin, const shared_ptr<point<T>>& end)
        : beginning_(begin),
          end_(end)
    {
        if (beginning_->axes() != end_->axes())
            throw std::invalid_argument("Beginning and end points must have the same number of axes");
        set_cached_values(beginning_, end_);
    }

    template <class T>
    direction<T>::direction(const direction& other)
        : direction(other.beginning_, other.end_)
    {
    }

    template <class T>
    direction<T>& direction<T>::operator=(const direction& other)
    {
        direction<T> copy(other);
        *this = std::move(copy);
        return *this;
    }

    template <class T>
    direction<T>::direction(direction&& other) noexcept
        : beginning_{
              std::move(other.beginning_)
          },
          end_{
              std::move(other.end_)
          },
          cachedLength_(other.cachedLength_),
          cachedRadiusDirection_(other.cachedRadiusDirection_),
          cachedUnitDirection_(other.cachedUnitDirection_)
    {
        other.beginning_.reset();
        other.end_.reset();
        other.cachedLength_ = T(-1);
        cachedRadiusDirection_ = point<T>{cachedRadiusDirection_.axes()};
        cachedUnitDirection_ = point<T>{cachedUnitDirection_.axes()};
    }

    template <class T>
    direction<T>& direction<T>::operator=(direction&& other) noexcept
    {
        if (this != &other)
        {
            this->beginning_ = std::move(other.beginning_);
            this->end_ = std::move(other.end_);
            cachedLength_ = other.cachedLength_;
            cachedRadiusDirection_ = other.cachedRadiusDirection_;
            cachedUnitDirection_ = other.cachedUnitDirection_;
            other.cachedLength_ = T(-1);
            cachedRadiusDirection_ = point<T>{cachedRadiusDirection_.axes()};
            cachedUnitDirection_ = point<T>{cachedUnitDirection_.axes()};
            other.beginning_.reset();
            other.end_.reset();
        }
        return *this;
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
    T direction<T>::get_length() const
    {
        return cachedLength_;
    }

    template <class T>
    direction<T> direction<T>::get_unit_direction() const
    {
        return direction(cachedUnitDirection_);
    }

    template <class T>
    direction<T> direction<T>::get_radius_direction() const
    {
        return direction(cachedRadiusDirection_);
    }


    template <class T>
    T direction<T>::length(shared_ptr<point<T>> beginning, shared_ptr<point<T>> end) const
    {
        T sum(0);
        for (auto r = *end - *beginning; T i : r.get_coordinates())
            sum += i * i;
        return T(sqrt(sum));
    }

    template <class T>
    T direction<T>::cos_axis_angle(size_t axis) const
    {
        return this->get_radius_direction().get_end().coordinate(axis) / cachedLength_;
    }

    template <class T>
    T direction<T>::cos_vector_angle(const direction<T>& other) const
    {
        check_compatible(other);
        T sum(0);
        auto a = this->get_radius_direction().get_end();
        auto b = other.get_radius_direction().get_end();
        if (a->axes() != b->axes())
            throw std::invalid_argument("Cosine angle requires directions with the same number of axes");
        for (size_t i = 0; i < a.axes(); ++i)
            sum += a.coordinate(i) * b.coordinate(i);
        return sum / (this->get_length() * other.get_length());
    }

    template <class T>
    T direction<T>::projection(const direction<T>& other) const
    {
        check_compatible(other);
        if (other.zero_direction())
            throw std::invalid_argument("Cannot project on zero-direction");
        return dot_product(other) / other.get_length();
    }

    template <class T>
    T direction<T>::dot_product(const direction<T>& other) const
    {
        check_compatible(other);

        T sum(0);
        auto a = this->get_radius_direction().get_end();
        auto b = other.get_radius_direction().get_end();

        for (size_t i = 0; i < a.axes(); ++i)
            sum += a.coordinate(i) * b.coordinate(i);
        return sum;
    }

    template <class T>
    direction<T> direction<T>::cross_product(const direction<T>& other) const
    {
        check_compatible(other);
        auto a = this->get_radius_direction().get_end();
        auto b = other.get_radius_direction().get_end();

        if (a.axes() < 3 || b.axes() < 3)
            throw std::invalid_argument("Cross product is only defined for 3D directions");

        point<T> result(a.axes());
        result[x] = a.coordinate(y) * b.coordinate(z) - a.coordinate(z) * b.coordinate(y);
        result[y] = a.coordinate(z) * b.coordinate(x) - a.coordinate(x) * b.coordinate(z);
        result[z] = a.coordinate(x) * b.coordinate(y) - a.coordinate(y) * b.coordinate(x);
        if (a.axes() > 3)
            result[w] = T(1);
        return direction(result);
    }


    template <class T>
    direction<T> direction<T>::ort() const
    {
        auto o = this->get_radius_direction().get_end();

        if (almost_equal(cachedLength_, T(0.0)))
            throw std::invalid_argument("Cannot divide by zero");
        return {o / cachedLength_};
    }

    template <class T>

    bool direction<T>::equal(const direction<T>& other) const
    {
        check_compatible(other);
        auto a = this->get_radius_direction().get_end();
        auto b = other.get_radius_direction().get_end();

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
        auto a = this->get_radius_direction().get_end();
        auto b = other.get_radius_direction().get_end();

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
        auto a = this->get_radius_direction().get_end();
        for (T i : a.get_coordinates())
            if (!almost_equal(i, T(0.0)))
                return false;
        return true;
    }

    // ========================= Operator implementations =========================

    template <class T>
    direction<T> direction<T>::operator+(const point<T>& other) const
    {
        auto A = get_beginning();
        auto B = get_end();
        return direction(A, B + other);
    }

    template <class T>
    direction<T> direction<T>::operator-(const point<T>& other) const
    {
        auto A = get_beginning();
        auto B = get_end();
        return direction(A, B - other);
    }

    // direction<T> arguments (forward to point versions)
    template <class T>
    direction<T> direction<T>::operator+(const direction<T>& other) const
    {
        auto A = get_beginning();
        auto B = get_end();
        auto C = other.get_beginning();
        auto D = other.get_end();
        return direction(A, B + (D - C));
    }

    template <class T>
    direction<T> direction<T>::operator-(const direction<T>& other) const
    {
        auto A = get_beginning();
        auto B = get_end();
        auto C = other.get_beginning();
        auto D = other.get_end();
        return direction(A, B - (D - C));
    }


    // Same-N point element-wise ops
    template <class T>
    direction<T> direction<T>::operator*(const point<T>& other) const
    {
        auto a = get_beginning();
        auto b = get_end();
        return direction(a / other, b / other);
    }

    template <class T>
    direction<T> direction<T>::operator/(const point<T>& other) const
    {
        auto a = get_beginning();
        auto b = get_end();
        return direction(a / other, b / other);
    }


    // Same-N direction element-wise ops (forward to point ones)
    template <class T>
    direction<T> direction<T>::operator*(const direction<T>& other) const
    {
        auto A = get_beginning();
        auto B = get_end();
        auto C = other.get_beginning();
        auto D = other.get_end();

        return direction(A * C, B * D);
    }

    template <class T>
    direction<T> direction<T>::operator/(const direction<T>& other) const
    {
        auto A = get_beginning();
        auto B = get_end();
        auto C = other.get_beginning();
        auto D = other.get_end();

        return direction(A / C, B / D);
    }


    // Scalar ops
    template <class T>
    direction<T> direction<T>::operator*(T value) const
    {
        auto A = get_beginning();
        auto B = get_end();
        return direction(A * value, B * value);
    }

    template <class T>
    direction<T> direction<T>::operator/(T value) const
    {
        auto A = get_beginning();
        auto B = get_end();
        return direction(A / value, B / value);
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

    template <class T>
    void direction<T>::set_cached_values(const shared_ptr<point<T>>& begin, const shared_ptr<point<T>>& end)
    {
        cachedLength_ = this->length(begin, end);
        cachedRadiusDirection_ = *end - *begin;
        cachedUnitDirection_ = cachedRadiusDirection_ / cachedLength_;
    }
}
#endif
