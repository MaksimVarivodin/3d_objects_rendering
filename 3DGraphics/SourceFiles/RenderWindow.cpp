#include "..\headers\RenderWindow.h"

void RenderWindow::run()
{
    SDL_Event event;
    bool running = true;
    int counter = 0;
    int index = 0;
    while (running) {
        if (counter == 180) {
            index++;
			counter = 0;
			if (index >= _render3D.size()) {
				index = 0;
			}
        }
        SDL_SetRenderDrawColor(
            _renderer,
            _backgroundColor.r,
            _backgroundColor.g, 
            _backgroundColor.b, 
            _backgroundColor.a);
        SDL_RenderClear(_renderer);
        SDL_RenderPresent(_renderer);
        _render3D[index].runThreads();
        counter++;
       
        Sleep(0);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
        }       
    }

    
}




RenderWindow::RenderWindow(const SDL_Color& _backgroundColor, const vector<Render3D>& _render3D, SDL_Window* _window, SDL_Renderer* _renderer)
    : _backgroundColor(_backgroundColor), _render3D(_render3D), _window(_window), _renderer(_renderer)
{
}
