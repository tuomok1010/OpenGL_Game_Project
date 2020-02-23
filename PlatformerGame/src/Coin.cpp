#include "Coin.h"

Coin::Coin(CoinType type, glm::vec3 position)
	:
	textureOffset(0.0f),
	textureScale(1.0f),
	position(position),
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

	sparkleEffect.SetPosition(position);
}

Coin::Coin(const Coin& src)
{
	textureOffset = src.textureOffset;
	textureScale = src.textureScale;
	texIterator = src.texIterator;

	position = src.position;
	size = src.size;
	color = src.color;
	rotation = src.rotation;

	coinType = src.coinType;
	value = src.value;

	sparkleEffect = src.sparkleEffect;
	isCollected = src.isCollected;

	for (const auto& texture : src.texturesCoin)
		texturesCoin.emplace_back(new Texture2D(*texture));
}

Coin::~Coin()
{
	for (auto& texture : texturesCoin)
	{
		if (texture != nullptr)
		{
			texture->Unbind();
			delete texture;
		}
	}
}

Coin& Coin::operator=(const Coin& src)
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

	coinType = src.coinType;
	value = src.value;

	sparkleEffect = src.sparkleEffect;
	isCollected = src.isCollected;

	for (const auto& texture : src.texturesCoin)
		texturesCoin.emplace_back(new Texture2D(*texture));

	return *this;
}

void Coin::Draw(SpriteRenderer& renderer)
{
	if (!isCollected)
	{
		if (texIterator >= texturesCoin.size() - 1)
			texIterator = 0;

		renderer.Draw(*texturesCoin.at(texIterator), 0, color, position, size, rotation, textureScale, textureOffset);
		++texIterator;
	}
	else
	{
		sparkleEffect.Draw(renderer);
	}
}

void Coin::ResetAnimation()
{
	texIterator = 0;
}
