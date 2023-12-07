#include "..\headers\RenderWindow.h"

// ������ ������
const int SCREEN_WIDTH = 1920;

// ������ ������
const int SCREEN_HEIGHT = 1080;

// �����
struct Colors {
    SDL_Color Black{ 0, 0, 0, 225 };
    SDL_Color White{ 255, 255, 255, 255 };
}colors;

// ���������� 3� �������� �� ������
vector<Point> targetCoordinates = {
    {SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, 0},
    {SCREEN_WIDTH / 4.0f - 250, SCREEN_HEIGHT / 4.0f, 0},
    {SCREEN_WIDTH / 4.0f + 250, SCREEN_HEIGHT / 4.0f, 0},
    {SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f - 250, 0},
    {SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f+ 250, 0}

};

// ����������� ������� 3� ��������
vector<Point> objectRotations = {
    {180},
    {180},
    {180},
    {180},
    {180}

};

// ������ �������� 3� ��������
vector<Point>objectRotationDeltas = {
    {3, 2},
    {2, 3},
    {3},
    {2},
    {0, 1, 3}
};

// ������� ����
int SDL_main(int argc, char** args) {

    // ������� ������ ������������� ����
    int width= SCREEN_WIDTH * 0.5;
	int height = SCREEN_HEIGHT * 0.5;

    // �������� ���� (�� ���������� SDL)
    SDL_Window* _window = SDL_CreateWindow(
        "Simple 3D object render",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    // �������� ��������� - ���������� (�� ���������� SDL)
    // ��������� �������� � ����
    SDL_Renderer* _renderer = SDL_CreateRenderer(_window,
        -1,
        SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);


	// ������������� ������� 
    Render3D render3D = Render3D{
        // ������ 1 ��� � 4 ��������
        vector<Object3D>{
            Object3D::Cube(50, colors.White),
            Object3D::Pyramid(25, colors.White),
            Object3D::Pyramid(25, colors.White),
            Object3D::Pyramid(25, colors.White),
            Object3D::Pyramid(25, colors.White)  },
        // ���������� �� ������ �� ������ ��������� �����
        500,
        // ������� ����������� ���� �����
        objectRotations,
		// ������� ������ ��������
        objectRotationDeltas,
        // ������� ������������ ����� �� ������
        targetCoordinates,
        // ������� �������� - ���������� (�� ���������� SDL)
        _renderer};

    // ������������� �������� ����
    RenderWindow winRen = {
        // ���� ���� ����
            colors.Black,
            // ��� 3� ������
            render3D,
            // ������� ���� (�� ���������� SDL)
            _window,
            // ������� �������� - ���������� (�� ���������� SDL)
            _renderer
    };

    // ������ ���������
    winRen.run();

    return 0;
}