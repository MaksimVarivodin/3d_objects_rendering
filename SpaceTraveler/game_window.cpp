#pragma once;

#include "game_window.h"


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

		draw(temp.to_triangle_vertex_array());

		const float fps= f_per_sec_.get_average_frame_rate();

		if (fps > 0)
		{
			angle_x += 20.f / fps;
			angle_y += 1000.0f / fps;
			angle_z += 750.0f /fps;
		}
			
		temp = calculate_points(*loaded, angle_x, angle_y, angle_z);
		
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

