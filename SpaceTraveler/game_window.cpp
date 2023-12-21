#include "game_window.h"

mesh game_window::calculate_points(const float& angle1, const float& angle2) const
{
	const float radian_angle1 = em_angle_to_radian(angle1),
			radian_angle2 = em_angle_to_radian(angle2);
	mesh temp(cube_);
	temp.rotate_x(radian_angle1)
		.rotate_y(radian_angle2)
		.move(Vector3f(0, 0, 3.0f));

	temp = camera_.filter_by_normals(temp);
	temp = camera_.projection_method(temp);
	
	temp
	.move(Vector3f(1, 1, 0))
	.scale(Vector3f(
								0.5f * getSize().x,
								0.5f * getSize().y,
								1.f
	));
	return temp;
}

void game_window::draw_triangle(const vector<VertexArray>& shapes, const vector<VertexArray>& lines)
{
	for(int i = 0; i< shapes.size(); i++)
	{		
		draw(shapes[i]);
		draw(lines[i]);
	}
	
	
}

void game_window::run()
{	
	if (show_frame_rate_)
		f_per_sec_.count();
	float angle_x = 0;
	float angle_y = 0;
	mesh temp(calculate_points(angle_x, angle_y));
	const Color	fill(50, 50, 50),
			outline(Color::White);
	while (isOpen())
	{
		Event event;
		while (pollEvent(event))
			// Пользователь нажал на «крестик» и хочет закрыть окно ?
			if (event.type == Event::Closed)
				// тогда закрываем его
				close();
		
		clear();

		draw_triangle(
			temp.to_triangle_vertex_array(fill),
			temp.to_line_vertex_array(outline));
		
		const float fps= f_per_sec_.get_average_frame_rate();

		if (fps > 0)
		angle_x += 1000.0f / fps;
		angle_y = angle_x;
		temp = calculate_points(angle_x, angle_y);

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

void game_window::init_cube(vector<Vector3f> points, vector<triangle> tr, const Vector3f& scale_point)
{
	cube_ = mesh(points, tr);
	cube_.scale(scale_point);
	
}
