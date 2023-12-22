#pragma once
#include "matrix_impl.h"
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
	int em_find_maximum(const int& a, const int& b, const int& c);

	int em_find_minimum(const int& a, const int& b, const int& c);

	int em_find_average(const int& a, const int& b, const int& c);

	template <class T>
	T em_find_average(const vector<T>& vec)
	{
		T sum = T() ;
		for(const T& v: vec)
			sum+= v;
		return sum / (T)(vec.size());
	}

	float ctg(const float& radian_angle);

	double ctg(const double& radian_angle);

	float em_angle_to_radian(const float& angle);

	double em_angle_to_radian(const double& angle);

	matrix<float> em_x_rot_matrix(const float& radian_angle);

	matrix<float> em_y_rot_matrix(const float& radian_angle);

	matrix<float> em_z_rot_matrix(const float& radian_angle);

	vector<Vector3f> em_rotate_x(const vector<Vector3f>& v, const float &radian_angle );
	vector<Vector3f> em_rotate_y(const vector<Vector3f>& v, const float &radian_angle );
	vector<Vector3f> em_rotate_z(const vector<Vector3f>& v, const float &radian_angle );
	template<class T>
	T em_precision(T value, int precision)
	{
		T decades = pow(10, precision);
		return round(value * decades)/  decades;
	}
	template<class T>
	vector<Vector3<T>> em_precision(const vector<Vector3<T>>& v, int precision){
		vector<Vector3<T>> p(v.size());
		for (int i =0; i< p.size(); i++)
		{
			p[i].x = em_precision(v[i].x, precision);
			p[i].y = em_precision(v[i].y, precision);
			p[i].z = em_precision(v[i].z, precision);
		}
		return p;
	}
	matrix<float> em_project_function(
		const float& aspect_ratio,
		const float& fov,
		const float& z_compression,
		const float& z_monitor, 
		const Vector3<float> & to_project
	);
	float em_aspect_ratio(const float& height, const float& width);
	float em_field_of_view(const float & radian_angle);
	float em_z_compression(const float & z_horizon, const float & z_monitor);

	vector<Vector3f> em_move(const Vector3f& move, const vector<Vector3f> &points);

	vector<Vector3f> em_scale(const vector<Vector3f>& points, const Vector3f& scale_point);

	/*
	 * Создание векторов
	 */

	Vector3f em_find_vector_point(const Vector3f & a, const Vector3f & b);
	matrix<> em_find_vector_matrix(const Vector3f & a, const Vector3f & b);

	/*
	 * произведение векторов
	 */

	Vector3f em_cross_product_point(const Vector3f& a, const Vector3f& b);
	matrix<> em_cross_product_matrix(const Vector3f& a, const Vector3f& b);

	Vector3f em_vector_normalization(const Vector3f & point);
	matrix<> em_vector_normalization(const matrix<> & point);

	/*
	 * скалярное произведение
	 */
	float em_dot_product_point(const Vector3f& a, const Vector3f& b);
	float em_dot_product_matrix(const matrix<>& a, const matrix<>& b );

};