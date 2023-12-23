#include "mesh.h"


VertexArray mesh::to_triangle_vertex_array() const
{
	int array_size = trians_.size()*3;
	VertexArray result(Triangles, array_size);
	int i = 0;
	int j = 0;
	while(i < array_size){
		result[i	].position = points_[trians_[j].a()].to_Vector2f();
		result[i + 1].position = points_[trians_[j].b()].to_Vector2f();
		result[i + 2].position = points_[trians_[j].c()].to_Vector2f();
		result[i	].color = trians_[j].fill();
		result[i + 1].color = trians_[j].fill();
		result[i + 2].color = trians_[j].fill();
		i += 3;
		j++;
	}

	return result;
}

vector<VertexArray> mesh::to_line_vertex_array() const
{
	vector<VertexArray> result(trians_.size());

	for (size_t i = 0 ; i < trians_.size(); i++)
		result[i] = (trians_[i].to_line_vertex_array(points_));

	return result;
}

vector<point> mesh::normals_to_triangles() const
{
	vector<point> vectors(trians_.size());

	for(int i = 0; i < trians_.size(); i++)
	{
		point vec_a = points_[trians_[i].a()].vector( points_[trians_[i].b()]),
		vec_b = points_[trians_[i].a()].vector( points_[trians_[i].c()]); 
		vec_a *= vec_b;
		vectors[i] = vec_a.normalization();
	}
	return vectors;
}

vector<point> mesh::distances_to_point(const point& p) const
{
	vector<point> distances(trians_.size());
	int i =0 ;
	for (const triangle& tr: trians_){
		distances[i] = points_[trians_[i].a()] - p;
		i++;
	}
	return distances;
}


mesh& mesh::sort_triangles()
{
	sort(trians_.begin(), trians_.end(), 
		[this](triangle &t1, triangle &t2)
		{
			const float z1 = em_find_average(
				points_[t1.a()].z(),
				points_[t1.b()].z(),
				points_[t1.c()].z() );
			const float z2 = em_find_average(
				points_[t2.a()].z(),
				points_[t2.b()].z(),
				points_[t2.c()].z() );
			return z1 > z2;
		}
	);
	return *this;
}

