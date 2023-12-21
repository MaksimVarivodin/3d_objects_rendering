#pragma once
#include "mesh.h"

class projection
{
	
	float asp_ratio_ = 0;
	float field_of_view_ = 0;
	float z_compression_ = 0;
	float z_to_monitor_ = 0;



public:
	projection(
		const float &height, 
		const float & width,
		const float & degrees_angle,
		const float & z_horizon,
		const float & z_monitor
	):	asp_ratio_(em_aspect_ratio(height, width)),
		field_of_view_ (em_field_of_view(em_angle_to_radian(degrees_angle / 2.0f))),
		z_compression_ (em_z_compression(z_horizon, z_monitor)),
		z_to_monitor_(z_monitor)
	{
	}
	projection() = default;
	projection(const projection& other) = default;


	projection& operator=(const projection& other);

	mesh projection_method(const mesh& m) const;

};
