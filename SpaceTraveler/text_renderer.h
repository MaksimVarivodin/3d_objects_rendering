#pragma once
#include "frame_rate.h"
struct font_text {
	Font* font;
	Text* text;
};
class text_renderer
{
protected:

	font_text* font_text_;

public:
	font_text* get_font_text()const;

	const Text* to_text(const string& some_string) const;

	static text_renderer create_any_text_renderer(
		const string& font_file_name =  R"(\arial\arial_light.ttf)",
		const unsigned& font_size = 14,
		const float& rotation = 0,
		const float& scale = 1.f,
		const Vertex& text_vertex = Vertex(Vector2f(20, 20)));


	explicit text_renderer(font_text* font_text)
		: font_text_(font_text)
	{
	};
	text_renderer() :font_text_(nullptr) {};
};

