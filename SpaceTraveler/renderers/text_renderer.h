#pragma once
#include "..\features\frame_rate.h"
struct font_text {
	Font* font = nullptr;
	Text* text = nullptr;
};
class text_renderer
{
protected:

	font_text* font_text_ = nullptr;

public:
	bool is_font_text_empty() const;
	bool is_text_empty() const;
	bool is_font_empty() const;

	font_text* get_font_text()const;
	const Text* to_text(const string& some_string) const;

	void load_font(const string& file_name_path);
	void set_text_properties(
		const Vertex& location = Vertex(Vector2f(-960, -540)),
		const unsigned& font_size = 20,
		const Uint32 & font_style = Text::Bold,
		const float& scale = 1.f,
		const float& rotation = 0		
		);

	static text_renderer load_text_renderer(const string& font_file_path);


	text_renderer(font_text* font_text)
		: font_text_(font_text)
	{
	};

	text_renderer(const text_renderer& t_r):text_renderer(t_r.get_font_text()){};	
	text_renderer() :text_renderer(nullptr) {};
	~text_renderer()
	{
		font_text_->text->~Text();
		font_text_->font->~Font();
		delete font_text_;
	};
};

