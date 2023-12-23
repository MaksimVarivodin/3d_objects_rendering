#pragma once
#include "triangle.h"
class mesh
{

	vector<point> points_;
	vector<triangle> trians_;
public:
	vector<point> get_points()const { return points_; }
	vector<triangle> get_triangles()const {return trians_; }
	VertexArray to_triangle_vertex_array() const;
	vector<VertexArray> to_line_vertex_array() const;
	vector<point> normals_to_triangles() const;
	vector<point> distances_to_point(const point & p) const;

	mesh& sort_triangles();

	size_t count() const {return trians_.size();}
	
	mesh() :points_(), trians_() {}

	mesh(const vector<point>& p,  const vector<triangle>& tr)
	{
		points_ = p;
		trians_ = tr;
	}
	mesh(const mesh& other) = default;
	mesh(mesh&& other) noexcept = default;
	mesh& operator=(const mesh& other) = default;
	mesh& operator=(mesh&& other) noexcept = default;
};

