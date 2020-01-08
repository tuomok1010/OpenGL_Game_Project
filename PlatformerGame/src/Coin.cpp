#include "Coin.h"

Coin::Coin(CoinType type)
	:
	textureOffset(0.0f),
	textureScale(1.0f),
	position(0.0f),
	size(32.0f),
	color(1.0f),
	rotation(0.0f),
	coinType(type)
{
	switch (coinType)
	{
		case CoinType::COPPER:
		{
			for (unsigned int i = 0; i < 8; ++i)
				texturesCoin.emplace_back(new Texture2D("../assets/CoinsByLexassets/PNG/COPPER/BIG/BIG_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));

			value = 1;
			break;
		}
		case CoinType::SILVER:
		{
			for (unsigned int i = 0; i < 8; ++i)
				texturesCoin.emplace_back(new Texture2D("../assets/CoinsByLexassets/PNG/SILVER/BIG/BIG_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));

			value = 5;
			break;
		}
		case CoinType::GOLD:
		{
			for (unsigned int i = 0; i < 8; ++i)
				texturesCoin.emplace_back(new Texture2D("../assets/CoinsByLexassets/PNG/GOLD/BIG/BIG_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));

			value = 10;
			break;
		}
	}
}

Coin::~Coin()
{
	for (auto& texture : texturesCoin)
	{
		texture->Unbind();
		delete texture;
	}
}

void Coin::Draw(SpriteRenderer& renderer)
{
	if (texIterator >= texturesCoin.size() - 1)
		texIterator = 0;

	renderer.Draw(*texturesCoin.at(texIterator), 0, color, position, size, rotation, textureScale, textureOffset);
	++texIterator;
}

void Coin::ResetAnimation()
{
	texIterator = 0;
}
