#include "FrameRateRenderer.h"

Text* FrameRateRenderer::toText( FrameRate& frameRate)
{
	String stringText(
		"Avg: " + to_string(frameRate.getAverageFrameRate())+"\n"+
		"Max: " + to_string(frameRate.getMaximumFrameRate())+"\n"+
		"Min: " + to_string(frameRate.getMinimumFrameRate())
	);

	return TextRenderer::toText(stringText);
}

FrameRateRenderer::FrameRateRenderer(FontText * value)
{
	this->fontText = value;
}

FrameRateRenderer::FrameRateRenderer(const TextRenderer& other)
{
	this->fontText = other.getFontText();
	this->fontText->text->setStyle(Text::Bold);
}



