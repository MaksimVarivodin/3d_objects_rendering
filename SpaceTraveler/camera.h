#pragma once
#include "mesh_loader.h"

class camera
{
	
	float asp_ratio_ = 0;
	float field_of_view_ = 0;
	float z_compression_ = 0;
	float z_to_monitor_ = 0;
	Vector3f camera_location = {0, 0, 0};


public:
	camera(
		const float & screen_height, 
		const float & screen_width,
		const float & view_angle,
		const float & z_horizon,
		const float & z_monitor
	):	asp_ratio_(em_aspect_ratio(screen_height, screen_width)),
		field_of_view_ (em_field_of_view(em_angle_to_radian(view_angle / 2.0f))),
		z_compression_ (em_z_compression(z_horizon, z_monitor)),
		z_to_monitor_(z_monitor)
	{
	}
	camera() = default;
	camera(const camera& other) = default;


	camera& operator=(const camera& other);

	mesh projection_method(const mesh& m) const;
	mesh filter_by_normals(const mesh& m) const;
};
