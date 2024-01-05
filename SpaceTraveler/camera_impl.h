#include "camera.h"
template<class T>
inline void camera<T>::move(const point<T>& move_point)
{
	cout << "Move point: ";
	move_point.print();
	cout << "Position: ";
	position().print();
	position_ += move_point;
}
template<class T>
inline void camera<T>::rotate(const point<T>& degrees_angles)
{
	point<T> position_in_zero = look_direction_ - position_;
	cout << "position in zero: ";
	position_in_zero.print();
	matrix<T> rot_matrix = matrix<T>::x_y_z_rotation(degrees_angles.x, degrees_angles.y, degrees_angles.z);
	position_in_zero *= rot_matrix;
	cout << "rotated position in zero: ";
	position_in_zero.print();
	position_ =  position_in_zero + position_;
	cout << "result position: ";
	position_.print();
}