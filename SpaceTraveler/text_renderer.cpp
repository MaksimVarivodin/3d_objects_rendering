#include "text_renderer.h"

bool text_renderer::is_font_text_empty() const
{
	bool empty = font_text_ == nullptr;

	if (empty)
		cout << "font_text_ is nullptr" << endl;

	return empty;
}

bool text_renderer::is_text_empty() const
{
	bool empty = font_text_->text == nullptr;

	if (empty)
		cout << "font_text_->text is nullptr" << endl;

	return empty;
}

bool text_renderer::is_font_empty() const
{
	bool empty = font_text_->font == nullptr;

	if (empty)
		cout << "font_text_->font is nullptr" << endl;

	return empty;
}

font_text* text_renderer::get_font_text() const
{
	if (!is_font_text_empty() && !is_font_empty() && !is_text_empty()) {

		font_text* font_text_copy = new font_text{};

		font_text_copy->font = new Font{ *(font_text_->font) };

		font_text_copy->text = new Text{ *(font_text_->text) };

		font_text_copy->text->setFont(*(font_text_copy->font));

		return font_text_;
	}
	return nullptr;
}

const Text* text_renderer::to_text(const string& some_string) const
{
	if (!is_font_text_empty() && !is_text_empty()) {

		const String string_text(some_string);

		font_text_->text->setString(string_text);

		return font_text_->text;
	}
	return nullptr;
}

void text_renderer::load_font(const string& file_name_path)
{
	if (is_font_text_empty())
		font_text_ = new font_text{};

	if (is_font_empty())
		font_text_->font = new Font{};

	string full_font_file_path = get_current_dir() + file_name_path;

	if (!font_text_->font->loadFromFile(full_font_file_path))
		cout << "Could not load font file, path: " + full_font_file_path;

}

void text_renderer::set_text_properties(const Vertex& vertex_,
	const unsigned& font_size,
	const Uint32& font_style,
	const float& scale,
	const float& rotation)
{
	if (!is_font_text_empty() && !is_font_empty() && !is_text_empty()) {

		font_text_->text->setPosition(vertex_.position);
		font_text_->text->setFillColor(vertex_.color);

		font_text_->text->setCharacterSize(font_size);

		font_text_->text->setStyle(font_style);

		font_text_->text->setScale({ scale, scale });

		font_text_->text->setRotation(rotation);
	}

}

text_renderer text_renderer::load_text_renderer(const string& font_file_path)
{

	text_renderer new_text_renderer_{ new font_text{} };

	new_text_renderer_.load_font(font_file_path);

	new_text_renderer_.font_text_->text = new Text{ "", *(new_text_renderer_.font_text_->font) };

	return new_text_renderer_;
}
