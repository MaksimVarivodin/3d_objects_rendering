#include "Render3D.h"

void Render3D::render(Object3D someObject)
{
	
	vector<Point> points = Point::rotate(
		someObject.points(),
		cameraTarget,
		someObject.center(),
		angle.x,
		angle.y,
		angle.z);

	for (size_t i = 0; i < points.size(); i++)
		points[i] = points[i].projection3DTo2D(projectionDistance);

	SDL_SetRenderDrawColor(
		_renderer,
		someObject.color().r,
		someObject.color().g,
		someObject.color().b,
		someObject.color().a);

	for (pair<int, int> side : someObject.sides()) {
		SDL_RenderDrawLine(
			_renderer, 
			points[side.first].x,
			points[side.first].y,
			points[side.second].x,
			points[side.second].y);
	}
	SDL_RenderPresent(_renderer);
}
