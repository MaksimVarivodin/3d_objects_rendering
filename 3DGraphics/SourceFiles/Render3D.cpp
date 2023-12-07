#include "..\headers\Render3D.h"

void Render3D::renderObject(Object3D someObject, int index)
{
	someObject = calculateObject3DTo2D(someObject, index);
	drawObject(someObject);
	
}

void Render3D::renderObjects() {
	int index = 0;
	for (const Object3D& obj : objects) {
		renderObject(obj, index);
		index++;
	}
	SDL_RenderPresent(_renderer);
};

Render3D::~Render3D() = default;

void Render3D::addDeltas(int index)
{
	objectRotations[index].x += objectRotations[index].x > 360? -360: 0 + rotationDeltas[index].x;
	objectRotations[index].y += objectRotations[index].y > 360? -360: 0 + rotationDeltas[index].y;
	objectRotations[index].z += objectRotations[index].z > 360? -360: 0 + rotationDeltas[index].z;
}

Object3D Render3D::calculateObject3DTo2D(Object3D object, int index)
{
	object = object.rotate(objectRotations[index]);

	object = object.projectTo2D(projectionDistance);

	object = object.moveCenter(object.center(), objectPositions[index]);

	addDeltas(index); 

	return object;
}

void Render3D::drawObject(Object3D someObject)
{
	SDL_SetRenderDrawColor(
		_renderer,
		someObject.color().r,
		someObject.color().g,
		someObject.color().b,
		someObject.color().a);

	for (pair<int, int> side : someObject.sides()) {
		SDL_RenderDrawLine(
			_renderer,
			(int)someObject.points()[side.first].x,
			(int)someObject.points()[side.first].y,
			(int)someObject.points()[side.second].x,
			(int)someObject.points()[side.second].y);
	}
}

Render3D::Render3D() = default;

Render3D::Render3D(const vector<Object3D>& objects, float projectionDistance, const vector<Point>& objectRotations, const vector<Point>& rotationDeltas, const vector<Point>& objectPositions, SDL_Renderer* _renderer)
	: objects(objects), projectionDistance(projectionDistance), objectRotations(objectRotations), rotationDeltas(rotationDeltas), objectPositions(objectPositions), _renderer(_renderer)
{
	if (objects.size() != objectRotations.size() && objects.size() != objectPositions.size() && objects.size() != rotationDeltas.size())
		throw invalid_argument("objects length and rotations and positions and deltas not equal");
}
