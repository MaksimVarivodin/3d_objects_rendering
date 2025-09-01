#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include <cstdint>
#include <memory>
#include "../point/point.hpp"
#include "../direction/direction.hpp"
#include "SFML/Graphics/Color.hpp"

namespace SpaceEngine
{
    extern const double PI_D;
    extern const float PI_F;
    extern const double RIGHT_ANGLE_D;
    extern const float RIGHT_ANGLE_F;
    extern const double ZERO_DEGREES_D;
    extern const float ZERO_DEGREES_F;

    enum vertex: uint8_t
    {
        vA,
        vB,
        vC
    };

    

    template <class T>
    class triangle
    {
        array<direction<T>, 3> vertices_ = {};
        array<T, 3> cachedRadianAngles_ = {};
        point<T> cachedNormalTo_ = {};
        sf::Color color_ = sf::Color{ 255, 255, 255, 255};
        bool isTextured_ = false;

    public:
        triangle() = default;
        triangle(point<T>* a, point<T>* b, point<T>* c, sf::Color color = { 255, 255, 255, 255});
        triangle(const point<T>& a, const point<T>& b, const point<T>& c, sf::Color color = {255, 255, 255, 255});
        direction<T>& operator[](vertex v);
        point<T> operator[](vertex v) const;
        sf::Color color() const;
        void color(sf::Color color);

        int angle_triangle_type() const;
        int sideTriangleType() const;

    private:
        void update_cached_radian_angles();
    };
}
#endif

#include "triangle.inl"
