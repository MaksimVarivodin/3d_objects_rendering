#include "triangle.h"

const VertexArray& triangle::to_line_vertex_array(const vector<point> points) const
{
	VertexArray result (LinesStrip, 4);

	result[0].position = points[a()].to_Vector2f();
	result[1].position = points[b()].to_Vector2f();
	result[2].position = points[c()].to_Vector2f();
	result[0].position = points[a()].to_Vector2f();

	result[0].color = outline_;
	result[1].color = outline_;
	result[2].color = outline_;
	result[0].color = outline_;
	return result;
}
