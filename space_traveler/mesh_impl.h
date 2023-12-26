#pragma once
#include "mesh.h"
template<class T>

inline VertexArray mesh<T>::to_triangle_array() const
{	

	VertexArray result (Triangles, triangles_.size() * 3);
	unsigned i = 0;
	vector<Vertex> temp;
	while(i < triangles_.size())
	{
		temp = triangles_[i].to_triangle();

		result[i] = temp[0];
		result[i + 1] = temp[1];
		result[i + 2] = temp[2];

		i++;
	}
	return result;
}

template<class T>
inline vector<VertexArray> mesh<T>::to_line_array() const
{
	unsigned i = 0;

	vector<VertexArray> result (triangles_.size());
	
	for(auto& r: result){

		r = triangles_[i].to_line();

		i++;

	}

	return result;
}

template<class T>
inline vector<point<T>> mesh<T>::normals_to_triangles()
{
	vector<point<T>> normals (triangles_.size());
	unsigned i =0;

	for(auto & d: normals)
	{
		point<T> vec_a = triangles_[i].a()->vector(triangles_[i].b());
		point<T> vec_b = triangles_[i].a()->vector(triangles_[i].c());
		vec_a *= vec_b;
		d = vec_a.normalization();
		i++;
	}

	return normals;
}

template<class T>
inline vector<point<T>> mesh<T>::distances_to_point(const point<T> & p)
{
	vector<point<T>> distances(triangles_.size());

	unsigned i = 0;

	for (triangle& tr: triangles_){
		tr = triangles_.a()-> operator-(p);
		i++;
	}

	return distances;
}

template<class T>
inline void mesh<T>::sort_triangles(){
	sort(
		triangles_.begin(),
		triangles_.end(),
		[this](triangle & t1, triangle & t2){

			const T z1 = em_find_average(
			t1.a()->z(),
			t1.b()->z(),
			t1.c()->z()
			);

			const T z2 = em_find_average(
			t2.a()->z(),
			t2.b()->z(),
			t2.c()->z()
			);

			return z1 > z2;

		}
	);
}
