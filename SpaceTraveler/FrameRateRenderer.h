#pragma once
#include "TextRenderer.h"

class FrameRateRenderer : public TextRenderer
{

public:

	Text* toText(FrameRate& frameRate);	
	
	FrameRateRenderer(FontText * value);
	FrameRateRenderer(const TextRenderer& other);
	FrameRateRenderer() :TextRenderer() {};
};

