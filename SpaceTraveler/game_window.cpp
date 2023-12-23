#pragma once

#include "game_window.h"


void game_window::run()
{	
	if (show_frame_rate_)
		f_per_sec_.count();


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

