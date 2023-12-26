//#include "game_window.h"
#include "matrix.h"
constexpr int MAXIMUM_FRAME_RATE = 5000;

//int WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
int main()
{
	//mesh_loader<float> loader;
	//mesh<float>* object = loader.load();

	matrix<float> x = matrix<float>::x_rotation(0.5, 4, 4);
	matrix<float>::print(cout, x);
	matrix<float> y = matrix<float>::y_rotation(0.5, 4, 4);
	//y << (cout);
	y*= x;

	//game_window win(true, 	VideoMode::getDesktopMode(), "Space Traveler", Style::Default);
	//game_window win(true, 	VideoMode::getDesktopMode(), "Space Traveler", Style::Fullscreen);
	//game_window win(true, 	VideoMode(1080, 1080), "Space Traveler", Style::Default);
	//game_window win(MAXIMUM_FRAME_RATE, VideoMode::getDesktopMode(),"Space Traveler", Style::Fullscreen);
	//win.run();

	//delete object;
	return 0;
}