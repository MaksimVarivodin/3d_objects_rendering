#include "..\headers\RenderWindow.h"

// ширина экрана
const int SCREEN_WIDTH = 1920;

// высота экрана
const int SCREEN_HEIGHT = 1080;
float width = SCREEN_WIDTH * 0.95;
float height = SCREEN_HEIGHT* 0.95;
// цвета
struct Colors {
    SDL_Color Black{ 0, 0, 0, 225 };
    SDL_Color White{ 255, 255, 255, 255 };
    SDL_Color Red{255, 0, 0, 255};
    SDL_Color Green{ 0, 255, 0, 255 };
    SDL_Color Blue{ 0, 0, 255, 255 };
}colors;



// функция мейн
int SDL_main(int argc, char** args) {

    // координаты 3Д объектов на экране
    vector<Point> targetCoordinates = {

        {width / 2.0f,         height / 2.0f, 0},
        {width / 2.0f,         height / 2.0f, 0},
        {width / 2.0f,         height / 2.0f, 0},

        {width / 2.0f,         height / 2.0f, 0},
        {width / 2.0f,         height / 2.0f, 0},        
        {width / 2.0f,         height / 2.0f, 0}
    };

    // изначальный поворот 3Д объектов
    vector<Point> objectRotations = {

        {},
        {0, 30},

        {0, 60},

        {0, 90},

        {0, 120},

        {0, 150}

    };

    // дельты поворота 3Д объектов
    vector<Point>objectRotationDeltas = {

        {0, 2},
        {0, 2},
        {0, 2},         
        {0, 2},
        {0, 2},
        {0, 2}

    };
    Object3D objectGreen = Object3D::KohStar(
        { 0, 0, 0 },
        300,
        3,
        3,
        -3,
        3,
        colors.Green),
        objectBlue = Object3D::KohStar(
            { 0, 0, 0 },
            300,
            3,
            2,
            -6,
            6,
            colors.Blue),
        objectRed = Object3D::KohStar(
            { 0, 0, 0 },
            200,
            3,
            1,
            -12,
            12,
            colors.Red) ,
        objectWhite = Object3D::KohStar(
            { 0, 0, 0 },
            200,
            3,
            0,
            -24,
            24,
            colors.White);

    vector<Object3D> GreenObjects = {
       objectGreen,
        objectGreen,
        objectGreen,
        objectGreen,
        objectGreen,
        objectGreen

       

    };
    vector<Object3D> RedObjects = {
         objectRed,
        objectRed,
        objectRed,
        objectRed,
        objectRed,
        objectRed
    };
    vector<Object3D> BlueObjects = {
        objectBlue,
        objectBlue,
        objectBlue,
        objectBlue,
        objectBlue,
        objectBlue
    };
    vector<Object3D> WhiteObjects = {
        objectWhite,
        objectWhite,
        objectWhite,
        objectWhite,
        objectWhite,
        objectWhite
    };

    // создание окна (из библиотеки SDL)
    SDL_Window* _window = SDL_CreateWindow(
        "Simple 3D object render",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_MAXIMIZED );
    // создание рендерера - отрисовщик (из библиотеки SDL)
    // управляет графикой в окне
    SDL_Renderer* _renderer = SDL_CreateRenderer(_window,
        -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC );


	// инициализация рендера 
    vector<Render3D> render3D = { 
        {
        GreenObjects,
        // расстояние от екрана до центра координат фигур
        500,
        // передаю изначальный угол фигур
        objectRotations,
        // передаю дельты поворота
        objectRotationDeltas,
        // передаю расположение фигур на екране
        targetCoordinates,
        // передаю рендерер - отрисовщик (из библиотеки SDL)
        _renderer} ,
         {
        BlueObjects,
        // расстояние от екрана до центра координат фигур
        500,
        // передаю изначальный угол фигур
        objectRotations,
        // передаю дельты поворота
        objectRotationDeltas,
        // передаю расположение фигур на екране
        targetCoordinates,
        // передаю рендерер - отрисовщик (из библиотеки SDL)
        _renderer} ,
        {
        RedObjects,
            // расстояние от екрана до центра координат фигур
            500,
            // передаю изначальный угол фигур
            objectRotations,
            // передаю дельты поворота
            objectRotationDeltas,
            // передаю расположение фигур на екране
            targetCoordinates,
            // передаю рендерер - отрисовщик (из библиотеки SDL)
            _renderer},
             {
        WhiteObjects,
        // расстояние от екрана до центра координат фигур
        500,
        // передаю изначальный угол фигур
        objectRotations,
        // передаю дельты поворота
        objectRotationDeltas,
        // передаю расположение фигур на екране
        targetCoordinates,
        // передаю рендерер - отрисовщик (из библиотеки SDL)
        _renderer} 
    };

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