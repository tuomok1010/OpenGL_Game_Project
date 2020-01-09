#include "BloodEffect.h"

BloodEffect::BloodEffect()
	:
	damageDirection(DamageDirection::LEFT),
	textureOffset(0.0f),
	textureScale(1.0f),
	position(0.0f),
	size(32.0f),
	color(1.0f),
	rotation(0.0f)
{
	for (unsigned int i = 0; i < 6; ++i)
		texturesBlood.emplace_back(new Texture2D("../textures/blood/splattersplash_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
}

BloodEffect::~BloodEffect()
{
	for (auto& texture : texturesBlood)
	{
		texture->Unbind();
		delete texture;
	}
}

void BloodEffect::Draw(SpriteRenderer& renderer)
{
	if (texIterator >= texturesBlood.size())
	{
		texIterator = 0;
		shouldStop = true;
		return;
	}

	renderer.Draw(*texturesBlood.at(texIterator), 0, color, position, size, rotation, textureScale, textureOffset);
	++texIterator;

	shouldStop = false;
}

void BloodEffect::ResetAnimation()
{
	texIterator = 0;
}