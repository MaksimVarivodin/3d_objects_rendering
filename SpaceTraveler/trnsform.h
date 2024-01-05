#pragma once
#include "mesh_loader.h"


template <class T>
class trnsform
{
public:
	static mesh<T> transformation(
		const mesh<T>& object_,
		const point<T>& radian_angles_,
		const point<T>& object_move_,
		const point<T>& object_scale_,
		const camera<T>& camera_,
		const light<T>& light_,
		const Vector2<T>& coordinate_invertion_
	);

	static matrix<T> set_angles(const point<T>& radian);

	static void filter_by_normals(mesh<T>& object, const camera<T>& cam);

	static void projection(mesh<T>& object, const camera<T>& cam);

	static void color_filtering(mesh<T>& object, const light<T>& l);

	static void to_screen_coordinate_plane(mesh<T>& object, const Vector2<T>& coordinate_invertion);
};


