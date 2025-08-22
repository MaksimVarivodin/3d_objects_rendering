#define _USE_MATH_DEFINES
#include <iostream>

#include <chrono>
#include <SFML/Graphics.hpp>
#include "BackgroundThread/BackgroundThread.hpp"
#include "math/direction/direction.hpp"
#include "math/point/point.hpp"
#include "math/matrix/matrix.hpp"

#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
using namespace se;


std::vector<std::vector<SpaceEngine::point<float>>> generateMeshCube()
{
    std::vector<std::vector<SpaceEngine::point<float>>> triangles = {
        {
            // South face, triangle 1
            {{4, 0.0f, 0.0f, 0.0f}, {4, 0.0f, 1.0f, 0.0f}, {4, 1.0f, 1.0f, 0.0f}},
            // South face, triangle 2
            {{4, 0.0f, 0.0f, 0.0f}, {4, 1.0f, 1.0f, 0.0f}, {4, 1.0f, 0.0f, 0.0f}},

            // East face, triangle 1
            {{4, 1.0f, 0.0f, 0.0f}, {4, 1.0f, 1.0f, 0.0f}, {4, 1.0f, 1.0f, 1.0f}},
            // East face, triangle 2
            {{4, 1.0f, 0.0f, 0.0f}, {4, 1.0f, 1.0f, 1.0f}, {4, 1.0f, 0.0f, 1.0f}},

            // North face, triangle 1
            {{4, 1.0f, 0.0f, 1.0f}, {4, 1.0f, 1.0f, 1.0f}, {4, 0.0f, 1.0f, 1.0f}},
            // North face, triangle 2
            {{4, 1.0f, 0.0f, 1.0f}, {4, 0.0f, 1.0f, 1.0f}, {4, 0.0f, 0.0f, 1.0f}},

            // West face, triangle 1
            {{4, 0.0f, 0.0f, 1.0f}, {4, 0.0f, 1.0f, 1.0f}, {4, 0.0f, 1.0f, 0.0f}},
            // West face, triangle 2
            {{4, 0.0f, 0.0f, 1.0f}, {4, 0.0f, 1.0f, 0.0f}, {4, 0.0f, 0.0f, 0.0f}},

            // Top face, triangle 1
            {{4, 0.0f, 1.0f, 0.0f}, {4, 0.0f, 1.0f, 1.0f}, {4, 1.0f, 1.0f, 1.0f}},
            // Top face, triangle 2
            {{4, 0.0f, 1.0f, 0.0f}, {4, 1.0f, 1.0f, 1.0f}, {4, 1.0f, 1.0f, 0.0f}},

            // Bottom face, triangle 1
            {{4, 1.0f, 0.0f, 1.0f}, {4, 0.0f, 0.0f, 1.0f}, {4, 0.0f, 0.0f, 0.0f}},
            // Bottom face, triangle 2
            {{4, 1.0f, 0.0f, 1.0f}, {4, 0.0f, 0.0f, 0.0f}, {4, 1.0f, 0.0f, 0.0f}}
        }
    };
    return triangles;
}

sf::VertexArray arrayToLineTriangle(const std::tuple<std::vector<point<float>>, sf::Color>& points)
{
    sf::VertexArray lines(sf::PrimitiveType::LineStrip, 4);
    
    auto &[tr, color] = points;
    lines[0].position = sf::Vector2f(tr[0].coordinate(0), tr[0].coordinate(1));
    lines[1].position = sf::Vector2f(tr[1].coordinate(0), tr[1].coordinate(1));
    lines[2].position = sf::Vector2f(tr[2].coordinate(0), tr[2].coordinate(1));
    lines[3].position = sf::Vector2f(tr[0].coordinate(0), tr[0].coordinate(1)); // замкнуть обратно

    for (int i = 0; i < 4; i++)
        lines[i].color = sf::Color::White;

    return lines;
}

sf::VertexArray arrayToTriangles(const std::tuple<std::vector<point<float>>, sf::Color>& points)
{
    auto &[tr, color] = points;
    sf::VertexArray triangles(sf::PrimitiveType::Triangles, tr.size());

    
    for (size_t i = 0; i < tr.size(); i++)
    {
        triangles[i].position = sf::Vector2f(tr[i].coordinate(0), tr[i].coordinate(1));
        triangles[i].color = color; // назначаем цвет
    }
    return triangles;
}

std::vector<std::vector<point<float>>> readObj(string fileName)
{
    ifstream file(fileName);

    if (!file.is_open())
    {
        std::cerr << "Could not open the file: " << fileName << std::endl;
        return {};
    }
    std::vector<point<float>> points;
    std::vector<std::vector<point<float>>> triangles;
    // Read vertices
    while (!file.eof())
    {
        char line[128];
        file.getline(line, 128);
        stringstream ss(line);
        string prefix;
        ss >> prefix;
        if (prefix == "v") // vertex
        {
            float x, y, z;
            ss >> x >> y >> z;
            points.push_back({4, x, y, z, 1.0}); // 4D point with w = 1.0f
        }
        else if (prefix == "f") // face
        {
            std::vector<point<float>> triangle;
            int index;
            for (int i = 0; i < 3; ++i) // assuming triangles
            {
                ss >> index; // read vertex index
                triangle.push_back(points[index - 1]); // indices in obj are 1-based
            }
            triangles.push_back(triangle);
        }
    }

    return triangles;
}

std::string getCurrentDir()
{
    return std::filesystem::current_path().string();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "Space Traveler");
    window.setFramerateLimit(60); // reduce CPU usage in the render loop
    std::cout << "Текущая директория: " << getCurrentDir() << std::endl;
    //auto mesh = generateMeshCube();
    auto mesh = readObj("assets/VideoShip.obj");
    auto projectionMatrix = matrix<float>::projection_matrix(float(window.getSize().y) / float(window.getSize().x));

    sf::Clock clock;
    point<float> cameraPosition{4, 0.0f, 0.0f, -1.0f, 1.0f}; // Camera position in 4D space
    while (window.isOpen())
    {
        window.clear();
        auto rotationMatrix = matrix<float>::rotation_matrix({
            4,
            float(clock.getElapsedTime().asMilliseconds() / 1000.f),
            float(clock.getElapsedTime().asMilliseconds() / 2500.f),
            float(clock.getElapsedTime().asMilliseconds() / 5000.f),
            1.0
    });
        // Combine rotation matrices
        

        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        std::vector<std::tuple<vector<point<float>>, sf::Color>> toRasterize;
        toRasterize.reserve(mesh.size());
        // Pipeline
        for (const auto& meshTriangle : mesh)
        {
            std::array<matrix<float>, 3> triangleToDraw;

            // each point in triangle

            for (size_t i = 0; i < meshTriangle.size(); ++i)
            {
                // Rotate
                triangleToDraw[i] = matrix<float>{{meshTriangle[i]}} * rotationMatrix;

                // Offset by z
                triangleToDraw[i](0, 2) += 10.0f; // Move the cube away from the camera
            }
            point<float> pA{triangleToDraw[0].get_table()[0]};
            point<float> pB{triangleToDraw[1].get_table()[0]};
            point<float> pC{triangleToDraw[2].get_table()[0]};
            std::cout << "A\t" << pA[0] << " " << pA[1] << " " << pA[2] << std::endl;
            std::cout << "B\t" << pB[0] << " " << pB[1] << " " << pB[2] << std::endl;
            std::cout << "C\t" << pC[0] << " " << pC[1] << " " << pC[2] << std::endl;
            // 0->1
            direction A{pA, pB};
            // 0->2
            direction B{pA, pC};
            direction C{pB, pC};
            
            // Проверяем коллинеарность - если векторы коллинеарны, пропускаем треугольник
            if (A.collinear(B) || A.collinear(C) || B.collinear(C))
                continue;

            auto normalP = A.cross_product(B);
            auto zeroP = point<float>{4, 0.0f, 0.0f, 0.0f, 0.0f};

            std::cout << "N\t" << normalP[0] << " " << normalP[1] << " " << normalP[2] << std::endl;

            auto normalD = direction{zeroP, normalP}.ort();
            auto p = pA - cameraPosition;
            auto ort = direction<float>(zeroP, p).ort();
            if (direction{zeroP, normalP}.dot_product({zeroP, ort}) < 0.0f)
            // Check if the triangle is facing the camera
            {
                point<float> lightP = {4, 0.0f, 0.0f, -1.0f, 0.0f}; // Light position in 4D space
                auto light = direction{zeroP, lightP}.ort();
                float lightIntensity = direction{zeroP, normalD}.dot_product({zeroP, light});
                auto triangleColor = sf::Color{
                    static_cast<uint8_t>(std::max(0.04f, lightIntensity) * 50.0f),
                    static_cast<uint8_t>(std::max(0.04f, lightIntensity) * 50.0f),
                    static_cast<uint8_t>(std::max(0.04f, lightIntensity) * 50.0f),
                    255
                };
                for (size_t i = 0; i < meshTriangle.size(); ++i)
                {
                    // Project
                    triangleToDraw[i] *= projectionMatrix;
                    float w = triangleToDraw[i](0, 3);
                    if (w != 0.0f)
                    {
                        triangleToDraw[i] /= w;
                    }

                    // Scale
                    triangleToDraw[i] += 1.0f;
                    triangleToDraw[i] *= 0.5f * float(window.getSize().x);
                    
                }
                point<float> A{3, triangleToDraw[0](0, 0), triangleToDraw[0](0, 1),  triangleToDraw[0](0, 2)};
                point<float> B{3, triangleToDraw[1](0, 0), triangleToDraw[1](0, 1),  triangleToDraw[1](0, 2)};
                point<float> C{3, triangleToDraw[2](0, 0), triangleToDraw[2](0, 1),  triangleToDraw[2](0, 2)};
                toRasterize.emplace_back(vector{A, B, C}, triangleColor);                
            }
        }

        // Sort triangles
        std::sort(toRasterize.begin(), toRasterize.end(),
            [](const auto& a, const auto& b) {
                auto [firstA, secondA] = a;
                auto [firstB, secondB] = b;
                // Sort by the average z-coordinate of the triangle
                float avgA = (firstA[0][2] + firstA[1][2] + firstA[2][2]) / 3.0;
                float avgB = (firstB[0][2] + firstB[1][2] + firstB[2][2]) / 3.0;
                return avgA > avgB; // Sort in descending order
            });
        for (const auto & triangle : toRasterize)
        {
            window.draw(arrayToTriangles(triangle));
            //window.draw(arrayToLineTriangle(triangle));
        }
        
        
        window.display();
    }
    return 0;
}
