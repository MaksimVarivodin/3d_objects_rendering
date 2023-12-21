#include "mesh.h"


vector<VertexArray> mesh::to_triangle_vertex_array(const Color& color) const
{
	vector<VertexArray> result(trians_.size());

	for (size_t i = 0 ; i < trians_.size(); i++)
			result[i] = (trians_[i].to_triangle_vertex_array(points_, color));

	return result;
}

vector<VertexArray> mesh::to_line_vertex_array(const Color& color) const
{
	vector<VertexArray> result(trians_.size());

	for (size_t i = 0 ; i < trians_.size(); i++)
		result[i] = (trians_[i].to_line_vertex_array(points_, color));

	return result;
}

vector<Vector3f> mesh::normals_to_triangles() const
{
	vector<Vector3f> vectors(trians_.size());
	Vector3f	vec_a,
				vec_b,
				normal;

	for(int i = 0; i < trians_.size(); i++)
	{
		vec_a= em_find_vector_point(points_[trians_[i].a()], points_[trians_[i].b()]);
		vec_b = em_find_vector_point(points_[trians_[i].a()], points_[trians_[i].c()]);
		normal = em_cross_product_point(vec_a, vec_b);
		vectors[i] = em_cross_product_normalization(normal);
	}
	return vectors;
}

vector<Vector3f> mesh::distances_to_point(const Vector3f& point) const
{
	vector<Vector3f> distances(trians_.size());

	for (size_t i = 0; i< trians_.size(); i++)
		distances[i] = {
		points_[trians_[i].a()].x - point.x,
		points_[trians_[i].a()].y - point.y,
		points_[trians_[i].a()].z - point.z
		};

	return distances;
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
