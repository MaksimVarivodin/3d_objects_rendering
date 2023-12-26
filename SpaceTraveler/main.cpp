#include "game_window.h"
constexpr int MAXIMUM_FRAME_RATE = 5000;
//int WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
int main()
{
	
	mesh_loader<float> m_l;

	mesh<float> spaceship = m_l.load();
	m_l.file_name_ = "teapot";
	mesh<float> teapot = m_l.load();

	game_window win(true, 	VideoMode::getDesktopMode(), "Space Traveler", Style::Default);
	//game_window win(true, 	VideoMode::getDesktopMode(), "Space Traveler", Style::Fullscreen);
	//game_window win(true, 	VideoMode(1080, 1080), "Space Traveler", Style::Default);
	//game_window win(MAXIMUM_FRAME_RATE, VideoMode::getDesktopMode(),"Space Traveler", Style::Fullscreen);
	win.run();
	return 0;
}