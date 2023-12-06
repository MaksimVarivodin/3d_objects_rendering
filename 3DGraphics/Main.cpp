#include "Render3D.h"

vector<Point> vertices{
    (0, 0, 0),
    (1, 0, 0),
    (1, 1, 0),
    (0, 1, 0),
    (0, 0, 1),
    (1, 0, 1),
    (1, 1, 1),
    (0, 1, 1)
};
vector<pair<int, int>> sides =
{
    {0, 1},{1, 2},{2, 3},{3, 0},
    {4, 5},{5, 6},{6, 7},{7, 4},
    {0, 4},{1, 5},{2, 6},{3, 7}
};
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;

int SDL_main(int argc, char** args) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return 1;
    }

    SDL_Window* _window = SDL_CreateWindow(
        "Hello, SDL 2!",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH* 0.75,
        SCREEN_HEIGHT*0.75, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer* _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Rect button;
    button.x = (SCREEN_WIDTH - BUTTON_WIDTH) / 2;
    button.y = (SCREEN_HEIGHT - BUTTON_HEIGHT) / 2;
    button.w = BUTTON_WIDTH;
    button.h = BUTTON_HEIGHT;


    return 0;
}