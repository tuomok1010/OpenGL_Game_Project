#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "Effect.h"

class FireSparkleEffect : public Effect
{
public:
	FireSparkleEffect();
	FireSparkleEffect(const FireSparkleEffect& src);
	~FireSparkleEffect();

	void Draw(SpriteRenderer& renderer) override;
};