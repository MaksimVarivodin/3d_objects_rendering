#include "mesh.h"


vector<VertexArray> mesh::to_triangle_vertex_array(const Color& color)
{
	vector<VertexArray> result(trians_.size());
	
	for (size_t i = 0 ; i < trians_.size(); i++)
		result[i] = trians_[i].to_triangle_vertex_array(points_, color);

	return result;
}

vector<VertexArray> mesh::to_line_vertex_array(const Color& color)
{
	vector<VertexArray> result(trians_.size());
	
	for (size_t i = 0 ; i < trians_.size(); i++)
		result[i] = trians_[i].to_line_vertex_array(points_, color);

	return result;
}

mesh& mesh::rotate_x(const float& degrees)
{
	const float radian = em_angle_to_radian(degrees);

	points_ = em_rotate_x(points_, radian);

	return *this;
}

mesh& mesh::rotate_y(const float& degrees)
{
	const float radian = em_angle_to_radian(degrees);

	points_ = em_rotate_y(points_, radian);

	return *this;
}

mesh& mesh::rotate_z(const float& degrees)
{
	const float radian = em_angle_to_radian(degrees);

	points_ = em_rotate_z(points_, radian);

	return *this;
}

mesh& mesh::move(const Vector3f& move_point)
{
	points_ = em_move(move_point, points_);

	return *this;
}

mesh& mesh::scale(const Vector3f& scale_point)
{
	points_ = em_scale(points_, scale_point);

	return *this;
}

mesh& mesh::set_precision(const int& precision)
{
	points_= em_precision(points_, precision);

	return *this;
}
