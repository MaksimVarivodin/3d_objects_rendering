#include "..\headers\Render3D.h"

mutex mtx;


void Render3D::renderObjects() {
	int index = 0;
	for (Object3D& obj : objects) {
		drawObject(calculateObject3DTo2D(obj, index));
		index++;
	}
	
	SDL_RenderPresent(_renderer);

};

Render3D::~Render3D() = default;

void Render3D::addDeltas(int index)
{
	mtx.lock();
	objectRotations[index].x += objectRotations[index].x > 360? -360: 0 + rotationDeltas[index].x;
	objectRotations[index].y += objectRotations[index].y > 360? -360: 0 + rotationDeltas[index].y;
	objectRotations[index].z += objectRotations[index].z > 360? -360: 0 + rotationDeltas[index].z;
	mtx.unlock();
}

Object3D Render3D::calculateObject3DTo2D(Object3D object, int index)
{
	mtx.lock();
	Point rotations = objectRotations[index];
	float distance = projectionDistance;
	Point position = objectPositions[index];
	mtx.unlock();
	object = object.rotate(rotations);

	object = object.projectTo2D(distance);

	object = object.moveCenter(object.center(), position);

	addDeltas(index); 

	return object;
}

thread Render3D::projectionInThread(const Object3D& object, int index, promise<bool> &done)
{
	return  thread([&]() {
		drawObject(calculateObject3DTo2D(object, index));
		//lock_guard<mutex> guard(mtx);
		done.set_value(true);
		});
}

void Render3D::drawObject(Object3D someObject)
{
	{
		SDL_SetRenderDrawColor(
			_renderer,
			someObject.color().r,
			someObject.color().g,
			someObject.color().b,
			someObject.color().a);
		mtx.lock();
		for (const pair<int, int>& side : someObject.sides()) {
			
			SDL_RenderDrawLine(
				_renderer,
				(int)someObject.points()[side.first].x,
				(int)someObject.points()[side.first].y,
				(int)someObject.points()[side.second].x,
				(int)someObject.points()[side.second].y);
		}
		mtx.unlock();
	}
}

void Render3D::runThreads()
{
	vector<thread> threads;
	vector<Object3D> newObjects(objects);
	for (int i = 0; i < objects.size(); i++) { 
		threads.push_back(
			thread([&newObjects, i, this]() {
				mtx.lock();
				Object3D buffer = newObjects[i];
				mtx.unlock();

				drawObject(doWork(buffer, i));				
				}));
	}	

	for (auto& t : threads) {
		if (t.joinable()) {
			t.join();
		}
	}

	SDL_RenderPresent(_renderer);
}

Object3D Render3D::doWork(Object3D someobject, int index)
{
	return calculateObject3DTo2D(someobject, index);
}

Render3D::Render3D() = default;

Render3D::Render3D(const vector<Object3D>& objects, float projectionDistance, const vector<Point>& objectRotations, const vector<Point>& rotationDeltas, const vector<Point>& objectPositions, SDL_Renderer* _renderer)
	: objects(objects), projectionDistance(projectionDistance), objectRotations(objectRotations), rotationDeltas(rotationDeltas), objectPositions(objectPositions), _renderer(_renderer)
{
	if (objects.size() != objectRotations.size() && objects.size() != objectPositions.size() && objects.size() != rotationDeltas.size())
		throw invalid_argument("objects length and rotations and positions and deltas not equal");
}
