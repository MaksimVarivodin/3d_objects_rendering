#include "game_window.h"

void game_window::run()
{
	
	point<float> degrees{ 0, 0, 180};
	point<float> angle = em_angle_to_radian<float>(degrees);
	mesh_loader<float> m_l;
	m_l.file_name_ = "teapot";
	mesh<float> spaceship = m_l.load();
	light<float> l(point<float>{0, 0, -1});
	camera<float> cam;
	
	mesh<float> temp = trnsform<float>::transformation(
		spaceship,
		cam,
		l,
		point<float>{1, 1, 0},
		point<float>{
		0.5f * getSize().x,
			0.5f * getSize().y,
			1.f
	},
		angle
	);


	if (show_frame_rate_)
		f_per_sec_.count();


	while (isOpen())
	{
		Event event;
		while (pollEvent(event))
			// Пользователь нажал на «крестик» и хочет закрыть окно ?
			if (event.type == Event::Closed ||
				(event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape))) {
				// тогда закрываем его
				close();
			}


		clear();
		draw(temp.to_draw_triangles());

		const float fps = f_per_sec_.get_average_frame_rate();

		if (fps > 0)
		{
			degrees += point<float>{

					0,
					fps / 100.0f,
					/*fps / 100.0f*/
					fps / 1000.0f
			
			};
		}
		angle = em_angle_to_radian<float>(degrees);
		temp = trnsform<float>::transformation(
			spaceship,
			cam,
			l,
			point<float>{1, 1, 0},
			point<float>{
				0.5f * getSize().x,
				0.5f * getSize().y,
				1.f
		},
			angle
		);
		if (show_frame_rate_) {
			draw(*(f_r_renderer_.to_text(f_per_sec_)));
			f_per_sec_++;
		}
		display();

	}
}

void game_window::set_frame_rate_show(bool value)
{
	this->show_frame_rate_ = value;
	if (show_frame_rate_)
		f_per_sec_.count();
	else
		f_per_sec_.stop();
}

