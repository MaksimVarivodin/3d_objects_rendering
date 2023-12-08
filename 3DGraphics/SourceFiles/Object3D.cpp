#include "..\headers\Object3D.h"

Object3D Object3D::rotate(Point rotation)
{
    return Object3D{ 
        Point::rotate(_points, rotation),
        _sides,
        _center,
        _color };
}
Object3D Object3D::projectTo2D(float projectionDistance) {
    return Object3D{
        Point::projectTo2D(_points, projectionDistance),
        _sides,
        _center,
        _color };

}

Object3D Object3D::moveCenter(Point oldCenter, Point newCenter)
{
    return Object3D{
        Point::moveCenter(_points, oldCenter, newCenter),
        _sides,
        _center,
        _color   
    };
}

Object3D Object3D::create3DObject(
	SDL_Color color,
	float scale,
	Point actualCenter,
	vector<Point> points,
	const vector<pair<int, int>>& sides)
{
    points = Point::scale(points, {scale, scale, scale});

	return Object3D{ points, sides, actualCenter, color };
}

Object3D Object3D::Cube(float scale, SDL_Color color)
{
    vector<Point> cubeVertices = {
    {-1, -1, -1},
    {+1, -1, -1},
    {+1, +1, -1},
    {-1, +1, -1},
    {-1, -1, +1},
    {+1, -1, +1},
    {+1, +1, +1},
    {-1, +1, +1}
    };
    vector<pair<int, int>> cubeSides =
    {
        {0, 1},{1, 2},{2, 3},{0, 3},
        {4, 5},{5, 6},{6, 7},{4, 7},
        {0, 4},{1, 5},{2, 6},{3, 7}
    };

    return create3DObject(
        color,
        scale,
        {scale/2, scale / 2, scale / 2}, 
        cubeVertices,
        cubeSides);
}

Object3D Object3D::Pyramid(float scale, SDL_Color color)
{
    vector<Point> pyramidVertices = {
    {0, 1, 0},
    {-1, -1, -1},
    {+1, -1, -1},
    {+1, -1, +1},
    {-1, -1, +1}
    };

    vector<pair<int, int>> pyramidSides =
    {
        {1, 2},{2, 3},{3, 4},{1, 4},
        {0, 1},{0, 2}, {0, 3}, {0, 4}
    };
    return create3DObject(
        color,
        scale,
        { scale / 2, scale / 2, scale / 2 },
        pyramidVertices,
        pyramidSides);
}

Object3D Object3D::Square(float scale, SDL_Color color)
{
    vector<Point> squareVertices = {
    {-1, -1, -1},
    {+1, -1, -1},
    {+1, -1, +1},
    {-1, -1, +1}
    };
    vector<pair<int, int>> squareSides =
    {
        {0, 1},{1, 2},{2, 3},{0, 3}
    };
    return create3DObject(
        color,
        scale,
        { scale / 2, scale / 2, scale / 2 },
        squareVertices,
        squareSides);
}

Object3D Object3D::KohStar(const Point& center, const float& radius, const int& vertices, const int& depth, const float& z1, const float& z2, SDL_Color color)
{
    vector<Point> points = generateKoh3DPolygon(center, radius, vertices, depth, z1, z2);
    vector<pair<int, int>> sides = generateLinksFor3DPolygon(points.size()/2);
    return Object3D{
        points, 
        sides, 
        center, 
        color
    };
}
