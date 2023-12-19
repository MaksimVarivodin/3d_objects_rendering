#include "projection.h"

vector<Vector3f> projection::projection_method(vector<Vector3f>& points) const
{
	int iter = 0;
	vector<Vector3f> result(points.size());
	for (Vector3f & p: points)
	{		
		result[iter] = project_function(
			asp_ratio_fov_,
			z_compression_,
			z_to_monitor_, p).to_vector3();
		iter++;
	}			
	return result;
}
