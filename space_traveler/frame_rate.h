#pragma once
#include "engine_math.h"
using namespace engine_math;
class frame_rate
{
	int frame_counter_ = 0;
	int average_frame_rate_ = 0;
	int minimum_frame_rate_ = 0;
	int maximum_frame_rate_ = 0;

	int f_rate_values_[3] = {0};
	int cur_index_ = 0;

	Mutex mtx_;
	Thread frame_rate_thread_;	

	void frame_rate_method();
	void control_array_index();
	void calculate_frames();

public :
	frame_rate()
		:
	f_rate_values_(),
	frame_rate_thread_(&frame_rate::frame_rate_method, this)
		
	{
		
	}
	frame_rate(const frame_rate& other) 
		:
		f_rate_values_(),
	frame_rate_thread_(&frame_rate::frame_rate_method, this){
		frame_counter_ = other.frame_counter_;
	}
	~frame_rate()
	{
		this->frame_rate_thread_.terminate();
	}
	
	frame_rate& operator++();
	frame_rate operator++(int);
	void count();
	void stop();

	int get_average_frame_rate() ;
	int get_minimum_frame_rate() ;
	int get_maximum_frame_rate() ;


};

