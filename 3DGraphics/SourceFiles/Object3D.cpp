#include "Headers/Object3D.h"

Object3D Object3D::create3DObject(
	SDL_Color color,
	Point screenCenter, 
	Point actualCenter,
	vector<Point> points,
	const vector<pair<int, int>>& sides)
{
	points = Point::scale(points, 100, 100, 100);
	points = Point::moveCenter(points, Point(0, 0), screenCenter);

	return Object3D{ points, sides, actualCenter, color };
}
