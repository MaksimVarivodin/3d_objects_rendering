#pragma once
#include"Header.h"
// класс точка(вектор)
class Point {

public:
	// координата х 
	float x;
	// координата y
	float y;
	// координата z
	float z;
	
	// метод сдвига точки относительно заданного центра
	Point moveCenter(Point oldCenter, Point newCenter);
	// метод сдвига точки на переданный вектор
	Point move(Point movePoint);
	// метод поворота точки
	Point rotate(float angleX, float angleY, float angleZ);
	// метод поворота точки по оси X
	Point rotateX(float angle);
	// метод поворота точки по оси Y
	Point rotateY(float angle);
	// метод поворота точки по оси Z
	Point rotateZ(float angle);

	// метод масштабирования
	Point scale(Point scale);
	// метод масштабирования с учетом центра объекта
	Point scale(Point oldCenter, Point newCenter, Point scale);
	// метод проекции объекта на плоскость экрана
	Point projection3DTo2D(float distanceToScreen);

	// метод получения разницы между двумя точками
	static Point getDifferencePoint(Point point1, Point point2);
	// метод сдвига массива точек относительно старого и нового центра
	static vector<Point> moveCenter(vector<Point> points, Point oldCenter, Point newCenter);

	// метод поворота массива точек относительно старого и нового центра
	static vector<Point> rotate(vector<Point> points, Point oldCenter, Point newCenter, Point angle);
	// метод поворота массива точек относительно центра координат
	static vector<Point> rotate(vector<Point> points, Point rotation);

	// метод масштабирования массива точек относительно старого и нового центра
 	static vector<Point> scale(vector<Point> points, Point oldCenter, Point newCenter, Point scale);
	// метод масштабирования массива точек
	static vector<Point> scale(vector<Point> points, Point scale);

	// метод проекции массива точек на плоскость экрана
	static vector<Point> projectTo2D(vector<Point> points, float distance);
	
	Point(float x, float y, float z) : x(x), y(y), z(z) {}
	Point(float x, float y) : Point(x, y, 0) {};
	Point(float x) : Point(x, 0) {};
	Point() :Point(0, 0, 0) {};
	
};
