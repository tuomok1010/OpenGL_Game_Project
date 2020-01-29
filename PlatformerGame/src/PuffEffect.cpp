#include "PuffEffect.h"

#include <iostream>

PuffEffect::PuffEffect()
{
	textureOffset = glm::vec2(0.0f, 4.0f);
	textureScale = glm::vec2(0.1666f, 0.2f);
	position = glm::vec3(0.0f);
	size = glm::vec2(128.0f);
	color = glm::vec3(1.0f);
	rotation = 0.0f;
	shouldStop = false;

	AddTexture(new Texture2D("../textures/PuffEffect/Poof.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
}

PuffEffect::~PuffEffect()
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

void PuffEffect::Draw(SpriteRenderer& renderer)
{
	if (texIterator >= 30)
	{
		textureOffset = glm::vec2(0.0f, 4.0f);
		texIterator = 0;
		shouldStop = true;
		return;
	}

	if (texIterator == 0)
		textureOffset = glm::vec2(0.0f, 4.0f);
	else
		textureOffset.x += 1.0f;

	if (textureOffset.x > 5.0f)
		textureOffset.x = 0.0f;

	if (texIterator != 0 && texIterator % 6 == 0)
		textureOffset.y -= 1.0f;

	renderer.Draw(*textures.at(0), 0, color, position, size, rotation, textureScale, textureOffset);

	++texIterator;

	shouldStop = false;
}