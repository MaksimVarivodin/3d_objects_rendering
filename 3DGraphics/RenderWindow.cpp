#include "RenderWindow.h"

void RenderWindow::run()
{
    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(_renderer);

        SDL_RenderPresent(_renderer);
    }

    
}
