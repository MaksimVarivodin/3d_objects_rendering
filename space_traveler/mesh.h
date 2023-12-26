#pragma once
#include "triangle_impl.h"

template <class T = float>
class mesh{
	vector<point<T>*> points_;
	vector<triangle<T>> triangles_;

public:
	VertexArray to_triangle_array() const;
	vector<VertexArray> to_line_array() const;

	const vector<point<T>*>& get_points(){return points_;}
	const vector<triangle<T>>& get_triangles(){ return triangles_;}

	vector<point<T>> normals_to_triangles();
	vector<point<T>> distances_to_point(const point<T>& p);
	void sort_triangles();

	mesh():points_(), triangles_(){}

	mesh(const vector<point<T>*>& p,  const vector<triangle<T>>& tr)
	{
		points_ = p;
		triangles_ = tr;
	}
	mesh(const mesh<T>& other) = default;
	mesh(mesh<T>&& other) noexcept = default;
	mesh<T>& operator=(const mesh<T>& other) = default;
	mesh<T>& operator=(mesh<T>&& other) noexcept = default;

	~mesh()
	{
		for(size_t i= 0; i< points_.size(); i++)
			delete points_[i];
	}
};
