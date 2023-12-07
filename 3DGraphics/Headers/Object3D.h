#pragma once
#include "Point.h"

// ����� 3� ������
class Object3D
{	
	// ����� �������
	vector<Point> _points;
	// ������� �������(���� �������� � ������� �����)
	vector<pair<int, int>> _sides;
	// ����������� ����� ������
	Point _center;
	// ���� ������� ������ ������
	SDL_Color _color{};

public:
	// ���� ������� ������ ������
	SDL_Color color() { return _color; };
	// ����� �������
	vector<Point> points() { return _points; };
	// ������� �������
	vector<pair<int, int>> sides() { return _sides; };
	// �����
	Point center() { return _center; };
	
	// ��������� ������
	Object3D rotate(Point rotation);
	// ������������ �� �����
	Object3D projectTo2D(float projectionDistance);
	// ����������� �����
	Object3D moveCenter(Point oldCenter, Point newCenter);

	// ������� ������
	static Object3D create3DObject(
		SDL_Color color,
		float scale,
		Point actualCenter,
		vector<Point> points,
		const vector<pair<int, int>>& sides);
	// ��������� ���
	static Object3D Cube(float scale, SDL_Color color);
	// ��������� ��������
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

