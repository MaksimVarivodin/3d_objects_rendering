#pragma once
#include "Render3D.h"


class RenderWindow
{
	// ���� ����
	SDL_Color _backgroundColor;
	// ������
	Render3D _render3D;
	// ���� (�� ���������� SDL2)
	SDL_Window* _window;
	// ������ (�� ���������� SDL2)
	SDL_Renderer* _renderer;

public:
	// �������� ������� ������� ���������
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

