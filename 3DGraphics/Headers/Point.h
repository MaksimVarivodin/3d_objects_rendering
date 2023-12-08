#pragma once
#include"Header.h"
// ����� �����(������)
class Point {

public:
	// ���������� � 
	float x;
	// ���������� y
	float y;
	// ���������� z
	float z;
	
	// ����� ������ ����� ������������ ��������� ������
	Point moveCenter(Point oldCenter, Point newCenter);
	// ����� ������ ����� �� ���������� ������
	Point move(Point movePoint);
	// ����� �������� �����
	Point rotate(float angleX, float angleY, float angleZ);
	// ����� �������� ����� �� ��� X
	Point rotateX(float angle);
	// ����� �������� ����� �� ��� Y
	Point rotateY(float angle);
	// ����� �������� ����� �� ��� Z
	Point rotateZ(float angle);

	// ����� ���������������
	Point scale(Point scale);
	// ����� ��������������� � ������ ������ �������
	Point scale(Point oldCenter, Point newCenter, Point scale);
	// ����� �������� ������� �� ��������� ������
	Point projection3DTo2D(float distanceToScreen);

	// ����� ��������� ������� ����� ����� �������
	static Point getDifferencePoint(Point point1, Point point2);
	// ����� ������ ������� ����� ������������ ������� � ������ ������
	static vector<Point> moveCenter(vector<Point> points, Point oldCenter, Point newCenter);

	// ����� �������� ������� ����� ������������ ������� � ������ ������
	static vector<Point> rotate(vector<Point> points, Point oldCenter, Point newCenter, Point angle);
	// ����� �������� ������� ����� ������������ ������ ���������
	static vector<Point> rotate(vector<Point> points, Point rotation);

	// ����� ��������������� ������� ����� ������������ ������� � ������ ������
 	static vector<Point> scale(vector<Point> points, Point oldCenter, Point newCenter, Point scale);
	// ����� ��������������� ������� �����
	static vector<Point> scale(vector<Point> points, Point scale);

	// ����� �������� ������� ����� �� ��������� ������
	static vector<Point> projectTo2D(vector<Point> points, float distance);
	
	Point(float x, float y, float z) : x(x), y(y), z(z) {}
	Point(float x, float y) : Point(x, y, 0) {};
	Point(float x) : Point(x, 0) {};
	Point() :Point(0, 0, 0) {};
	
};
