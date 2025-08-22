#define _USE_MATH_DEFINES
#include <iostream>

#include <chrono>
#include <SFML/Graphics.hpp>
#include "BackgroundThread/BackgroundThread.hpp"
#include "math/direction/direction.hpp"
#include "math/point/point.hpp"
#include "math/matrix/matrix.hpp"
#include "math/triangle/triangle.hpp"
#include <vector>

#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
using namespace se;
using namespace se;

std::vector<std::vector<SpaceEngine::point<double>>> generateMeshCube()
{
    std::vector<std::vector<SpaceEngine::point<double>>> triangles = {
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

sf::VertexArray arrayToLineTriangle(vector<point<double>>& tr, sf::Color color)
{
    sf::VertexArray lines(sf::PrimitiveType::LineStrip, 4);

    lines[0].position = sf::Vector2f((float)(tr[0][x]), (float)(tr[0][y]));
    lines[1].position = sf::Vector2f((float)(tr[1][x]), (float)(tr[1][y]));
    lines[2].position = sf::Vector2f((float)(tr[2][x]), (float)(tr[2][y]));
    lines[3].position = sf::Vector2f((float)(tr[0][x]), (float)(tr[0][y])); // замкнуть обратно

    for (int i = 0; i < 4; i++)
        lines[i].color = sf::Color::White;

    return lines;
}

sf::VertexArray arrayToTriangles(std::vector<point<double>>& points, sf::Color color)
{
    sf::VertexArray triangles(sf::PrimitiveType::Triangles, points.size());

    for (size_t i = 0; i < points.size(); i++)
    {
        triangles[i].position = sf::Vector2f((int)(points[i][0]), (int)points[i][1]);
        triangles[i].color = color;
    }
    return triangles;
}

void createVertexBuffer(const std::vector<std::tuple<std::vector<point<double>>, sf::Color>>& points,
                        sf::VertexBuffer& vb,
                        size_t startIndex,
                        size_t endIndex)
{
    vb.create((endIndex - startIndex) * 3); // 3 вершины на треугольник

    std::vector<sf::Vertex> vertices((endIndex - startIndex) * 3);
    size_t pointsIndex = startIndex;
    for (size_t vertexIndex = 0; vertexIndex < vertices.size(); ++pointsIndex)
    {
        const auto& [tr, color] = points[pointsIndex];
        if (tr.size() != 3) continue;
        for (size_t i = 0; i < 3; ++i)
        {
            vertices[vertexIndex].position = sf::Vector2f(tr[i].coordinate(0), tr[i].coordinate(1));
            vertices[vertexIndex].color = color;
            ++vertexIndex;
        }
    }
    if (!vb.update(vertices.data(), vertices.size(), 0))
    {
        std::cerr << "Failed to update vertex buffer" << std::endl;
    }
}

std::vector<std::vector<point<double>>> readObj(string fileName)
{
    ifstream file(fileName);

    if (!file.is_open())
    {
        std::cerr << "Could not open the file: " << fileName << std::endl;
        return {};
    }
    std::vector<point<double>> points;
    std::vector<std::vector<point<double>>> triangles;
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
            double x, y, z;
            ss >> x >> y >> z;
            points.push_back({4, x, y, z}); // 4D point with w = 1.0f
        }
        else if (prefix == "f") // face
        {
            std::vector<point<double>> triangle;
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
    sf::Color c{};
    
    constexpr size_t sizeX = 1080;
    constexpr size_t sizeY = 1080;
    constexpr size_t viewSizeX = sizeX / 4;
    constexpr size_t viewSizeY = sizeY / 4;
    uint32_t frameLimit = 240;

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({sizeX, sizeY}),
        "Space Traveler",
        sf::Style::Default, sf::State::Windowed, settings);

    // Define a view that's half the size of the window, effectively doubling pixel size
    sf::View view1(sf::FloatRect({0, 0}, {viewSizeX, viewSizeY}));
    window.setView(view1);
    sf::RenderTexture renderTexture({viewSizeX, viewSizeY});
    sf::Sprite bufferSprite(renderTexture.getTexture());
    window.setFramerateLimit(frameLimit); // reduce CPU usage in the render loop

    //window.setFramerateLimit(240); // reduce CPU usage in the render loop


    std::cout << "Текущая директория: " << getCurrentDir() << "\n";
    //auto mesh = generateMeshCube();

    sf::Clock clock;

    // Loading mesh from .obj file
    //auto mesh = readObj("assets/VideoShip.obj");
    auto mesh = readObj("assets/teapot.obj");
    //auto mesh = readObj("assets/axis.obj");
    // Creating projection matrix
    auto projectionMatrix = matrix<double>::projection_matrix(double(viewSizeX) / double(viewSizeY));


    auto translationMatrix = matrix<double>::translation_matrix({4, 0.0f, 0.0f, 8.f});
    // Creating zero-point
    auto zeroP = point<double>{4, 0.0f, 0.0f, 0.0f, 0.0f};

    // Camera
    point<double> cameraPosition{4, 0.0f, 0.0f, -1.0f}; // Camera position in 4D space

    // Normalized light direction
    point<double> lightOrt = {4, 0.0f, 0.0f, -1.0f}; // Light position in 4D space
    lightOrt = direction{zeroP, lightOrt}.ort();


    while (window.isOpen())
    {
        window.clear();
        renderTexture.clear();
        // Combine rotation matrices


        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }


        // Time-based rotation angle
        auto fTheta = clock.getElapsedTime().asSeconds();
        auto rotationMatrix = matrix<double>::rotation_matrix({4, fTheta, 0., fTheta * 0.5, 1.0});

        // Store triangles to rasterize
        std::vector<vector<point<double>>> toRasterize;
        vector<sf::Color> colors;
        toRasterize.reserve(mesh.size());
        colors.reserve(mesh.size());

        // Pipeline
        for (const auto& meshTriangle : mesh)
        {
            std::vector<point<double>> triangleProjected(meshTriangle.size(), {4, 0.0f, 0.0f, 0.0f});
            
            for (size_t i = 0; i < meshTriangle.size(); ++i)
            {
                // Rotate
                triangleProjected[i] = meshTriangle[i] * rotationMatrix;
                // Translate
                triangleProjected[i] *= translationMatrix;
            }


            direction D{triangleProjected[0], triangleProjected[1]};
            direction E{triangleProjected[0], triangleProjected[2]};
            direction F{triangleProjected[1], triangleProjected[2]};


            // Проверяем коллинеарность - если векторы коллинеарны, пропускаем треугольник
            /*if (D.collinear(E) || D.collinear(F))
                continue;*/


            auto triangleNormalRef = D.cross_product(E);
            auto triangleNormalOrtRef = direction{zeroP, triangleNormalRef}.ort();


            auto cameraToTriangle = triangleProjected[0] - cameraPosition;


            auto cameraToCenterOrt = direction{zeroP, cameraToTriangle}.ort();
            auto isInLineOfSightRef = direction{zeroP, triangleNormalOrtRef}.dot_product({zeroP, cameraToCenterOrt});


            if (isInLineOfSightRef < 0.0f)
            // Check if the triangle is facing the camera
            {
                double lightIntensity = direction{zeroP, triangleNormalOrtRef}.dot_product({zeroP, lightOrt});
                auto triangleColor = sf::Color{
                    static_cast<uint8_t>(std::max(0.04, lightIntensity) * 50.0f),
                    static_cast<uint8_t>(std::max(0.04, lightIntensity) * 50.0f),
                    static_cast<uint8_t>(std::max(0.04, lightIntensity) * 50.0f),
                    255
                };
                for (size_t i = 0; i < meshTriangle.size(); ++i)
                {
                    // Project
                    triangleProjected[i] *= projectionMatrix;
                    double w = triangleProjected[i][3];
                    if (!almost_equal(w, 0.0))
                    {
                        triangleProjected[i] /= w;
                    }

                    // Scale
                    triangleProjected[i] += 1.0f;
                    triangleProjected[i] *= 0.5f * double(viewSizeX);
                }
                // Add to rasterization list if within view
                toRasterize.emplace_back(vector{triangleProjected[0], triangleProjected[1], triangleProjected[2]});
                colors.push_back(triangleColor);
            }
        }

        // Sort triangles
        std::ranges::sort(toRasterize.begin(), toRasterize.end(),
                          [](const auto& a, const auto& b)
                          {
                              // Sort by the average z-coordinate of the triangle
                              double avgAz = (
                                      a[0].coordinate(axis::z) +
                                      a[1].coordinate(axis::z) +
                                      a[2].coordinate(axis::z))
                                  / 3.0f;
                              double avgBz = (
                                      b[0].coordinate(axis::z) +
                                      b[1].coordinate(axis::z) +
                                      b[2].coordinate(axis::z))
                                  / 3.0f;

                              return avgAz > avgBz; // Sort in descending order
                          });


        size_t i = 0;
        for (auto& triangle : toRasterize)
        {
            /*renderTexture.draw(arrayToTriangles(triangle, colors[i]));
            renderTexture.draw(arrayToLineTriangle(triangle, sf::Color::White));*/
            window.draw(arrayToTriangles(triangle, colors[i]));
            window.draw(arrayToLineTriangle(triangle, sf::Color::White));
            ++i;
        }
        /*renderTexture.display();
        window.draw(bufferSprite);*/
        window.display();

        /*window.draw(bufferSprite);*/
        //window.draw(createVertexBuffer(toRasterize, vb));
    }
    return 0;
}
