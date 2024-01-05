#pragma once
#include "camera.h"
template <class T>
class mesh
{
	vector<point<T>*> points_;
	vector<triangle<T>> trians_;
	vector<point<T>> normals_;

public:
	vector<point<T>*>& points() { return points_; }
	vector<triangle<T>>& trians() { return trians_; }
	vector<point<T>> & normals() { return normals_; }
	void move(const point<T>& move_point) {
		for (point<T>* p : points_) {
			*p += move_point;
		}
	}
	void scale(const point<T>& scale_point) {
		for (point<T>* p : points_) {
			*p *= scale_point;
		}
	}

	void rotate(const matrix<T>& rotation_matrix){
		for(point<T> * p:points_)
			(*p) *= rotation_matrix;
		
		for (point<T>& p: normals_)
			p *= rotation_matrix;		
	}
	void sort_triangles(){
		std::sort(trians_.begin(), trians_.end(), 
				[](triangle<T>& t1, triangle<T>& t2){
					return t1 > t2;
				}
			);
	}
	size_t triangle_size(){return trians_.size();}
	void points(const vector<point<T>*>& p) { points_ = p; }
	void trians(const vector<triangle<T>>& t) { trians_ = t; }
	void normals(const vector<point<T>>& t) { normals_ = t; }

	point<T>* points(const size_t & ind){return points_[ind];}

	triangle<T> triangles(const size_t & ind){return trians_[ind];}

	point<T> normals(const size_t & ind){return normals_[ind];}

	VertexArray to_filled_triangles(){

		VertexArray array(Triangles,  triangle_size()* 3);
		for(size_t i = 0, j = 0; i < triangle_size(); i++, j += 3){
			array[j		] = Vertex{(*trians_[i].a()).to_Vector2(), trians_[i].fill()};
			array[j + 1	] = Vertex{(*trians_[i].b()).to_Vector2(), trians_[i].fill()};
			array[j + 2	] = Vertex{(*trians_[i].c()).to_Vector2(), trians_[i].fill()};
		}
		
		return array;
	}
	VertexArray to_outline_triangles(){

		VertexArray outline_triangles(Lines,  triangle_size()* 6);
		for(size_t i = 0, j = 0; i < triangle_size(); i++, j += 6){
			outline_triangles[j		] = Vertex{(*trians_[i].a()).to_Vector2(), trians_[i].outline()};
			outline_triangles[j + 1	] = Vertex{(*trians_[i].b()).to_Vector2(), trians_[i].outline()};
			outline_triangles[j + 2	] = Vertex{(*trians_[i].b()).to_Vector2(), trians_[i].outline()};
			outline_triangles[j + 3	] = Vertex{(*trians_[i].c()).to_Vector2(), trians_[i].outline()};
			outline_triangles[j + 4	] = Vertex{(*trians_[i].c()).to_Vector2(), trians_[i].outline()};
			outline_triangles[j	+ 5	] = Vertex{(*trians_[i].a()).to_Vector2(), trians_[i].outline()};
		}
		
		return outline_triangles;
	}

	mesh() :points_(), trians_() {}

	~mesh()
	{
		for (size_t i = 0; i < points_.size(); i++)
			delete points_[i];
	}


	mesh(mesh&& other) noexcept = default;
	mesh& operator=(const mesh& other) = default;
	mesh& operator=(mesh&& other) noexcept = default;


	mesh(const mesh<T>& other)
	{
		points_ = vector<point<T>*>(other.points_.size());

		for (size_t i = 0; i < other.points_.size(); i++)
			points_[i] = engine_math::copy(other.points_[i]);

		trians_ = vector<triangle<T>>(other.trians_.size());

		for (size_t i = 0; i < other.trians_.size(); i++)
			trians_[i] = triangle<T>::copy(other.trians_[i], points_);

		normals_ =other.normals_;
	}

	mesh(const vector<point<T>*>& points_, const vector<triangle<T>>& trians_, const vector<point<T>>& normals_)
		: points_(points_), trians_(trians_), normals_(normals_)
	{
	}
};

