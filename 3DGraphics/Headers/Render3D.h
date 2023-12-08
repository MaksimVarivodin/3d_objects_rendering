#pragma once
#include "Object3D.h"
class Render3D
{
	// массив объектов 3D
	vector<Object3D> objects;
	// расстояние до экрана
	float projectionDistance{};
	// массив поворотов
	vector<Point> objectRotations;
	// массив изменения поворотов
	vector<Point> rotationDeltas;
	// массив позиций объектов на екране
	vector<Point> objectPositions;
	// рендерер (из библиотеки SDL)
	SDL_Renderer* _renderer{};

	// добавить угол поворота
	void addDeltas(int index);
	// проецировать один объект на екран
	Object3D calculateObject3DTo2D(Object3D object, int index);

	thread projectionInThread(const Object3D& object, int index, promise<bool>& done);
	// нарисовать один объект на екран
	void drawObject(Object3D someObject);

	vector<thread*> threads;

	Object3D doWork(Object3D someobject, int index);

public:

	
	Render3D();


    ~Render3D();
	/*
		рендеринг всех объектов класса
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

