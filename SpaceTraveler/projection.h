#pragma once
#include "mesh.h"

class projection
{
	float asp_ratio_fov_ = 0;
	float z_compression_ = 0;
	float z_to_monitor_ = 0;
	
public:
	projection(
		const int &height, 
		const int & width,
		const float & degrees_angle,
		const float & z_horizon,
		const float & z_monitor
	)
	{
		init_asp_ratio_fov(height, width, degrees_angle);
		init_z_compression(z_horizon, z_monitor);		
		z_to_monitor_ = z_monitor;
	}
	vector<Vector3f> projection_method(vector<Vector3f>&) const;
	void init_asp_ratio_fov(const float& height,
	                        const float& width,
	                        const float & degrees_angle)
	{
		const float radian_angle = angle_to_radian(degrees_angle/2.0f);
		asp_ratio_fov_ = aspect_ratio_field_of_view(height, width, radian_angle);

	}
	void init_z_compression(const float & z_horizon,
		const float & z_monitor)
	{
		z_compression_ = z_compression(z_horizon, z_monitor);
	}
};
