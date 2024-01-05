#pragma once
#include "light.h"
template <class T>
class camera
{
public:
	point<T> position_ = {0, 0, 0};
	point<T> direction_ = {0, 0, 1};

	T z_horizon_ = 1000.0f;
	T z_monitor_ = 0.1f;
	T width_ = 1920;
	T height_ = 1080;
	T degrees_fov_ = 90;
	T z_compression_;
	T field_of_view_;
	T aspect_ratio_;




	T radian_fov();
	T aspect_ratio();
	T z_compression();
	T z_monitor();
	point<T> position();
	void move(const point<T>& move_point);




	camera(const point<T>& position_, const point<T>& direction_, const T& z_horizon_, const T& z_monitor_, const T& width_, const T& height_, const T& degrees_fov_)
		: position_(position_), direction_(direction_), z_horizon_(z_horizon_), z_monitor_(z_monitor_), width_(width_), height_(height_), degrees_fov_(degrees_fov_)
	{
	}

	camera() = default;
};

