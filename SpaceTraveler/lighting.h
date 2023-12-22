#pragma once
#include "camera.h"
class lighting
{
	Vector3f direction_ = {0, 0, -1};

public:
	lighting()
	{
		direction_ = em_vector_normalization(direction_);
	}
	mesh color_filtering(const mesh & m) const;
};
