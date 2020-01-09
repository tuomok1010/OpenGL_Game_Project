#include "FireSparkleEffect.h"
#include <iostream>

FireSparkleEffect::FireSparkleEffect()
	:
	textureOffset(glm::vec2(0.5f, 0.5f)),
	textureScale(glm::vec2(0.5f)),
	position(0.0f),
	size(32.0f),
	color(1.0f),
	rotation(0.0f)
{
	for (unsigned int i = 1; i < 16; ++i)
		textures.emplace_back(new Texture2D("../assets/sparkling_fire_effect/particles_fireball/effect" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
}

FireSparkleEffect::~FireSparkleEffect()
{
	for (auto& texture : textures)
	{
		texture->Unbind();
		delete texture;
	}
}

void FireSparkleEffect::Draw(SpriteRenderer& renderer)
{
	if (texIterator >= textures.size() - 1)
		isDestroyed = true;

	if (!isDestroyed)
	{
		renderer.Draw(*textures.at(texIterator), 0, color, position, size, rotation, textureScale, textureOffset);
		++texIterator;
	}
}

void FireSparkleEffect::ResetAnimation()
{
	texIterator = 0;
}
