#pragma once
#include "text_renderer.h"

class frame_rate_renderer : public text_renderer
{
public:
	frame_rate_renderer(const frame_rate_renderer& other)
		: text_renderer(other)
	{
	}

	frame_rate_renderer(frame_rate_renderer&& other) noexcept
		: text_renderer(std::move(other))
	{
	}

	frame_rate_renderer& operator=(const frame_rate_renderer& other)
	{
		if (this == &other)
			return *this;
		text_renderer::operator =(other);
		return *this;
	}

	frame_rate_renderer& operator=(frame_rate_renderer&& other) noexcept
	{
		if (this == &other)
			return *this;
		text_renderer::operator =(std::move(other));
		return *this;
	}

	const Text* to_text(frame_rate& frame_rate) const;

	explicit frame_rate_renderer(font_text * value);
	explicit frame_rate_renderer(const text_renderer& other);
	frame_rate_renderer() :text_renderer() {};
};

