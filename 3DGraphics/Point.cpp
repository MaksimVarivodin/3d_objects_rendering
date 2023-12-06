#include "Point.h"

Point Point::operator*(Matrix matrix)
{
	Matrix point = pointToMatrix(*this);
	Matrix result = matrix * point; // 3x3 * 3x1 = 3x1
	return matrixToPoint(result);
}

Point& Point::operator*=(const Matrix& other)
{
	// TODO: вставьте здесь оператор return
	(*this) = (*this) * other;
	return *this;
}

Point Point::move(Point movePoint)
{
	return Point(
		x + movePoint.x,
		y + movePoint.y,
		z + movePoint.z);
}

Point Point::rotate(float angleX, float angleY = 0, float angleZ = 0)
{
	Point newPoint = (*this) * Matrix::createRotationX(angleX);
	if (angleY!= 0)
		newPoint *= Matrix::createRotationY(angleY);
	if (angleZ != 0)
		newPoint *= Matrix::createRotationZ(angleZ);
	return Point();
}

Point Point::scale(float scaleX, float scaleY, float scaleZ)
{
	return Point(
		x * scaleX,
		y * scaleY,
		z * scaleZ);
}

Point Point::scale(Point oldCenter, Point newCenter, float scaleX, float scaleY, float scaleZ)
{
	return 
		 moveCenter(oldCenter, newCenter)
		.scale(scaleX, scaleY, scaleZ)
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

	for (size_t i = 0; i < points.size(); i++)	
		points[i] = points[i].move(difference);

	return vector<Point>();
}

Point Point::moveCenter(Point oldCenter, Point newCenter)
{
	return move(getDifferencePoint(newCenter, oldCenter));
}


Matrix Point::pointToMatrix(const Point& point)
{
	vector<vector<float>> v = {
		{point.x},
		{point.y},
		{point.z}
	};
    return Matrix(v);
}

Point Point::matrixToPoint(Matrix matrix)
{
	if ((matrix.columns() != 1 && matrix.rows()!= 1) || (matrix.rows() !=3 && matrix.columns() !=3)) 
		throw invalid_argument("Matrix must be 1x3 or 3x1");

	if (matrix.columns() == 1) {
		return Point(matrix.data()[0][0], matrix.data()[1][0], matrix.data()[2][0]);
	}

	if (matrix.rows() == 1) {
		return Point(matrix.data()[0][0], matrix.data()[0][1], matrix.data()[0][2]);
	}
	return Point();
}

vector<Point> Point::rotate(vector<Point> points, Point oldCenter, Point newCenter, float angleX, float angleY, float angleZ)
{
	points = moveCenter(points, oldCenter, newCenter);
	points = rotate(points, angleX, angleY, angleZ);
	return moveCenter(points, newCenter, oldCenter);
}

vector<Point> Point::rotate(vector<Point> points, float angleX, float angleY, float angleZ)
{
	for (size_t i = 0; i < points.size(); i++)
		points[i] = points[i].rotate(angleX, angleY, angleZ);
	return points;
}

vector<Point> Point::scale(vector<Point> points, Point oldCenter, Point newCenter, float scaleX, float scaleY, float scaleZ)
{
	points  = moveCenter(points, oldCenter, newCenter);

	points = scale(points, scaleX, scaleY, scaleZ);

	return moveCenter(points, newCenter, oldCenter);
}

vector<Point> Point::scale(vector<Point> points, float scaleX, float scaleY, float scaleZ)
{
	for (size_t i = 0; i < points.size(); i++)
		points[i] = points[i].scale(scaleX, scaleY, scaleZ);

	return points;
}
