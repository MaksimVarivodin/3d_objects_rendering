#pragma once
#include "Object3D.h"
class Render3D
{
	// ������ �������� 3D
	vector<Object3D> objects;
	// ���������� �� ������
	float projectionDistance{};
	// ������ ���������
	vector<Point> objectRotations;
	// ������ ��������� ���������
	vector<Point> rotationDeltas;
	// ������ ������� �������� �� ������
	vector<Point> objectPositions;
	// �������� (�� ���������� SDL)
	SDL_Renderer* _renderer{};

	// �������� ���� ��������
	void addDeltas(int index);
	// ������������ ���� ������ �� �����
	Object3D calculateObject3DTo2D(Object3D object, int index);
	// ���������� ���� ������ �� �����
	void drawObject(Object3D someObject);
public:

	
	Render3D();


    ~Render3D();
	/*
		��������� ������ ������� (��������):
			- ������������� �� ����� 
			- ��������� �� ������
	*/
	void renderObject(Object3D someObject, int index);
	/*
		��������� ���� �������� ������
	*/
    void renderObjects();

	Render3D(
		const vector<Object3D>& objects,
		float projectionDistance, 
		const vector<Point>& objectRotations,
		const vector<Point>& rotationDeltas,
		const vector<Point>& objectPositions,
		SDL_Renderer* _renderer);
};

