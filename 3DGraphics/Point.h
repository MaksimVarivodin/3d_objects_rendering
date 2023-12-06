#pragma once
#include"Matrix.h"
class Point {
public:
	float x;
	float y;
	float z;
	
	Point operator*(Matrix matrix);	
	Point& operator*= (const Matrix& other);
	Point moveCenter(Point oldCenter, Point newCenter);
	Point move(Point movePoint);
	Point rotate(float angleX, float angleY, float angleZ);
	Point scale(float scaleX, float scaleY, float scaleZ);
	Point scale(Point oldCenter, Point newCenter, float scaleX, float scaleY, float scaleZ);
	Point projection3DTo2D(float distanceToScreen);
	static Matrix pointToMatrix(const Point& point);
	static Point matrixToPoint(Matrix matrix);

	static Point getDifferencePoint(Point point1, Point point2);
	static vector<Point> moveCenter(vector<Point> points, Point oldCenter, Point newCenter);


	static vector<Point> rotate(vector<Point> points, Point oldCenter, Point newCenter, float angleX, float angleY = 0, float angleZ = 0);
	static vector<Point> rotate(vector<Point> points, float angleX, float angleY, float angleZ);
 	static vector<Point> scale(vector<Point> points, Point oldCenter, Point newCenter, float scaleX, float scaleY, float scaleZ);
	static vector<Point> scale(vector<Point> points, float scaleX, float scaleY, float scaleZ);
	Point(float x, float y, float z) : x(x), y(y), z(z) {}
	Point(float x, float y) : Point(x, y, 0) {};
	Point(float x) : Point(x, 0) {};
	Point() :Point(0, 0, 0) {};
	
};
