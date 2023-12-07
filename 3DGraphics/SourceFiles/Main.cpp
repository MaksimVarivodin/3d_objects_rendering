#include "..\headers\RenderWindow.h"

// ширина экрана
const int SCREEN_WIDTH = 1920;

// высота экрана
const int SCREEN_HEIGHT = 1080;

// цвета
struct Colors {
    SDL_Color Black{ 0, 0, 0, 225 };
    SDL_Color White{ 255, 255, 255, 255 };
}colors;

// координаты 3Д объектов на экране
vector<Point> targetCoordinates = {
    {SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, 0},
    {SCREEN_WIDTH / 4.0f - 250, SCREEN_HEIGHT / 4.0f, 0},
    {SCREEN_WIDTH / 4.0f + 250, SCREEN_HEIGHT / 4.0f, 0},
    {SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f - 250, 0},
    {SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f+ 250, 0}

};

// изначальный поворот 3Д объектов
vector<Point> objectRotations = {
    {180},
    {180},
    {180},
    {180},
    {180}

};

// дельты поворота 3Д объектов
vector<Point>objectRotationDeltas = {
    {3, 2},
    {2, 3},
    {3},
    {2},
    {0, 1, 3}
};

// функция мейн
int SDL_main(int argc, char** args) {

    // задание ширины отображаемого окна
    int width= SCREEN_WIDTH * 0.5;
	int height = SCREEN_HEIGHT * 0.5;

    // создание окна (из библиотеки SDL)
    SDL_Window* _window = SDL_CreateWindow(
        "Simple 3D object render",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    // создание рендерера - отрисовщик (из библиотеки SDL)
    // управляет графикой в окне
    SDL_Renderer* _renderer = SDL_CreateRenderer(_window,
        -1,
        SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);


	// инициализация рендера 
    Render3D render3D = Render3D{
        // создаю 1 куб и 4 пирамиды
        vector<Object3D>{
            Object3D::Cube(50, colors.White),
            Object3D::Pyramid(25, colors.White),
            Object3D::Pyramid(25, colors.White),
            Object3D::Pyramid(25, colors.White),
            Object3D::Pyramid(25, colors.White)  },
        // расстояние от екрана до центра координат фигур
        500,
        // передаю изначальный угол фигур
        objectRotations,
		// передаю дельты поворота
        objectRotationDeltas,
        // передаю расположение фигур на екране
        targetCoordinates,
        // передаю рендерер - отрисовщик (из библиотеки SDL)
        _renderer};

    // инициализация настроек окна
    RenderWindow winRen = {
        // цвет фона окна
            colors.Black,
            // мой 3д рендер
            render3D,
            // передаю окно (из библиотеки SDL)
            _window,
            // передаю рендерер - отрисовщик (из библиотеки SDL)
            _renderer
    };

    // запуск программы
    winRen.run();

    return 0;
}