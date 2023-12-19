#include "frame_rate_renderer.h"

const Text* frame_rate_renderer::to_text(frame_rate& frame_rate) const
{
	const String string_text(
		"Avg: " + to_string(frame_rate.get_average_frame_rate())+"\n"+
		"Max: " + to_string(frame_rate.get_maximum_frame_rate())+"\n"+
		"Min: " + to_string(frame_rate.get_minimum_frame_rate())
	);

	return text_renderer::to_text(string_text);
}

frame_rate_renderer::frame_rate_renderer(font_text * value)
{
	this->font_text_ = value;
}

frame_rate_renderer::frame_rate_renderer(const text_renderer& other)
{
	this->font_text_ = other.get_font_text();
	this->font_text_->text->setStyle(Text::Bold);
}



