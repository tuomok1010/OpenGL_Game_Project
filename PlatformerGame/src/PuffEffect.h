#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "Effect.h"

class PuffEffect : public Effect
{
public:
	PuffEffect();
	PuffEffect(PuffEffect& src);
	~PuffEffect();

	void Draw(SpriteRenderer& renderer) override;
};