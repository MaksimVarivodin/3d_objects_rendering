#pragma once
#include <cstdint>
#include <memory>
#include "../point/point.hpp"

namespace SpaceEngine
{
    enum vertex: uint8_t
    {
        A,
        B,
        C
    };

    enum rgba: uint8_t
    {
        r,
        g,
        b,
        a
    };

    using triangle_c = point<uint8_t>;

    template <class T>
    class triangle
    {
        std::shared_ptr<point<T>> vertices_[3] = {};
        triangle_c color_ = {4, 255, 255, 255, 255};

    public:
        triangle() = default;
        triangle(point<T>& a, point<T>& b, point<T>& c, triangle_c color = {4, 255, 255, 255, 255});

        point<T>& operator[](vertex v);
        const point<T>& operator[](vertex v) const;
        triangle_c color() const;
        void color(triangle_c color);
    };
}
