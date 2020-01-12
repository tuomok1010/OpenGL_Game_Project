#include "BloodEffect.h"

BloodEffect::BloodEffect()
	:
	textureOffset(glm::vec2(2.0f, 3.0f)),
	textureScale(glm::vec2(0.25f)),
	position(0.0f),
	size(128.0f),
	color(1.0f),
	rotation(0.0f)
{
	texture = new Texture2D("../textures/blood/all.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
}

BloodEffect::~BloodEffect()
{
	texture->Unbind();
	delete texture;
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

	renderer.Draw(*texture, 0, color, position, size, rotation, textureScale, textureOffset);

	++texIterator;

	shouldStop = false;
}

void BloodEffect::ResetAnimation()
{
	texIterator = 0;
}