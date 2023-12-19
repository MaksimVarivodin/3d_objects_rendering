#pragma once
#include "triangle.h"
class mesh
{
	vector<Vector3f> points_;
	vector<triangle> trians_;
public:
	vector<Vector3f>& get_points(){ return points_; }
	vector<triangle>& get_triangles(){return trians_; }
	int  count() const {return trians_.size();}
	mesh() :points_(), trians_() {}

	mesh(const vector<Vector3f>& p,  const vector<triangle>& tr)
	{
		points_ = p;
		trians_ = tr;
	}
	mesh(const vector<Vector3f>& p,  const vector<triangle>& tr, const float& scale_x, const float& scale_y, const float& scale_z):mesh(p, tr)
	{
		for(Vector3f & p: points_)
		{
			p.x *= scale_x;
			p.y *= scale_y;
			p.z *= scale_z;

		}

	}
};

