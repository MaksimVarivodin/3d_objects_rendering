#pragma once
#include "Render3D.h"
struct Colors {
	SDL_Color Black{ 0, 0, 0, 225 };
	SDL_Color White{ 255, 255, 255, 255 };
}colors;

class RenderWindow
{
	int _width;
	int _height;
	SDL_Color _backgroundColor;
	Render3D _render3D;
	SDL_Window* _window;
	SDL_Renderer* _renderer;

public:

	[[nodiscard]] int width() const {return _width;	};
	[[nodiscard]] int height() const { return _height; };
	SDL_Color backgroundColor() { return _backgroundColor; };
	void run();

	RenderWindow(
		int _width,
		int _height,
		const SDL_Color& _backgroundColor,
		const Render3D& _render3D,
		SDL_Window* _window,
		SDL_Renderer* _renderer)
		: _width(_width),
          _height(_height),
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

