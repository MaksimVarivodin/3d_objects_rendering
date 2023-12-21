#include "game_window.h"
constexpr int MAXIMUM_FRAME_RATE = 5000;
//int WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
int main()
{

	game_window win(true,
		VideoMode::getDesktopMode(),
		"Space Traveler", Style::Fullscreen);
	//game_window win(MAXIMUM_FRAME_RATE,VideoMode(1080, 1080),	"Space Traveler");
	vector<Vector3f> cube_vertices = {
		/*0*/{-1, -1, -1},
		/*1*/{+1, -1, -1},
		/*2*/{-1, +1, -1},
		/*3*/{+1, +1, -1},
		/*4*/{-1, -1, +1},
		/*5*/{+1, -1, +1},
		/*6*/{-1, +1, +1},
		/*7*/{+1, +1, +1}
	};
	const vector<triangle> cube_triangles =
	{
		// front
		{0, 2, 3},	{0, 3, 1},
		// back
		{5, 7, 6},	{5, 6, 4},
		// right
		{4, 6, 2},	{4, 2, 0},
		// left
		{1, 3, 7},	{1, 7, 5},
		// top
		{2, 6, 7},	{2, 7, 3},
		// bottom
		{4, 0, 1},	{4, 1, 5}

	};
	//vector<Vector3f> cube_vertices = {
	//	/*0*/{0, 0, 0},
	//	/*1*/{1, 0, 0},
	//	/*2*/{0, 1, 0},
	//	/*3*/{1, 1, 0},
	//	/*4*/{0, 0, 1},
	//	/*5*/{1, 0, 1},
	//	/*6*/{0, 1, 1},
	//	/*7*/{1, 1, 1}
	//};
	//
	//
	//const vector<triangle> cube_triangles =
	//{
	//	// front
	//	{0, 2, 3},	{0, 3, 1},
	//	// back
	//	{5, 7, 6},	{5, 6, 4},
	//	// right
	//	{4, 6, 2},	{4, 2, 0},
	//	// left
	//	{1, 3, 7},	{1, 7, 5},
	//	// top
	//	{2, 6, 7},	{2, 7, 3},
	//	// bottom
	//	{4, 0, 1},	{4, 1, 5}

	//};
	win.init_cube(
		cube_vertices, 
		cube_triangles
	);
	win.run();
	return 0;
}