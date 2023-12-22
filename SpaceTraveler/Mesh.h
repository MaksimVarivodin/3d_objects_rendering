#pragma once
#include "triangle.h"
class mesh
{

private:
	vector<Vector3f> points_;
	vector<triangle> trians_;
public:
	vector<Vector3f> get_points()const { return points_; }
	vector<triangle> get_triangles()const {return trians_; }
	vector<VertexArray> to_triangle_vertex_array() const;
	vector<VertexArray> to_line_vertex_array() const;
	vector<Vector3f> normals_to_triangles() const;
	vector<Vector3f> distances_to_point(const Vector3f & point) const;


	mesh& rotate_x(const float & degrees);
	mesh& rotate_y(const float & degrees);
	mesh& rotate_z(const float & degrees);
	mesh& move(const Vector3f& move_point);
	mesh& scale(const Vector3f& scale_point);
	mesh& sort_triangles();

	mesh& set_precision(const int& precision);
	size_t count() const {return trians_.size();}
	
	mesh() :points_(), trians_() {}

	mesh(const vector<Vector3f>& p,  const vector<triangle>& tr)
	{
		points_ = p;
		trians_ = tr;
	}
	mesh(const mesh& other) = default;
	mesh(mesh&& other) noexcept = default;
	mesh& operator=(const mesh& other) = default;
	mesh& operator=(mesh&& other) noexcept = default;
};

