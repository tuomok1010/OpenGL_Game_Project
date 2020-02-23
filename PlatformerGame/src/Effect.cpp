#include "Effect.h"

Effect::Effect()
{
}

Effect::Effect(const Effect& src)
	: 
	textureOffset(src.textureOffset),
	textureScale(src.textureScale),
	texIterator(src.texIterator),
	position(src.position),
	size(src.size),
	color(src.color),
	rotation(src.rotation),
	shouldStop(src.shouldStop)
{
	for (unsigned int i = 0; i < src.textures.size(); ++i)
	{
		textures.emplace_back(new Texture2D(*src.textures.at(i)));
	}
}

Effect::~Effect()
{
}

Effect& Effect::operator=(const Effect& src)
{
	if (this == &src)
		return *this;

	textureOffset = src.textureOffset;
	textureScale = src.textureScale;
	texIterator = src.texIterator;
	position = src.position;
	size = src.size;
	color = src.color;
	rotation = src.rotation;
	shouldStop = src.shouldStop;

	for (unsigned int i = 0; i < src.textures.size(); ++i)
	{
		textures.emplace_back(new Texture2D(*src.textures.at(i)));
	}

	return *this;
}

void Effect::ResetAnimation()
{
	texIterator = 0;
}

void Effect::AddTexture(Texture2D* textureToAdd)
{
	textures.emplace_back(textureToAdd);
}
