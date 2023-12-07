#pragma once
#include "Point.h"

// класс 3Д объект
class Object3D
{	
	// точки объекта
	vector<Point> _points;
	// стороны объекта(пары индексов в массиве точек)
	vector<pair<int, int>> _sides;
	// фактический центр фигуры
	Point _center;
	// цвет которым рисуют фигуру
	SDL_Color _color{};

public:
	// цвет которым рисуют фигуру
	SDL_Color color() { return _color; };
	// точки объекта
	vector<Point> points() { return _points; };
	// стороны объекта
	vector<pair<int, int>> sides() { return _sides; };
	// центр
	Point center() { return _center; };
	
	// повернуть фигуру
	Object3D rotate(Point rotation);
	// проэцировать на екран
	Object3D projectTo2D(float projectionDistance);
	// переместить центр
	Object3D moveCenter(Point oldCenter, Point newCenter);

	// создать объект
	static Object3D create3DObject(
		SDL_Color color,
		float scale,
		Point actualCenter,
		vector<Point> points,
		const vector<pair<int, int>>& sides);
	// построить куб
	static Object3D Cube(float scale, SDL_Color color);
	// построить пирамиду
	static Object3D Pyramid(float scale, SDL_Color color);

	Object3D() = default;

	~Object3D() = default;

	Object3D(
		const vector<Point>& _points,
		const vector<pair<int, int>>& sides,
		const Point& _center,
		const SDL_Color& _color)
		: _points(_points),
		_sides(sides),
		_center(_center),
		_color(_color)
	{
	};
};

