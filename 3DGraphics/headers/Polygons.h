#pragma once
#include "KochCurve.h"


vector<Point> generateRegularPolygon(
	const Point& center, 
	const float& radius,
	const int& vertices);
vector<Point> enlargeDepth(
	const vector<Point>& polygon,
	const int& depth
);
vector<Point> generateKohPolygon(
	const Point & center,
	const float& radius,
	const int& vertices, 
	const int& depth
);
vector<Point> generateKoh3DPolygon(
	const Point& center,
	const float& radius,
	const int& vertices,
	const int& depth,
	const float& z1,
	const float& z2);
vector<pair<int, int>> generateLinksFor3DPolygon(const int& vertices);


