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

sf::VertexArray arrayToLineTriangle(const triangle<double>& tr, sf::Color color)
{
    sf::VertexArray lines(sf::PrimitiveType::LineStrip, 4);

    lines[0].position = sf::Vector2f((float)(tr[vA].coordinate(x)), (float)tr[vA].coordinate(y));
    lines[1].position = sf::Vector2f((float)(tr[vB].coordinate(x)), (float)tr[vB].coordinate(y));
    lines[2].position = sf::Vector2f((float)(tr[vC].coordinate(x)), (float)tr[vC].coordinate(y));
    lines[3].position = sf::Vector2f((float)(tr[vA].coordinate(x)), (float)tr[vA].coordinate(y));

    for (int i = 0; i < 4; i++)
        lines[i].color = color;

    return lines;
}

sf::VertexArray arrayToTriangles(const triangle<double>& tr)
{
    sf::VertexArray triangles(sf::PrimitiveType::Triangles, 3);


    triangles[0].position = sf::Vector2f((float)(tr[vA].coordinate(x)), (float)tr[vA].coordinate(y));
    triangles[0].color = tr.color();
    triangles[1].position = sf::Vector2f((float)(tr[vB].coordinate(x)), (float)tr[vB].coordinate(y));
    triangles[1].color = tr.color();
    triangles[2].position = sf::Vector2f((float)(tr[vC].coordinate(x)), (float)tr[vC].coordinate(y));
    triangles[2].color = tr.color();
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
    //auto mesh = readObj("assets/teapot.obj");
    auto mesh = readObj("assets/axis.obj");
    // Creating projection matrix
    auto projectionMatrix = matrix<double>::projection_matrix(double(viewSizeX) / double(viewSizeY));


    auto translationMatrix = matrix<double>::translation_matrix({4, 0.0f, 0.0f, 20.f});

    // Camera
    point<double> vCamera{4, 0.0f, 0.0f, 0.0f}; // Camera position in 4D space
    point<double> vLookDir{4, 0.0f, 0.0f, 1.0f}; // Point the camera is looking at
    // Normalized light direction
    auto lightOrt = direction<double>{{4, 0.0f, 5.0f, -20.0f}}.ort();

    auto elapsed = clock.getElapsedTime().asSeconds();

    while (window.isOpen())
    {
        window.clear();
        renderTexture.clear();
        // Time-based rotation angle
        auto fTheta = clock.getElapsedTime().asSeconds() - elapsed;
        elapsed += fTheta;
        //std::cout << "Theta: " << fTheta << "\n";

        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (auto key = event->getIf<sf::Event::KeyPressed>())
            {
                switch (key->scancode)
                {
                case sf::Keyboard::Scancode::Up:
                    vCamera[y] += 100.0* fTheta;
                    break;
                case sf::Keyboard::Scancode::Down:
                    vCamera[y] -= 100.0* fTheta;
                    break;
                default:
                    break;
                }
            }
        }


        
        /*auto rotationMatrix = matrix<double>::rotation_matrix({4, fTheta * 0.3, fTheta * 0.1, 0.});*/
        auto rotationMatrix = matrix<double>::rotation_matrix({4, 0., 0., 0.});
        auto worldMatrix = matrix<double>::identity_matrix(4) * rotationMatrix * translationMatrix;

        auto cameraUp = point<double>{{4, 0.0f, 1.0f, 0.0f}};
        auto cameraForward = direction<double>{vCamera, vLookDir};

        point<double> vUp = {4, 0., 1., 0.};
        point<double> vTarget = {4, 0., 0., 1.};
        vTarget = vCamera + vLookDir;
        auto matView = matrix<double>::look_at(vCamera,  vTarget, vUp);

        // Store triangles to rasterize
        std::vector<triangle<double>> toRasterize;

        toRasterize.reserve(mesh.size());

        // Pipeline
        for (const auto& meshTriangle : mesh)
        {
            std::vector<point<double>> triangleProjected(meshTriangle.size());

            for (size_t i = 0; i < meshTriangle.size(); ++i)
            {
                // Rotate
                triangleProjected[i] = meshTriangle[i] * worldMatrix;
            }


            direction D{&triangleProjected[0], &triangleProjected[1]};
            direction E{&triangleProjected[0], &triangleProjected[2]};
            direction F{&triangleProjected[2], &triangleProjected[1]};


            // Проверяем коллинеарность - если векторы коллинеарны, пропускаем треугольник
            /*if (D.collinear(E) || D.collinear(F))
                continue;*/


            auto triangleNormal = D.cross_product(E).ort();


            auto cameraToTriangle = direction{D.get_beginning() - vCamera}.ort();
            auto isInLineOfSight = triangleNormal.dot_product(cameraToTriangle);


            if (isInLineOfSight < 0.0f)
            // Check if the triangle is facing the camera
            {
                double lightIntensity = lightOrt.dot_product(triangleNormal);
                auto triangleColor = sf::Color{
                    static_cast<uint8_t>(std::max(0.004, lightIntensity) * 255.0f),
                    static_cast<uint8_t>(std::max(0.004, lightIntensity) * 255.0f),
                    static_cast<uint8_t>(std::max(0.004, lightIntensity) * 255.0f),
                    255
                };
                for (size_t i = 0; i < meshTriangle.size(); ++i)
                {
                    // World space to view space
                    triangleProjected[i] *= matView;

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
                toRasterize.emplace_back(triangleProjected[0],
                                         triangleProjected[1],
                                         triangleProjected[2],
                                         triangleColor);
            }
        }

        // Sort triangles
        std::ranges::sort(toRasterize.begin(), toRasterize.end(),
                          [](const triangle<double>& a, const triangle<double>& b)
                          {
                              double avgAz = std::min(a[vA].coordinate(axis::z),
                                                      std::min(a[vB].coordinate(axis::z), a[vC].coordinate(axis::z)));
                              double avgBz = std::min(b[vA].coordinate(axis::z),
                                                      std::min(b[vB].coordinate(axis::z), b[vC].coordinate(axis::z)));
                              return avgAz > avgBz; // Sort in descending order
                          });


        for (auto& triangle : toRasterize)
        {
            /*renderTexture.draw(arrayToTriangles(triangle));
            renderTexture.draw(arrayToLineTriangle(triangle, sf::Color::White));*/
            window.draw(arrayToTriangles(triangle));
            //window.draw(arrayToLineTriangle(triangle, sf::Color::White));
        }
        /*renderTexture.display();
        window.draw(bufferSprite);*/
        window.display();

        /*window.draw(bufferSprite);*/
        //window.draw(createVertexBuffer(toRasterize, vb));
    }
    return 0;
}
