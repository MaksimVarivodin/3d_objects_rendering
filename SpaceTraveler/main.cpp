#define _USE_MATH_DEFINES
#include <iostream>

#include <chrono>
#include <SFML/Graphics.hpp>
#include "BackgroundThread/BackgroundThread.hpp"
#include "math/matrix/matrix.hpp"
#include "math/point/point.hpp"
#include "math/direction/direction.hpp"
#include <vector>
#include <cmath>
using namespace se;
using namespace engine_lib;


matrix<point<float, 4>, 12, 3> generateMeshCube()
{
    auto meshCube = matrix{
        array<array<point<float, 4>, 3>, 12>{
            {
                // South face, triangle 1
                {point<float, 4>{0.0, 0.0, 0.0}, point<float, 4>{0.0, 1.0, 0.0}, point<float, 4>{1.0, 1.0, 0.0}},
                // South face, triangle 2
                {point<float, 4>{0.0, 0.0, 0.0}, point<float, 4>{1.0, 1.0, 0.0}, point<float, 4>{1.0, 0.0, 0.0}},

                // East face, triangle 1
                {point<float, 4>{1.0, 0.0, 0.0}, point<float, 4>{1.0, 1.0, 0.0}, point<float, 4>{1.0, 1.0, 1.0}},
                // East face, triangle 2
                {point<float, 4>{1.0, 0.0, 0.0}, point<float, 4>{1.0, 1.0, 1.0}, point<float, 4>{1.0, 0.0, 1.0}},

                // North face, triangle 1
                {point<float, 4>{1.0, 0.0, 1.0}, point<float, 4>{1.0, 1.0, 1.0}, point<float, 4>{0.0, 1.0, 1.0}},
                // North face, triangle 2
                {point<float, 4>{1.0, 0.0, 1.0}, point<float, 4>{0.0, 1.0, 1.0}, point<float, 4>{0.0, 0.0, 1.0}},

                // West face, triangle 1
                {point<float, 4>{0.0, 0.0, 1.0}, point<float, 4>{0.0, 1.0, 1.0}, point<float, 4>{0.0, 1.0, 0.0}},
                // West face, triangle 2
                {point<float, 4>{0.0, 0.0, 1.0}, point<float, 4>{0.0, 1.0, 0.0}, point<float, 4>{0.0, 0.0, 0.0}},

                // Top face, triangle 1
                {point<float, 4>{0.0, 1.0, 0.0}, point<float, 4>{0.0, 1.0, 1.0}, point<float, 4>{1.0, 1.0, 1.0}},
                // Top face, triangle 2
                {point<float, 4>{0.0, 1.0, 0.0}, point<float, 4>{1.0, 1.0, 1.0}, point<float, 4>{1.0, 1.0, 0.0}},

                // Bottom face, triangle 1
                {point<float, 4>{1.0, 0.0, 1.0}, point<float, 4>{0.0, 0.0, 1.0}, point<float, 4>{0.0, 0.0, 0.0}},
                // Bottom face, triangle 2
                {point<float, 4>{1.0, 0.0, 1.0}, point<float, 4>{0.0, 0.0, 0.0}, point<float, 4>{1.0, 0.0, 0.0}}
            }
        }
    };
    return meshCube;
}

sf::VertexArray arrayToLineTriangle(const std::array<std::array<float, 2>, 3>& points)
{
    sf::VertexArray lines(sf::PrimitiveType::LineStrip, 4);

    lines[0].position = sf::Vector2f(points[0][0], points[0][1]);
    lines[1].position = sf::Vector2f(points[1][0], points[1][1]);
    lines[2].position = sf::Vector2f(points[2][0], points[2][1]);
    lines[3].position = sf::Vector2f(points[0][0], points[0][1]); // замкнуть обратно

    for (int i = 0; i < 4; i++)
        lines[i].color = sf::Color::White;

    return lines;
}

sf::VertexArray arrayToTriangles(const std::array<std::array<float, 2>, 3>& points, sf::Color color)
{
    sf::VertexArray triangles(sf::PrimitiveType::Triangles, points.size());

    for (size_t i = 0; i < points.size(); i++)
    {
        triangles[i].position = sf::Vector2f(points[i][0], points[i][1]);;
        triangles[i].color = color; // назначаем цвет
    }
    return triangles;
}

matrix<float, 4, 4> generateProjectionMatrix(
    float AspectRatio,
    float Near = 0.1f,
    float Far = 1000.0f,
    float FOV = 90.0f)
{
    float FovRad = 1.0f / (tanf((FOV / 360.0f) * M_PI));
    return matrix{
        std::array<std::array<float, 4>, 4>{
            {
                {AspectRatio * FovRad, 0.0f, 0.0f, 0.0f},
                {0.0f, FovRad, 0.0f, 0.0f},
                {0.0f, 0.0f, Far / (Far - Near), 1.0f},
                {0.0f, 0.0f, (-Far * Near) / (Far - Near), 0.0f}
            }
        }
    };
}

matrix<float, 4, 4> generateRotationMatrix(float fTheta)
{
    return matrix{

        // Z-axis rotation matrix
        std::array<std::array<float, 4>, 4>{
            {
                {cosf(fTheta), sinf(fTheta), 0.0f, 0.0f},
                {-sinf(fTheta), cosf(fTheta), 0.0f, 0.0f},
                {0.0f, 0.0f, 1.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 1.0f}
            }
        }
    } * matrix{

        // X-axis rotation matrix
        std::array<std::array<float, 4>, 4>{
            {
                {1.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, cosf(fTheta * 0.5f), sinf(fTheta * 0.5f), 0.0f},
                {0.0f, -sinf(fTheta * 0.5f), cosf(fTheta * 0.5f), 0.0f},
                {0.0f, 0.0f, 0.0f, 1.0f}
            }
        }
    };
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Space Traveler");
    window.setFramerateLimit(60); // reduce CPU usage in the render loop
    auto meshCube = generateMeshCube();
    auto projectionMatrix =
        generateProjectionMatrix(float(window.getSize().x) / float(window.getSize().y));
    sf::Clock clock;
    point cameraPosition{array{0.0f, 0.0f, 0.0f, 0.0f}}; // Camera position in 4D space
    while (window.isOpen())
    {
        window.clear();
        auto rotationMatrix = generateRotationMatrix(float(clock.getElapsedTime().asMilliseconds() / 1000.f));

        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        // Pipeline
        for (const auto& row : meshCube.get_table())
        {
            std::array<array<float, 2>, 3> projectedPoints;
            std::array<matrix1D<float, 4>, 3> triangle;
            
            // each point in triangle

            for (size_t i = 0; i < row.size(); ++i)
            {
                // Rotate
                triangle[i] = matrix1D{row[i]} * rotationMatrix;

                // Offset by z
                triangle[i](0, 2) += 3.0f; // Move the cube away from the camera
            }
            
            // 0->1
            direction A{triangle[0].get_table()[0], triangle[1].get_table()[0]};
            // 0->2
            direction B{triangle[0].get_table()[0], triangle[2].get_table()[0]};
            auto normal = A.cross_product(B).ort();
            auto p = point{triangle[0].get_table()[0]};
            
            if (normal.dot_product(direction(p - cameraPosition).ort()) < 0.0f) // Check if the triangle is facing the camera
            {
                direction light = direction{array{0.0f, 0.0f, -1.0f, 0.0f}}.ort();
                float lightIntensity = normal.dot_product(light);
                auto triangleColor = sf::Color{static_cast<uint8_t>(std::max(0.0f, lightIntensity) * 75.0f),
                                            static_cast<uint8_t>(std::max(0.0f, lightIntensity) * 75.0f),
                                            static_cast<uint8_t>(std::max(0.0f, lightIntensity) * 75.0f),
                                            255};
                for (size_t i = 0; i < row.size(); ++i)
                {
                    // Project
                    triangle[i] *= projectionMatrix;
                    float w = triangle[i](0, 3);
                    if (w != 0.0f)
                    {
                        triangle[i] /= w;
                    }

                    // Scale
                    triangle[i] += 1.0f;
                    triangle[i] *= 0.5f * float(window.getSize().x > window.getSize().y
                                             ? window.getSize().y
                                             : window.getSize().x);

                    // Store projected points
                    projectedPoints[i][0] = triangle[i](0, 0);
                    projectedPoints[i][1] = triangle[i](0, 1);
                }


                window.draw(arrayToTriangles(projectedPoints, triangleColor));
                window.draw(arrayToLineTriangle(projectedPoints));
            }
        }

        window.display();
    }
    return 0;
}
