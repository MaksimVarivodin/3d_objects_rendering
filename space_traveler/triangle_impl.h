#include "triangle.h"


template<class T>
inline vector<Vertex> triangle<T>::to_triangle()
{
	vector<Vertex>result(3);
	result[0] = Vertex{Vector2{a_->get_const_x(), a_->get_const_y()}, fill};
	result[1] = Vertex{Vector2{b_->get_const_x(), b_->get_const_y()}, fill};
	result[2] = Vertex{Vector2{c_->get_const_x(), c_->get_const_y()}, fill};
	return result;
}

template<class T>
inline VertexArray triangle<T>::to_line()
{
	VertexArray result(LineStrip, 4);
	result[0].position = Vertex{Vector2{a_->get_const_x(), a_->get_const_y()}, outline};
	result[1].position = Vertex{Vector2{b_->get_const_x(), b_->get_const_y()}, outline};
	result[2].position = Vertex{Vector2{c_->get_const_x(), c_->get_const_y()}, outline};
	result[3].position = Vertex{Vector2{a_->get_const_x(), a_->get_const_y()}, outline};
	return result;
}