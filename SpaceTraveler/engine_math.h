#pragma once
#include "point_impl.h"

namespace engine_math {

	template<class T>
	T degrees_to_radian_multiplier() {
		return static_cast<T>(M_PI) / T(180.0);
	}
	template<class T>
	T em_find_maximum(const T& a, const T& b, const T& c) {
		if (a > c) {
			if (a >= b)
				return a;
			return b;
		}
		else if (b > c)
			return b;
		return c;
	}
	template<class T>
	T em_find_minimum(const T& a, const T& b, const T& c) {
		if (b < a) {
			if (b <= c)
				return b;
			return c;
		}
		else if (c < a)
			return c;
		return a;
	}
	template<class T>
	T em_find_average(const T& a, const T& b, const T& c){
		return (a + b + c) / T(3);
	}

	template<class T>
	T ctg(const T& radian_angle){
		return T(1) / T(tan(radian_angle));
	}
	template<class T>
	T em_angle_to_radian(const T& angle){
		return degrees_to_radian_multiplier<T>() * angle;
	}
	template<class T>
	T em_aspect_ratio(const T& height, const T& width){
		return height / width;
	}
	template<class T>
	T em_field_of_view(const T& radian_angle){
		return ctg(radian_angle);
	}
	template<class T>
	T em_z_compression(const T& z_horizon, const T& z_monitor){
		return z_horizon / (z_horizon - z_monitor);
	}

};