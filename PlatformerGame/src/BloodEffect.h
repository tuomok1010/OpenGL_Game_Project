#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "Effect.h"

class BloodEffect : public Effect
{
public:
	BloodEffect();
	~BloodEffect();

	void Draw(SpriteRenderer& renderer) override;
};