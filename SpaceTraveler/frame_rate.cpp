#include "frame_rate.h"

void frame_rate::frame_rate_method()
{	
	while (true) {
		// чтобы сделать 24 замера в секунду 
		// необходимо заснуть на 0,024-ную секунды 
		// или на 41,(6) миллисекунды 
		// или на 41667 микросекунды
		// выбрал последнее
		sleep(microseconds(41667));

		Lock lock(mtx_);	

		f_rate_values_[cur_index_] = frame_counter_ * 24;

		calculate_frames();

		control_array_index();

		frame_counter_ = 0;

	}
	
}

void frame_rate::control_array_index()
{	
	if (cur_index_ == 2) 
		this->cur_index_ = 0;
	else
		this->cur_index_++;
}

void frame_rate::calculate_frames()
{
	if (cur_index_ == 2) {
		average_frame_rate_ = em_find_average(f_rate_values_[0], f_rate_values_[1], f_rate_values_[2]);
		minimum_frame_rate_ = em_find_minimum(f_rate_values_[0], f_rate_values_[1], f_rate_values_[2]);
		maximum_frame_rate_ = em_find_maximum(f_rate_values_[0], f_rate_values_[1], f_rate_values_[2]);
	}
	
}

frame_rate& frame_rate::operator++()
{
	mtx_.lock();
	frame_counter_++;
	frame_rate& link = *this;
	mtx_.unlock();
	return link;
}

frame_rate frame_rate::operator++(int)
{
	mtx_.lock();
	frame_rate temp = *this;
	mtx_.unlock();
	this->operator++();
	return temp;
}

void frame_rate::count()
{
	this->frame_rate_thread_.launch();
}

void frame_rate::stop()
{
	this->frame_rate_thread_.terminate();
}

int frame_rate::get_average_frame_rate() 
{
	mtx_.lock();
	const int value = average_frame_rate_;
	mtx_.unlock();
	return value;

}

int frame_rate::get_minimum_frame_rate() 
{
	mtx_.lock();
	const int value = minimum_frame_rate_;
	mtx_.unlock();
	return value;

}

int frame_rate::get_maximum_frame_rate() 
{
	mtx_.lock();
	const int value = maximum_frame_rate_;
	mtx_.unlock();
	return value;
}
