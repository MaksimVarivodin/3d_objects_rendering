#pragma once
#include "Object3D.h"
class Render3D
{
	vector<Object3D> objects;
	float projectionDistance;
	Point angle;
	Point cameraTarget;
	SDL_Renderer* _renderer;

public:

	
	Render3D();
	~Render3D();
	void render(Object3D someObject);
};

