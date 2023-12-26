#include "text_renderer.h"

font_text* text_renderer::get_font_text() const
{
	return font_text_;
}

const Text* text_renderer::to_text(const string& some_string) const
{
	const String string_text(some_string);

	font_text_->text->setString(string_text);

	return font_text_->text;
}

text_renderer text_renderer::create_any_text_renderer(
	const string& font_file_name,
	const unsigned& font_size, const float& rotation, const float& scale, const Vertex& text_vertex)
{
	auto* result = new font_text{};
	result->font = new Font{};
	if (!result->font->loadFromFile(font_file_name))
	{
		cout << "Could not load file";
	}
	result->text = new Text{ "", *(result->font), font_size };
	result->text->setPosition(text_vertex.position);
	result->text->setScale(scale, scale);

    return text_renderer(result);
}
