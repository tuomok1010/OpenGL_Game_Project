#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "Effect.h"

class FireEffect : public Effect
{
public:
	FireEffect();
	FireEffect(const FireEffect& src);
	~FireEffect();
	FireEffect& operator=(const FireEffect& src);

	void Draw(SpriteRenderer& renderer) override;
};