#pragma once
#include "Point.h"


class Object3D
{
	vector<Point> _points;
	vector<pair<int, int>> _sides;
	Point _center;
	SDL_Color _color;

public:
	
	SDL_Color color() { return _color; };
	vector<Point> points() { return _points; };
	vector<pair<int, int>> sides() { return _sides; };
	Point center() { return _center; };
	
	Object3D() = default;

	~Object3D() {};

	Object3D(
		const vector<Point>& _points,
		const vector<pair<int, int>>& sides,
		const Point& center,
		const SDL_Color& _color)
		: _points(_points),
		_sides(sides),
		_center(_center),
		_color(_color)
	{
	};

	static Object3D create3DObject(
		SDL_Color color,
		Point screenCenter,
		Point actualCenter,
		vector<Point> points,
		vector<pair<int, int>> sides);
};

