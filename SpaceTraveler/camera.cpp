#include "camera.h"

camera& camera::operator=(const camera& other)
{
	this->z_compression_ = other.z_compression_;
	this->field_of_view_ = other.field_of_view_;
	this->z_to_monitor_ = other.z_to_monitor_;
	this->asp_ratio_ = other.asp_ratio_;
	return *this;
}

mesh camera::projection_method(const mesh& m) const
{
	int iterator = 0;
	const vector<Vector3f> points = m.get_points();
	vector<Vector3f> result(points.size());
	for (const Vector3f & p: points)
	{		
		result[iterator] = em_project_function(
			asp_ratio_,
			field_of_view_,
			z_compression_,
			z_to_monitor_, p).to_vector3();
		iterator++;
	}			
	return mesh(result, m.get_triangles());
}

mesh camera::filter_by_normals(const mesh& m) const
{
	const vector<Vector3f> line_to_triangle = m.distances_to_point(camera_location);

	const vector<Vector3f> normals = m.normals_to_triangles();

	const vector<triangle> source_triangles = m.get_triangles();

	vector<triangle> filtered_triangles;

	filtered_triangles.reserve(normals.size());

	for (size_t i = 0; i< normals.size(); i++)	
		if (em_dot_product_point(normals[i], line_to_triangle[i]) < 0)
			filtered_triangles.push_back(source_triangles[i]);

	return mesh(m.get_points(), filtered_triangles);
}
