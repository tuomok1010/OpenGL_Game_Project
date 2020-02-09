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
	BloodEffect(const BloodEffect& src);
	~BloodEffect();

	void Draw(SpriteRenderer& renderer) override;
};