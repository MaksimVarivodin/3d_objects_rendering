#include "engine_math.h"

int engine_math::find_maximum(const int& a, const int& b, const int& c)
{
	//cout << "Biggest ->";
	if (a > c) {
		if (a >= b) {
			//cout << a<< endl;
			return a;
		}
		//cout << b << endl;
		return b;
	}
	else if (b > c) {
		//cout << b << endl;
		return b;
	}
	//cout << c << endl;
	return c;
}

int engine_math::find_minimum(const int& a, const int& b, const int& c)
{
	//cout << "Smallest->";
	if (b < a) {
		if (b <= c) {
			//cout << b << endl;
			return b;
		}
		//cout << c << endl;
		return c;
	}
	else if (c < a) {
		//cout << c << endl;
		return c;
	}
	//cout << a << endl;
	return a;
}

int engine_math::find_average(const int& a, const int& b, const int& c)
{
	//cout << "Average-> " << (a + b + c) / 3 << endl;
	return (a + b + c) / 3;
}

float engine_math::ctg(const float& radian_angle)
{
	return 1.0f / tanf(radian_angle);
}

double engine_math::ctg(const double& radian_angle)
{
	return 1.0f / tan(radian_angle);
}

float engine_math::angle_to_radian(const float& angle)
{
	return A_TO_R_FLOAT * angle;
}

double engine_math::angle_to_radian(const double& angle)
{
	return A_TO_R_DOUBLE * angle;
}

engine_math::matrix<float> engine_math::x_axis_rotation(const float& radian_angle)
{
	return 
		matrix<float>(vector<vector<float>>
		{
			{	1,	0,				0	},
			{	0, cosf(radian_angle),	-sinf(radian_angle)},
			{	0, sinf(radian_angle),	cosf(radian_angle) }
		});
}

engine_math::matrix<float> engine_math::y_axis_rotation(const float& radian_angle)
{
	return
		matrix<float>(vector<vector<float>>
	{
		{	cosf(radian_angle),	0,	sinf(radian_angle)},
		{	0,				1,			0	},
		{	-sinf(radian_angle),	0,	cosf(radian_angle)}
	});
}

engine_math::matrix<float> engine_math::z_axis_rotation(const float& radian_angle)
{
	return
		matrix<float>(vector<vector<float>>
	{
		{	cosf(radian_angle), sinf(radian_angle), 0},
		{ sinf(radian_angle),cosf(radian_angle), 0 },
		{ 0,	0,	1 }
	});
}

engine_math::matrix<float> engine_math::project_function(
	const float& aspect_ratio_fov, const float& z_compression,
	const float& z_monitor, const Vector3<float>& to_project)
{
	const float z_distance = 1.0f / to_project.z;
	matrix result(
		vector<vector<float>>{
			{aspect_ratio_fov * to_project.x * z_distance },
			{aspect_ratio_fov * to_project.y * z_distance },
			{z_compression *(to_project.z - z_monitor) * z_distance}
		}

	);
	return result;
}

float engine_math::aspect_ratio_field_of_view(const float& height, const float& width, const float& radian_angle)
{
	return (height / width) * ctg(radian_angle);
}

float engine_math::z_compression(const float& z_horizon, const float& z_monitor)
{
	return z_horizon / (z_horizon - z_monitor);
}

//vector<Vector2f> engine_math::move_center(const Vector2f& new_center, const Vector2f& old_center,
//	const vector<Vector3f>& points)
//{
//	const Vector2f	move_v(new_center.x - old_center.x,
//				new_center.y - old_center.y);
//	
//	return move(move_v, points);
//}

vector<Vector3f> engine_math::move_center(const Vector3f& new_center, const Vector3f& old_center,
	const vector<Vector3f>& points)
{
	const Vector3f	move_v(new_center.x - old_center.x,
				new_center.y - old_center.y, 
				new_center.z - old_center.z);
	return move(move_v, points);
}

vector<Vector3f> engine_math::move(const Vector3f& move, const vector<Vector3f>& points)
{
	vector<Vector3f> result(points.size());
	for(int i = 0; i< points.size(); i++)
	{
		result[i] = Vector3f(points[i].x + move.x, points[i].y+ move.y, points[i].z + move.z);
	}
	return result;
}
