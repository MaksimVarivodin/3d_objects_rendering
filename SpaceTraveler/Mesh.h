#pragma once
#include "triangle.h"
template <class T>
class mesh
{
	vector<point<T>*> points_;
	vector<triangle<T>> trians_;

public:
	const vector<point<T>*>&	points() {return points_;}
	const vector<triangle<T>>&	trians() {return trians_;}

	void points(const vector<point<T>*>&	p){ points_ = p;}
	void trians(const vector<triangle<T>>&	t){ trians_ = t;}

	mesh() :points_(), trians_() {}

	~mesh()
	{
		for(size_t i = 0; i< points_.size(); i++)
			delete points_[i];
	}
	mesh(const mesh& other) = default;
	mesh(mesh&& other) noexcept = default;
	mesh& operator=(const mesh& other) = default;
	mesh& operator=(mesh&& other) noexcept = default;

	mesh(const vector<point<T>*>& points_, const vector<triangle<T>>& trians_)
		: points_(points_), trians_(trians_){}
};

