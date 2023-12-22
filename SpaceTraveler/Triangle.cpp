#include "triangle.h"


VertexArray triangle::to_triangle_vertex_array(const vector<Vector3f>& points) const
{
	VertexArray array (Triangles, 3);
	array[0] = Vertex({points[a()].x, points[a()].y}, fill_);
	array[1] = Vertex({points[b()].x, points[b()].y}, fill_);
	array[2] = Vertex({points[c()].x, points[c()].y}, fill_);
	return array;
}

VertexArray triangle::to_line_vertex_array(const vector<Vector3f>& points) const
{
	VertexArray array (LineStrip, 4);
	array[0] = Vertex({points[a()].x, points[a()].y}, outline_);
	array[1] = Vertex({points[b()].x, points[b()].y}, outline_);
	array[2] = Vertex({points[c()].x, points[c()].y}, outline_);
	array[3] = Vertex({points[a()].x, points[a()].y}, outline_);
	return array;
}
