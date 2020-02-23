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
	FireSparkleEffect& operator=(const FireSparkleEffect& src);

	void Draw(SpriteRenderer& renderer) override;
};