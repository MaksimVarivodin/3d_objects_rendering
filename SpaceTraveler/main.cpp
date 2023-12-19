#include "game_window.h"
constexpr int MAXIMUM_FRAME_RATE = 5000;
//int WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
int main()
{

	game_window win(MAXIMUM_FRAME_RATE);
	vector<Vector3f> cube_vertices = {
		/*0*/{-1, -1, -1},
		/*1*/{+1, -1, -1},
		/*2*/{+1, +1, -1},
		/*3*/{-1, +1, -1},
		/*4*/{-1, -1, +1},
		/*5*/{+1, -1, +1},
		/*6*/{+1, +1, +1},
		/*7*/{-1, +1, +1}
	};
	const vector<triangle> cube_triangles =
	{
		// front
		{0, 3, 2},
		{0, 2, 1},

		// back
		{5, 6, 7},
		{5, 7, 4},

		// right
		{1, 2, 6},
		{1, 6, 5},

		// left
		{4, 7, 3},
		{4, 3, 0},

		// top
		{3, 7, 6},
		{3, 7, 2},

		// bottom
		{4, 5, 1},
		{4, 1, 0}

	};
	win.init_cube(
		cube_vertices, 
		cube_triangles,
		win.getSize().x/6,
		win.getSize().y/3,
		1
	);
	win.run();
	return 0;
}