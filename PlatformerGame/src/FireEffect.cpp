#include "FireEffect.h"

FireEffect::FireEffect()
{
	textureOffset = glm::vec2(0.1f, 0.0f);
	textureScale = glm::vec2(1.0f);
	position = glm::vec3(0.0f);
	size = glm::vec2(64);
	color = glm::vec3(1.0f);
	rotation = 0.0f;
	shouldStop = false;

	for (unsigned int i = 1; i < 26; ++i)
	{
		if (i < 10)
			AddTexture(new Texture2D("../assets/FireLoop1/FireLoop1/PNG Frames/64x64/25 frames/fire1_ 0" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
		else
			AddTexture(new Texture2D("../assets/FireLoop1/FireLoop1/PNG Frames/64x64/25 frames/fire1_ " + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	}


}

FireEffect::FireEffect(const FireEffect& src)
	: Effect(src)
{
}

FireEffect::~FireEffect()
{
	for (auto texture : textures)
	{
		if (texture != nullptr)
		{
			texture->Unbind();
			delete texture;
		}
	}
}

FireEffect& FireEffect::operator=(const FireEffect& src)
{
	if (this == &src)
		return *this;

	Effect::operator=(src);
	return *this;
}

void FireEffect::Draw(SpriteRenderer& renderer)
{
	if (texIterator >= textures.size() - 1)
		texIterator = 0;

	renderer.Draw(*textures.at(texIterator), 0, color, position, size, rotation, textureScale, textureOffset);
	++texIterator;
}
