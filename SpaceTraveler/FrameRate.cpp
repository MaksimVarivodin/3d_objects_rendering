#include "FrameRate.h"

void FrameRate::frameRateMethod()
{	
	while (true) {
		// ����� ������� 24 ������ � ������� 
		// ���������� ������� �� 0,024-��� ������� 
		// ��� �� 41,(6) ������������ 
		// ��� �� 41667 ������������
		// ������ ���������
		sleep(microseconds(41667));

		Lock lock(mtx);	

		fRateValues[curIndex] = frameCounter * 24;

		calculateFrames();

		controlArrayIndex();

		frameCounter = 0;

	}
	
}

void FrameRate::controlArrayIndex()
{	
	if (curIndex == 2) 
		this->curIndex = 0;
	else
		this->curIndex++;
}

void FrameRate::calculateFrames()
{
	if (curIndex == 2) {
		averageFrameRate = findAverage(fRateValues[0], fRateValues[1], fRateValues[2]);
		minimumFrameRate = findMinimum(fRateValues[0], fRateValues[1], fRateValues[2]);
		maximumFrameRate = findMaximum(fRateValues[0], fRateValues[1], fRateValues[2]);
	}
	
}

FrameRate& FrameRate::operator++()
{
	mtx.lock();
	frameCounter++;
	FrameRate& link = *this;
	mtx.unlock();
	return link;
}

FrameRate FrameRate::operator++(int)
{
	mtx.lock();
	FrameRate temp = *this;
	mtx.unlock();
	this->operator++();
	return temp;
}

void FrameRate::count()
{
	this->frameRateThread.launch();
}

void FrameRate::stop()
{
	this->frameRateThread.terminate();
}

int FrameRate::getAverageFrameRate() 
{
	mtx.lock();
	int value = averageFrameRate;
	mtx.unlock();
	return value;

}

int FrameRate::getMinimumFrameRate() 
{
	mtx.lock();
	int value = minimumFrameRate;
	mtx.unlock();
	return value;

}

int FrameRate::getMaximumFrameRate() 
{
	mtx.lock();
	int value = maximumFrameRate;
	mtx.unlock();
	return value;
}
