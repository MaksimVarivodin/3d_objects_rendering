#include "engine_math.h"



float engine_math::ctg(const float& radian_angle)
{
	return 1.0f / tan(radian_angle);
}

float engine_math::em_angle_to_radian(const float& angle)
{
	return ANGLE_TO_RADIAN * angle;
}



float engine_math::em_aspect_ratio(const float& height, const float& width)
{
	return height / width;
}

float engine_math::em_field_of_view(const float& radian_angle)
{
	return ctg(radian_angle);
}

float engine_math::em_z_compression(const float& z_horizon, const float& z_monitor)
{
	return z_horizon / (z_horizon - z_monitor);
}
