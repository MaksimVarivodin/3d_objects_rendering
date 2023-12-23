#pragma once
#include "point.h"
namespace engine_math {

	/*
	Constant to convert degrees to radian angle:
	PI / 180
	@return float
	*/
	constexpr float ANGLE_TO_RADIAN = static_cast<float>(M_PI) / 180.0f;

	/*
	Function to find maximum between 3 numbers
	@return float
	*/
	template <class T>
	const T& em_find_maximum(const T& a, const T& b, const T& c);

	template <class T>
	const T& em_find_minimum(const T& a, const T& b, const T& c);

	template <class T>
	const T& em_find_average(const T& a, const T& b, const T& c);

	float ctg(const float& radian_angle);

	float em_angle_to_radian(const float& angle);

	float em_aspect_ratio(const float& height, const float& width);
	float em_field_of_view(const float & radian_angle);
	float em_z_compression(const float & z_horizon, const float & z_monitor);

	template<class T>
	const T&  em_find_maximum(const T& a, const T& b, const T& c)
	{
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
	const T& em_find_minimum(const T& a, const T& b, const T& c)
	{
			
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
	const T& em_find_average(const T& a, const T& b, const T& c)
	{
		return (a + b + c) / (T)3;
	}

};