#include "TextRenderer.h"

FontText* TextRenderer::getFontText() const
{
	return fontText;
}

Text* TextRenderer::toText(string someString)
{
	String stringText(someString);

	fontText->text->setString(stringText);

	return fontText->text;
}

TextRenderer TextRenderer::createAnyTextRenderer(const string& fontFileName, unsigned int fontSize, float rotation, float scale, const Vertex& textVertex)
{
	FontText* result = new FontText{};
	result->font = new Font{};
	if (!result->font->loadFromFile(fontFileName))
	{
		cout << "Could not load file";
	}
	result->text = new Text{ "", *(result->font), fontSize };
	result->text->setPosition(textVertex.position);
	result->text->setScale(scale, scale);

    return TextRenderer(result);
}
