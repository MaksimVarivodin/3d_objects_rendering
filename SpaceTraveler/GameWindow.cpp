#include "GameWindow.h"

void GameWindow::run()
{	
	if (showFrameRate)
		fPerSec.count();
	while (isOpen())
	{
		Event event;
		while (pollEvent(event))
			// ������������ ����� �� �������� � ����� ������� ���� ?
			if (event.type == Event::Closed)
				// ����� ��������� ���
				close();
		
		clear();
		if (showFrameRate) {
			draw(*(fRRenderer.toText(fPerSec)));
			fPerSec++;
		}			
		display();
	}
}

void GameWindow::setFrameRateShow(bool value)
{
	this->showFrameRate	= value;
	if (showFrameRate)
		fPerSec.count();
	else
		fPerSec.stop();
}

void GameWindow::initCube(vector<Triangle> tr)
{
	cube = Mesh(tr);
}
