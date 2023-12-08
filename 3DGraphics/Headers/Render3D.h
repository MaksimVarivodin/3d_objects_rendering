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

	thread projectionInThread(const Object3D& object, int index, promise<bool>& done);
	// ���������� ���� ������ �� �����
	void drawObject(Object3D someObject);

	vector<thread*> threads;

	Object3D doWork(Object3D someobject, int index);

public:

	
	Render3D();


    ~Render3D();
	/*
		��������� ���� �������� ������
	*/
    void renderObjects();
	void runThreads();
	Render3D(
		const vector<Object3D>& objects,
		float projectionDistance, 
		const vector<Point>& objectRotations,
		const vector<Point>& rotationDeltas,
		const vector<Point>& objectPositions,
		SDL_Renderer* _renderer);
};

