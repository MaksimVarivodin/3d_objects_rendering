#include "..\headers\RenderWindow.h"

void RenderWindow::run()
{
    SDL_Event event;
    bool running = true;
    while (running) {
        
        SDL_SetRenderDrawColor(
            _renderer,
            _backgroundColor.r,
            _backgroundColor.g, 
            _backgroundColor.b, 
            _backgroundColor.a);
        SDL_RenderClear(_renderer);
        SDL_RenderPresent(_renderer);
        _render3D.renderObjects();
        //Sleep(50);
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
        }       
    }

    
}
