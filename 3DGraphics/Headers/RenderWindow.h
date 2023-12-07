#pragma once
#include "Render3D.h"


class RenderWindow
{
	// цвет фона
	SDL_Color _backgroundColor;
	// рендер
	Render3D _render3D;
	// окно (из библиотеки SDL2)
	SDL_Window* _window;
	// рендер (из библиотеки SDL2)
	SDL_Renderer* _renderer;

public:
	// основная функция запуска программы
	void run();

	RenderWindow(
		const SDL_Color& _backgroundColor,
		const Render3D& _render3D,
		SDL_Window* _window,
		SDL_Renderer* _renderer):
          _backgroundColor(_backgroundColor),
          _render3D(_render3D),
          _window(_window),
          _renderer(_renderer)
	{
	};
	~RenderWindow()
	{
		SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(_window);
		SDL_Quit();
	};
};

