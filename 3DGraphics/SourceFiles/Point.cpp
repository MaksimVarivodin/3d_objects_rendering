#include "..\headers\Point.h"


Point Point::move(Point movePoint)
{
	return Point(
		x + movePoint.x,
		y + movePoint.y,
		z + movePoint.z);
}

Point Point::rotate(float angleX, float angleY = 0, float angleZ = 0)
{
	Point rotated = rotateX(angleX);
	if (angleY != 0)
		rotated = rotated.rotateY(angleY);
	if (angleY != 0)
		rotated = rotated.rotateZ(angleZ);
	return rotated;
}
Point Point::rotateX(float angle) {
	return Point(
		x,
		cos(angle) * y - sin(angle) * z,
		sin(angle) * y + cos(angle) * z);
}
Point Point::rotateY(float angle) {
	return Point(
		cos(angle) * x + sin(angle) * z,
		y,
		-sin(angle) * x + cos(angle) * z);
}
Point Point::rotateZ(float angle) {
	return Point(
		cos(angle) * x - sin(angle) * y,
		sin(angle) * x + cos(angle) * y,
		z);
}
Point Point::scale(Point scale)
{
	return Point(
		x * scale.x,
		y * scale.y,
		z * scale.z);
}

Point Point::scale(Point oldCenter, Point newCenter, Point scale)
{
	return 
		 moveCenter(oldCenter, newCenter)
		.scale(scale)
		.moveCenter(newCenter, oldCenter);
}

Point Point::projection3DTo2D(float projectionHeight)
{
	return Point(
		(projectionHeight * x) / (projectionHeight + z),
		(projectionHeight * y) / (projectionHeight + z));
}

Point Point::getDifferencePoint(Point point1, Point point2)
{
	return Point(
		point1.x - point2.x,
		point1.y - point2.y,
		point1.z - point2.z);
}

vector<Point> Point::moveCenter(vector<Point> points, Point oldCenter, Point newCenter)
{
	Point difference = getDifferencePoint(newCenter, oldCenter); // 

	for (Point& point :points)	
		point = point.move(difference);

	return points;
}

Point Point::moveCenter(Point oldCenter, Point newCenter)
{
	return move(getDifferencePoint(newCenter, oldCenter));
}




vector<Point> Point::rotate(vector<Point> points, Point oldCenter, Point newCenter, Point angle)
{
	points = moveCenter(points, oldCenter, newCenter);

	points = rotate(points, angle);
	return moveCenter(points, newCenter, oldCenter);
}

vector<Point> Point::rotate(vector<Point> points, Point rotation)
{
	float radianX = rotation.x * M_PI / 180;
	float radianY = rotation.y * M_PI / 180;
	float radianZ = rotation.z * M_PI / 180;
	for (Point& point : points)
		point = point.rotate(radianX, radianY, radianZ);
	return points;
}

vector<Point> Point::scale(vector<Point> points, Point oldCenter, Point newCenter, Point scale)
{
	points  = moveCenter(points, oldCenter, newCenter);

	points = Point::scale(points, scale);

	return moveCenter(points, newCenter, oldCenter);
}

vector<Point> Point::scale(vector<Point> points, Point scale)
{
	for (Point& point: points)
		point = point.scale(scale);

	return points;
}

vector<Point> Point::projectTo2D(vector<Point> points, float distance)
{
	for (Point& point : points) {
		point = point.projection3DTo2D(distance);
	}
	return points;
}
