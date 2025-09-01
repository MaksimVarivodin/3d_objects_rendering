#ifndef TRIANGLE_INL
#define TRIANGLE_INL

namespace SpaceEngine
{
    template <class T>
    triangle<T>::triangle(point<T>* a, point<T>* b, point<T>* c, sf::Color color)
        : vertices_{
              direction<T>(a, b),
              direction<T>(b, c),
              direction<T>(c, a)
          },
          color_(color)
    {
    }

    template <class T>
    triangle<T>::triangle(const point<T>& a, const point<T>& b, const point<T>& c, sf::Color color)
        : vertices_{
              direction<T>(a, b),
              direction<T>(b, c),
              direction<T>(c, a)
          },
          color_(color)
    {
    }


    template <class T>
    direction<T>& triangle<T>::operator[](vertex v)
    {
        return &vertices_[(size_t)v];
    }

    template <class T>
    point<T> triangle<T>::operator[](vertex v) const
    {
        return vertices_[(size_t)v].get_beginning();
    }

    template <class T>
    sf::Color triangle<T>::color() const
    {
        return color_;
    }

    template <class T>
    int triangle<T>::angle_triangle_type() const
    {
        // obtuse angle:
        for (const auto& el : cachedRadianAngles_)
        {
            if (el > RIGHT_ANGLE_D)
                return 1;
        }
        // right angle:
        return (cachedRadianAngles_[vA] == RIGHT_ANGLE_D ||
                   cachedRadianAngles_[vB] == RIGHT_ANGLE_D ||
                   cachedRadianAngles_[vC] == RIGHT_ANGLE_D)
                   ?
                   // return is right angle if one of angles is 90 degrees   
                   0
                   :
                   // else acute angle:
                   -1;
    }

    template <class T>
    void triangle<T>::update_cached_radian_angles()
    {
    }
}
#endif
