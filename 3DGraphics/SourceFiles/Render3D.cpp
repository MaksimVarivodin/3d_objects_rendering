#include "Headers/Render3D.h"

void Render3D::render(Object3D someObject)
{
	
	vector<Point> points = Point::rotate(
		someObject.points(),
		cameraTarget,
		someObject.center(),
		angle.x,
		angle.y,
		angle.z);

	for (auto & point : points)
		point = point.projection3DTo2D(projectionDistance);

	SDL_SetRenderDrawColor(
		_renderer,
		someObject.color().r,
		someObject.color().g,
		someObject.color().b,
		someObject.color().a);

	for (pair<int, int> side : someObject.sides()) {
		SDL_RenderDrawLine(
			_renderer,
            (int)points[side.first].x,
			(int)points[side.first].y,
			(int)points[side.second].x,
			(int)points[side.second].y);
	}
	SDL_RenderPresent(_renderer);
}

Render3D::Render3D(const vector<Object3D> &objects,
                   float projectionDistance,
                   const Point &angle,
                   const Point &cameraTarget,
                   SDL_Renderer *renderer) : objects(objects),
                   projectionDistance(projectionDistance),
                   angle(angle),
                   cameraTarget(cameraTarget),
                   _renderer(renderer)
                   {}

void Render3D::render() {
    for(const Object3D& obj: objects)
        render(obj);

};

Render3D::~Render3D() = default;

Render3D::Render3D() = default;
