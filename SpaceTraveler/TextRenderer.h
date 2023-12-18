#pragma once
#include "FrameRate.h"
struct FontText {
	Font* font;
	Text* text;
};
class TextRenderer
{
protected:

	FontText* fontText;

public:
	FontText* getFontText()const;

	Text* toText(string someString);

	static TextRenderer createAnyTextRenderer(
		const string& fontFileName = "C:\\Users\\maksy\\Documents\\Projects\\c++\\3DGraphics\\Debug\\arial\\arial_light.ttf",
		unsigned int fontSize = 14,
		float rotation = 0,
		float scale = 1.f,
		const Vertex& textVertex = Vertex(Vector2f(20, 20)));	


	TextRenderer(FontText* fontText)
		: fontText(fontText)
	{
	};
	TextRenderer() :fontText(nullptr) {};
};

