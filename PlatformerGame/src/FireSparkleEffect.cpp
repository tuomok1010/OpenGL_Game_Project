#include "FireSparkleEffect.h"
#include <iostream>

FireSparkleEffect::FireSparkleEffect()
{
	textureOffset = glm::vec2(0.5f, 0.5f);
	textureScale = glm::vec2(0.5f);
	position = glm::vec3(0.0f);
	size = glm::vec2(32.0f);
	color = glm::vec3(1.0f);
	rotation = 0.0f;
	shouldStop = false;

	for (unsigned int i = 1; i < 16; ++i)
		AddTexture(new Texture2D("../assets/sparkling_fire_effect/particles_fireball/effect" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
}

FireSparkleEffect::FireSparkleEffect(const FireSparkleEffect& src)
	: FireSparkleEffect()
{
}

FireSparkleEffect::~FireSparkleEffect()
{
	for (auto& texture : textures)
	{
		if (texture != nullptr)
		{
			texture->Unbind();
			delete texture;
		}
	}
}

void FireSparkleEffect::Draw(SpriteRenderer& renderer)
{
	if (texIterator >= textures.size() - 1)
		shouldStop = true;

	if (!shouldStop)
	{
		renderer.Draw(*textures.at(texIterator), 0, color, position, size, rotation, textureScale, textureOffset);
		++texIterator;
	}
}
