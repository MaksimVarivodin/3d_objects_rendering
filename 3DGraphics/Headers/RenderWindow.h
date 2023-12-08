#pragma once
#include "Render3D.h"


class RenderWindow
{
	// ���� ����
	SDL_Color _backgroundColor;
	// ������
	vector<Render3D> _render3D;
	// ���� (�� ���������� SDL2)
	SDL_Window* _window;
	// ������ (�� ���������� SDL2)
	SDL_Renderer* _renderer;

public:
	// �������� ������� ������� ���������
	void run();

	
	~RenderWindow()
	{
		SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(_window);
		SDL_Quit();
	};

	RenderWindow() = default;
	
	RenderWindow(
		const SDL_Color& _backgroundColor, 
		const vector<Render3D>& _render3D,
		SDL_Window* _window,
		SDL_Renderer* _renderer);
};

