#pragma once
#include "Mesh.h"
class FrameRate
{
	int frameCounter = 0;
	int averageFrameRate = 0;
	int minimumFrameRate = 0;
	int maximumFrameRate = 0;

	int fRateValues[3] = {0};
	int curIndex = 0;

	Mutex mtx;
	Thread frameRateThread;	

	void frameRateMethod();
	void controlArrayIndex();
	void calculateFrames();

public :
	FrameRate()
		:frameRateThread(&FrameRate::frameRateMethod, this),
		fRateValues()
	{
		
	}
	FrameRate(const FrameRate& other) 
		:frameRateThread(bind(&FrameRate::frameRateMethod, this)),
		fRateValues(){
		frameCounter = other.frameCounter;
	}
	~FrameRate()
	{
		this->frameRateThread.terminate();
	}
	
	FrameRate& operator++();
	FrameRate operator++(int);
	void count();
	void stop();

	int getAverageFrameRate() ;
	int getMinimumFrameRate() ;
	int getMaximumFrameRate() ;


};

