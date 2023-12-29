#pragma once
#include "mesh_loader.h"


template <class T>
class trnsform
{	
public:
	static mesh<T> transformation(
		const mesh<T>& object,
		const camera<T>& cam,
		const light<T>& l,
		const point<T>& move,
		const point<T>& scale,
		const point<T>& radian
		);

	static matrix<T> set_angles(const point<T>& radian);

	static void filter_by_normals(mesh<T>& object, const camera<T>& cam);

	static void projection(mesh<T>& object, const camera<T>& cam);

	static void color_filtering(mesh<T> & object, const light<T> & l);
};


