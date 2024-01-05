#include "game_window.h"

void game_window::run()
{

	setView(View{Vector2f{0, 0}, Vector2f{1920, 1080}});

	set_debug_mode();

	mesh_loader<float> m_l;

	m_l.file_name_ = "teapot";

	// initializing variables for transformation function

	mesh<float> object_ = m_l.load();

	point<float> object_degrees_{ 0.f, 0.f, 0.f };

	point<float> object_move_{0.f, 0.f, 7.f};

	camera<float> camera_;

	light<float> light_( {0.f, 0.f, -1.f});

	point<float> object_scale_{ 0.5f * getSize().x,	0.5f * getSize().y,	1.f	};

	Vector2f coordinate_inversion{1.f, -1.f};	



	if (show_frame_rate_)
		frames_per_sec_.count();


	while (isOpen())
	{
		Event event;
		while (pollEvent(event))
			// Пользователь нажал на «крестик» и хочет закрыть окно ?
			if (event.type == Event::Closed ||(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) 
				// тогда закрываем его
			{
				frames_per_sec_.stop();
				close();
			}
			

		clear();
		
		

		float elapsed_time = frames_per_sec_.get_elapsed_time();
		object_degrees_ += {0, elapsed_time, elapsed_time};	

		auto transformed_object = trnsform<float>::transformation(
			object_,
			em_angle_to_radian<float>(object_degrees_),
			object_move_,
			object_scale_,
			camera_,
			light_,			
			coordinate_inversion
		);

		draw(transformed_object.to_filled_triangles());

		if (debug_mode_)
			draw(transformed_object.to_outline_triangles());


		if (show_frame_rate_) {
			draw(*(text_renderer_.to_text(frames_per_sec_.to_string())));
			frames_per_sec_++;
		}

		display();
		transformed_object.~mesh();
	}
}

void game_window::set_frame_rate_show(bool value)
{
	this->show_frame_rate_ = value;
	if (show_frame_rate_)
		frames_per_sec_.count();
	else
		frames_per_sec_.stop();
}

