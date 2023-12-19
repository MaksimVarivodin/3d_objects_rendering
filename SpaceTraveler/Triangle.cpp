#include "triangle.h"

ConvexShape triangle::to_convex_shape(const vector<Vector3f>& points) const
{
	ConvexShape tr;
	tr.setPointCount(3);

	tr.setPoint(0, Vector2f(points[a()].x, points[a()].y));
	tr.setPoint(1, Vector2f(points[b()].x, points[b()].y));
	tr.setPoint(2, Vector2f(points[c()].x, points[c()].y));
	return tr;
}

ConvexShape triangle::to_convex_shape(const vector<Vector2f>& points) const
{
	ConvexShape tr(3);

	tr.setPoint(0, points[a()]);
	tr.setPoint(1, points[b()]);
	tr.setPoint(2, points[c()]);
	return tr;
}
