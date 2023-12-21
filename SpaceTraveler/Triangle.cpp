#include "triangle.h"


VertexArray triangle::to_triangle_vertex_array(const vector<Vector3f>& points, const Color& fill_color) const
{
	VertexArray array (Triangles, 3);
	array[0] = Vertex({points[a()].x, points[a()].y}, fill_color);
	array[1] = Vertex({points[b()].x, points[b()].y}, fill_color);
	array[2] = Vertex({points[c()].x, points[c()].y}, fill_color);
	return array;
}

VertexArray triangle::to_line_vertex_array(const vector<Vector3f>& points, const Color& outline_color) const
{
	VertexArray array (LineStrip, 4);
	array[0] = Vertex({points[a()].x, points[a()].y}, outline_color);
	array[1] = Vertex({points[b()].x, points[b()].y}, outline_color);
	array[2] = Vertex({points[c()].x, points[c()].y}, outline_color);
	array[3] = Vertex({points[a()].x, points[a()].y}, outline_color);
	return array;
}
