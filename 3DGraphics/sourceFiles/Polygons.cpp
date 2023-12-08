#include "..\headers\Polygons.h"

vector<Point> generateRegularPolygon(const Point& center, const float& radius, const int& vertices)
{
	vector<Point> points = vector<Point>(vertices); // Create an empty vector of Point obj
	float radian = 2 * M_PI / (float)vertices;
	for (size_t i = 0; i < vertices; i++)
	{
		float x = center.x + (radius * cos(i * radian) );
		float y = center.y + (radius * sin(i * radian) );
		points[i] = Point(x, y);
	}
	return points;

}

vector<Point> enlargeDepth(const vector<Point>& polygon, const int& depth)
{
	list<Point> kochVerticesList = list<Point>();
	int size = polygon.size() -1;

	for (int i = 0; i < size; i++)
		kochVerticesList.append_range(KochCurve::encreaseDepth(polygon[i], polygon[i + 1], depth));

	kochVerticesList.append_range(KochCurve::encreaseDepth(polygon[size], polygon[0], depth));

	return vector<Point>(kochVerticesList.begin(), kochVerticesList.end());
}

vector<Point> generateKohPolygon(const Point& center, const float& radius, const int& vertices, const int& depth)
{
	vector<Point> polygon = generateRegularPolygon(center, radius, vertices);
	return enlargeDepth(polygon, depth);	
}

vector<Point> generateKoh3DPolygon(const Point& center, const float& radius, const int& vertices, const int& depth, const float& z1, const float& z2)
{
	vector<Point> polygon = generateKohPolygon(center, radius, vertices, depth);
	vector < Point> polygon3D = vector<Point>(polygon.size() * 2);
	for (size_t i = 0; i < polygon.size(); i++)
	{
		polygon3D[i] = Point(polygon[i].x, polygon[i].y, z1);
		polygon3D[i + polygon.size()] = Point(polygon[i].x, polygon[i].y, z2);
	}
	return polygon3D;
}
vector<pair<int, int>> generateLinksFor3DPolygon(const int& vertices) {
	vector<pair<int, int>> sides = vector<pair<int, int>>(vertices*3);
	for (size_t i = 0; i < vertices-1; i++)
	{
		sides[i] = {i, i+1};
		sides[i + vertices] = { i + vertices, i + vertices + 1 };
		sides[i + vertices * 2] = {i, i+ vertices};
	}
	sides[vertices - 1] = { vertices - 1, 0 };
	sides[vertices * 2 - 1] = {2* vertices - 1, vertices };
	sides[vertices - 1 + (vertices) * 2] = { vertices - 1,2 * vertices - 1 };
	return sides;
}
