#include "trnsform.h"

template<class T>
inline mesh<T> trnsform<T>::transformation(
	const mesh<T>& object_,
	const point<T>& radian_angles_,
	const point<T>& object_move_,
	const point<T>& object_scale_,
	const camera<T>& camera_,
	const light<T>& light_,	
	const Vector2<T>& coordinate_invertion_)
{
	mesh<T> temp(object_);
	camera<T> cam_temp;

	temp.rotate(set_angles(radian_angles_));

	temp.move(object_move_);

	

	filter_by_normals(temp, camera_);

	color_filtering(temp, light_);

	projection(temp, camera_);		

	temp.sort_triangles();

	temp.scale(object_scale_);

	to_screen_coordinate_plane(temp, coordinate_invertion_);

	return temp;
}

template<class T>
inline matrix <T> trnsform<T>::set_angles(const point<T>& radian)
{

	matrix <T> tr_matrix(matrix<T>::x_rotation(radian.x));
	matrix <T> y, z;
	if (radian.y!= T(0)){
		y = matrix<T>::y_rotation(radian.y);
		tr_matrix *= y;
	}
		

	if (radian.z!= T(0)){
		z = matrix<T>::z_rotation(radian.z);
		tr_matrix *= z;
	}
		
	return tr_matrix;
}



template<class T>
inline void trnsform<T>::filter_by_normals(mesh<T>& object, const camera<T>& cam)
{
	vector<triangle<T>> filtered_tr;
	filtered_tr.reserve(object.triangle_size());
	vector<point<T>> filtered_norm;
	filtered_norm.reserve(object.triangle_size());
	for(size_t i = 0; i< object.triangle_size(); i++){
		point<T> distance = object.triangles(i).distance(cam.position_);
		T dot_pr = point<T>::dot_product(
				object.normals(i),
				distance);
		if( dot_pr < T(0)){
			filtered_tr.push_back(object.triangles(i));
			filtered_norm.push_back(object.normals(i));
		}		
	}
	object.trians(filtered_tr);
	object.normals(filtered_norm);
}

template<class T>
inline void trnsform<T>::projection(mesh<T>& object, const camera<T>& cam)
{
	
	T z_compression = em_z_compression<T>(cam.z_horizon_, cam.z_monitor_);
	T aspect_ratio = em_aspect_ratio<T>(cam.height_, cam.width_);
	T fov = em_field_of_view(em_angle_to_radian(cam.degrees_fov_ / T(2.0f)));
	for (point<T>* p: object.points())
		(*p) =(*p).projection(aspect_ratio,	fov , z_compression, cam.z_monitor_);
	
}

template<class T>
inline void trnsform<T>::color_filtering(mesh<T>& object, const light<T>& l)
{
	vector<triangle<T>> tr = object.trians();
	for(size_t i =0; i< tr.size(); i++){
		T dot_product = point<T>::dot_product(object.normals(i), l.direction);
		
		tr[i].fill({
			static_cast<Uint8>(((float)	object.triangles(i).fill().r) * dot_product),
			static_cast<Uint8>(((float)	object.triangles(i).fill().g) * dot_product),
			static_cast<Uint8>(((float)	object.triangles(i).fill().b) * dot_product)
		});
	}
	object.trians(tr);

}

template<class T>
inline void trnsform<T>::to_screen_coordinate_plane(mesh<T>& object, const Vector2<T>& coordinate_invertion)
{
	for(point<T>* pointer: object.points()){
		pointer->x *= coordinate_invertion.x;
		pointer->y *= coordinate_invertion.y;
	}
}
