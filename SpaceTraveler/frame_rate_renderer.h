#pragma once
#include "text_renderer.h"

class frame_rate_renderer : public text_renderer
{

public:
	const Text* to_text(frame_rate& frame_rate) const;

	explicit frame_rate_renderer(font_text * value);
	explicit frame_rate_renderer(const text_renderer& other);
	frame_rate_renderer() :text_renderer() {};
};

