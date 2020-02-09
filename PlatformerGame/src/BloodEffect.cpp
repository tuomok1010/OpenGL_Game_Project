#include "BloodEffect.h"

BloodEffect::BloodEffect()
{
	textureOffset = glm::vec2(2.0f, 3.0f);
	textureScale = glm::vec2(0.25f);
	position = glm::vec3(0.0f);
	size = glm::vec2(128.0f);
	color = glm::vec3(1.0f);
	rotation = 0.0f;

	AddTexture(new Texture2D("../textures/blood/all.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
}

BloodEffect::BloodEffect(const BloodEffect& src)
	: BloodEffect()
{
}

BloodEffect::~BloodEffect()
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

void BloodEffect::Draw(SpriteRenderer& renderer)
{
	if (texIterator >= 13)
	{
		textureOffset = glm::vec2(2.0f, 3.0f);
		texIterator = 0;
		shouldStop = true;
		return;
	}

	if(texIterator == 0)
		textureOffset = glm::vec2(2.0f, 3.0f);
	else
		textureOffset.x += 1.0f;

	if (textureOffset.x > 3.0f)
		textureOffset.x = 0.0f;

	if (textureOffset.x > -0.9f && textureOffset.x < 0.1f)
		textureOffset.y -= 1.0f;

	renderer.Draw(*textures.at(0), 0, color, position, size, rotation, textureScale, textureOffset);

	++texIterator;

	shouldStop = false;
}