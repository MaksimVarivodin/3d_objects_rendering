#include "game_window.h"

void game_window::draw_cube()
{
	vector<Vector3f> points = move_center(
		Vector3f(0,0, 3),
		Vector3f(0, 0, 0),
		cube_.get_points());
	points = projection_.projection_method(points);
	//points = 

	
	string str;
	for (int i =0; i<cube_.count(); i++)
	{
		ConvexShape sh = cube_.get_triangles()[i].to_convex_shape(points);
		sh.setFillColor(Color::Transparent);
		sh.setOutlineColor(Color::White);
		sh.setOutlineThickness(1);

		draw(sh);
		//cin >> str;
	}
}

void game_window::run()
{	
	if (show_frame_rate_)
		f_per_sec_.count();
	while (isOpen())
	{
		Event event;
		while (pollEvent(event))
			// Пользователь нажал на «крестик» и хочет закрыть окно ?
			if (event.type == Event::Closed)
				// тогда закрываем его
				close();
		
		clear();
		draw_cube();
		if (show_frame_rate_) {
			draw(*(f_r_renderer_.to_text(f_per_sec_)));
			f_per_sec_++;
		}			
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

void game_window::init_cube(vector<Vector3f> points, vector<triangle> tr, const float& scale_x, const float& scale_y, const float& scale_z)
{
	cube_ = mesh(points, tr, scale_x, scale_y, scale_z);
}
