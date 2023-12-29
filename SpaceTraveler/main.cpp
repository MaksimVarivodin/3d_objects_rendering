#include "game_window.h"
constexpr int MAXIMUM_FRAME_RATE = 5000;
//int WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
int main()
{

	//game_window win(true, 	VideoMode::getDesktopMode(), "Space Traveler", Style::Default);
	//game_window win(true, 	VideoMode::getDesktopMode(), "Space Traveler", Style::Fullscreen);
	//game_window win(true, 	VideoMode(1080, 1080), "Space Traveler", Style::Default);
	//game_window win(MAXIMUM_FRAME_RATE, VideoMode::getDesktopMode(),"Space Traveler", Style::Fullscreen);
	game_window win(MAXIMUM_FRAME_RATE, VideoMode::getDesktopMode(),"Space Traveler", Style::Default);
	win.run();
	return 0;
}