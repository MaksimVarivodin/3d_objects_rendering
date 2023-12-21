#include "projection.h"

projection& projection::operator=(const projection& other)
{
	this->z_compression_ = other.z_compression_;
	this->field_of_view_ = other.field_of_view_;
	this->z_to_monitor_ = other.z_to_monitor_;
	this->asp_ratio_ = other.asp_ratio_;
	return *this;
}

mesh projection::projection_method(const mesh& m) const
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
