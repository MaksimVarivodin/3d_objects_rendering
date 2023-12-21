#pragma once
#include "triangle.h"
class mesh
{
public:
	mesh(const mesh& other) = default;
	mesh(mesh&& other) noexcept = default;
	mesh& operator=(const mesh& other) = default;
	mesh& operator=(mesh&& other) noexcept = default;

private:
	vector<Vector3f> points_;
	vector<triangle> trians_;
public:
	vector<Vector3f> get_points()const { return points_; }
	vector<triangle> get_triangles()const {return trians_; }
	vector<VertexArray> to_triangle_vertex_array(const Color& color);
	vector<VertexArray> to_line_vertex_array(const Color& color);
	mesh& rotate_x(const float & degrees);
	mesh& rotate_y(const float & degrees);
	mesh& rotate_z(const float & degrees);
	mesh& move(const Vector3f& move_point);
	mesh& scale(const Vector3f& scale_point);

	mesh& set_precision(const int& precision);
	size_t count() const {return trians_.size();}
	
	mesh() :points_(), trians_() {}

	mesh(const vector<Vector3f>& p,  const vector<triangle>& tr)
	{
		points_ = p;
		trians_ = tr;
	}
};

