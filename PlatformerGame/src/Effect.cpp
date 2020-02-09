#include "Effect.h"

Effect::Effect()
{
}

Effect::Effect(const Effect& src)
	: Effect()
{
}

Effect::~Effect()
{
}

void Effect::ResetAnimation()
{
	texIterator = 0;
}

void Effect::AddTexture(Texture2D* textureToAdd)
{
	textures.emplace_back(textureToAdd);
}
