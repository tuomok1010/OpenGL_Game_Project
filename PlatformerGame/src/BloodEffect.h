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
	BloodEffect& operator=(const BloodEffect& src);

	void Draw(SpriteRenderer& renderer) override;
};