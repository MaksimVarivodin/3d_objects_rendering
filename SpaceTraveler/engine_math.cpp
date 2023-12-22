#include "engine_math.h"

int engine_math::em_find_maximum(const int& a, const int& b, const int& c)
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

int engine_math::em_find_minimum(const int& a, const int& b, const int& c)
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

int engine_math::em_find_average(const int& a, const int& b, const int& c)
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

float engine_math::em_angle_to_radian(const float& angle)
{
	return A_TO_R_FLOAT * angle;
}

double engine_math::em_angle_to_radian(const double& angle)
{
	return A_TO_R_DOUBLE * angle;
}


engine_math::matrix<float> engine_math::em_x_rot_matrix(const float& radian_angle)
{
	const vector<vector<float>> data
		{
			{	1,	0,				0	},
			{	0, cosf(radian_angle),	-sinf(radian_angle)},
			{	0, sinf(radian_angle),	cosf(radian_angle) }
		};
	return matrix(data);
}

engine_math::matrix<float> engine_math::em_y_rot_matrix(const float& radian_angle)
{
	vector<vector<float>> data
	{
		{	cosf(radian_angle),		0,	sinf(radian_angle)	},
		{	0,						1,			0			},
		{	-sinf(radian_angle),	0,	cosf(radian_angle)	}
	};
	return matrix(data);
}

engine_math::matrix<float> engine_math::em_z_rot_matrix(const float& radian_angle)
{
	vector<vector<float>> data
	{
		{		cosf(radian_angle), -sinf(radian_angle),0 },
		{		sinf(radian_angle), cosf(radian_angle),	0 },
		{		0,					0,					1 }
	};
	return matrix(data);
}

vector<Vector3f> engine_math::em_rotate_x(const vector<Vector3f>& v, const float& radian_angle)
{
	vector<Vector3f> result(v.size());
	matrix rot_matrix = em_x_rot_matrix(radian_angle);
	for (int i = 0; i< v.size(); i++)
		result[i] = rot_matrix * v[i];
	
	return result;
}

vector<Vector3f> engine_math::em_rotate_y(const vector<Vector3f>& v, const float& radian_angle)
{
	vector<Vector3f> result(v.size());
	matrix<float> rot_matrix = em_y_rot_matrix(radian_angle);
	for (int i = 0; i< v.size(); i++)
		result[i] = rot_matrix * v[i];
	
	return result;
}

vector<Vector3f> engine_math::em_rotate_z(const vector<Vector3f>& v, const float& radian_angle)
{
	vector<Vector3f> result(v.size());
	matrix<float> rot_matrix = em_z_rot_matrix(radian_angle);
	for (int i = 0; i< v.size(); i++)
		result[i] = rot_matrix * v[i];
	
	return result;
}

engine_math::matrix<float> engine_math::em_project_function(
	const float& aspect_ratio,
	const float& fov,
	const float& z_compression,
	const float& z_monitor,
	const Vector3<float>& to_project)
{

	matrix result(
		vector<vector<float>>{
			{aspect_ratio * fov * to_project.x},
			{fov * to_project.y},
			{z_compression *(to_project.z - z_monitor)}
		}
	);
	if (to_project.z != 0.0f)
		result /= to_project.z;
	return result;
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

vector<Vector3f> engine_math::em_move(const Vector3f& move, const vector<Vector3f>& points)
{
	vector<Vector3f> result(points.size());
	for(int i = 0; i< points.size(); i++)
	{
		result[i] = Vector3f(points[i].x + move.x, points[i].y+ move.y, points[i].z + move.z);
	}
	return result;
}

vector<Vector3f> engine_math::em_scale(const vector<Vector3f>& points, const Vector3f& scale_point)
{
	if (	scale_point.x != 1.0f 
		||	scale_point.y != 1.0f 
		||	scale_point.z != 1.0f)
	{
		vector<Vector3f> res (points.size());
		for(int i = 0; i < points.size(); i++)
		{
			res[i] = Vector3f(
				points[i].x * scale_point.x,
				points[i].y * scale_point.y,
				points[i].z * scale_point.z);
		}
		return res;
	}
	return points;
}

Vector3f engine_math::em_find_vector_point(const Vector3f& a, const Vector3f& b)
{
	return Vector3f{
		b.x - a.x,
		b.y - a.y,
		b.z - a.z
	};
}

engine_math::matrix<> engine_math::em_find_vector_matrix(const Vector3f& a, const Vector3f& b)
{
	return matrix<float>{
		{
			{b.x - a.x},
			{b.y - a.y},
			{b.z - a.z}
		}
	};
}

Vector3f engine_math::em_cross_product_point(const Vector3f& a, const Vector3f& b)
{
	return Vector3f{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

engine_math::matrix<> engine_math::em_cross_product_matrix(const Vector3f& a, const Vector3f& b)
{
	return matrix{
		{
			{a.y * b.z - a.z * b.y},
			{a.z * b.x - a.x * b.z},
			{a.x * b.y - a.y * b.x}
		}
	};
}

Vector3f engine_math::em_vector_normalization(const Vector3f& point)
{
	const float length = sqrtf( 
		 point.x	* point.x
		+	point.y	* point.y
		+	point.z * point.z
	);
	return Vector3f{
		point.x / length,
		point.y / length,
		point.z / length
	};
}

engine_math::matrix<> engine_math::em_vector_normalization(const matrix<float>& point)
{
	
	vector<vector<float>> data = vector(
		point.rows(),
		vector<float>(
			point.columns(),
			0
		)
	);
	float to_sqrtf = 0;
	
	for(int i = 0; i< point.rows(); i++)
		for(int j = 0; j< point.columns(); j++)
		to_sqrtf += point(i, j) * point(i, j);

	to_sqrtf = sqrtf(to_sqrtf);

	for(int i = 0; i< point.rows(); i++)
		for(int j = 0; j< point.columns(); j++)
		data[i][j] =  point(i, j) / to_sqrtf;
	
	return matrix{data};
}

float engine_math::em_dot_product_point(const Vector3f& a, const Vector3f& b)
{
	return 	a.x * b.x + a.y  * b.y + a.z * b.z ;
}

float engine_math::em_dot_product_matrix(const matrix<>& a, const matrix<>& b)
{
	if (a.rows()!= b.rows() || a.columns()!= b.columns() )
		throw exception("not equal matrix sizes");

	float sum = 0;
	for (int i = 0; i< a.rows() ; i++)
		for(int j = 0; j < a.columns(); j++)
		sum += a(i, j) * b(i, j);

	return sum;
	
}
