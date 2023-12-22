#include "game_window.h"

mesh game_window::calculate_points(mesh object, const float& angle1, const float& angle2, const float& angle3) const
{
	const float radian_angle1 = em_angle_to_radian(angle1),
			radian_angle2 = em_angle_to_radian(angle2),
			radian_angle3 = em_angle_to_radian(angle3);

	object
		.rotate_x(radian_angle1)
		.rotate_y(radian_angle2)
		//.rotate_z(radian_angle3)
		.move(Vector3f(0, 0, 8.0f));

	object = camera_.filter_by_normals(object);

	object = light_.color_filtering(object);

	object = camera_.projection_method(object);
	
	object
	.move(Vector3f(1, 1, 0))
	.scale(Vector3f(
								0.5f * getSize().x,
								0.5f * getSize().y,
								1.f
	))
	.sort_triangles();


	return object;
}

void game_window::draw_triangle(const vector<VertexArray>& shapes)
{
	for(const VertexArray & v: shapes)
		draw(v);	
}

void game_window::run()
{	
	if (show_frame_rate_)
		f_per_sec_.count();
	float angle_x = 35,
			angle_y = 0,
			angle_z = 0;
	int index= 0;
	long counter = 0;
	const string file_names[] = {"VideoShip","teapot"};
	object_loader_.file_name(file_names[index]);
	mesh * loaded = object_loader_.load();
	mesh temp;
	if (loaded== nullptr)
		throw exception("object was null");
	temp = calculate_points(*loaded, angle_x, angle_y, angle_z);


	while (isOpen())
	{
		Event event;
		while (pollEvent(event))
			// Пользователь нажал на «крестик» и хочет закрыть окно ?
			if (event.type == Event::Closed ||
				( event.type == Event::KeyPressed &&  Keyboard::isKeyPressed(Keyboard::Escape)))
				// тогда закрываем его
				close();
			
		
		clear();

		draw_triangle(temp.to_triangle_vertex_array());
		
		const float fps= f_per_sec_.get_average_frame_rate();

		if (fps > 0)
		{
			angle_x += 20.f / fps;
			angle_y += 1000.0f / fps;
			angle_z += 750.0f /fps;
		}
			
		temp = calculate_points(*loaded, angle_x, angle_y, angle_z);
		/*if (counter == 60 * 20)
		{
			counter = 0;
			if (index < 2)
				index++;
			else
				index = 0;
			object_loader_.file_name(file_names[index]);
			loaded = object_loader_.load();
		}*/
			
		if (show_frame_rate_) {
			draw(*(f_r_renderer_.to_text(f_per_sec_)));
			f_per_sec_++;
		}
		counter++;
		display();
		
	}
}

void game_window::set_frame_rate_show(bool value)
{
	this->show_frame_rate_	= value;
	if (show_frame_rate_)
		f_per_sec_.count();
	else
		f_per_sec_.stop();
}

