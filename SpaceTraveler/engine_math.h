#pragma once
#include "matrix.h"
namespace engine_math {
	/*
	Constant to convert degrees to radian angle:
	PI / 180
	@return float
	*/
	constexpr float A_TO_R_FLOAT = static_cast<float>(M_PI) / 180.0f;

	/*
	Constant to convert degrees to radian angle:
	PI / 180
	@return double
	*/
	constexpr double A_TO_R_DOUBLE = M_PI / 180.0;


	/*
	Function to find maximum between 3 numbers
	@return float
	*/
	int find_maximum(const int& a, const int& b, const int& c);

	int find_minimum(const int& a, const int& b, const int& c);

	int find_average(const int& a, const int& b, const int& c);

	float ctg(const float& radian_angle);

	double ctg(const double& radian_angle);

	float angle_to_radian(const float& angle);

	double angle_to_radian(const double& angle);

	matrix<float> x_axis_rotation(const float& radian_angle);

	matrix<float> y_axis_rotation(const float& radian_angle);

	matrix<float> z_axis_rotation(const float& radian_angle);

	matrix<float> project_function(
		const float& aspect_ratio_fov,
		const float& z_compression,
		const float& z_monitor, 
		const Vector3<float> & to_project
	);
	float aspect_ratio_field_of_view(const float& height, const float& width, const float & radian_angle);
	float z_compression(const float & z_horizon, const float & z_monitor);

	/*vector<Vector2f> move_center(const Vector2f& new_center, const Vector2f& old_center, const vector<Vector3f> &points);*/

	vector<Vector3f> move_center(const Vector3f& new_center, const Vector3f& old_center, const vector<Vector3f> &points);

	vector<Vector3f> move(const Vector3f& move, const vector<Vector3f> &points);

	vector<Vector3f> scale(const vector<Vector3f> points, const float & scale);

};