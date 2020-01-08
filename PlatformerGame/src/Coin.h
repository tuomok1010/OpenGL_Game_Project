#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"

enum class CoinType
{
	COPPER,
	SILVER,
	GOLD
};

class Coin
{
public:
public:
	Coin(CoinType type);
	~Coin();

	void Draw(SpriteRenderer& renderer);
	void ResetAnimation();

	void SetPosition(glm::vec3 newPos) { position = newPos; }
	void Rotate(GLfloat degrees) { rotation = degrees; }

	glm::vec2 GetSize()const { return size; }

private:
	std::vector<Texture2D*> texturesCoin{};
	glm::vec2 textureOffset{};
	glm::vec2 textureScale{}; // the "textureZoom" variable in the renderer draw functions
	GLuint texIterator{};

	glm::vec3 position{};
	glm::vec2 size{};
	glm::vec3 color{};
	GLfloat rotation{};

	CoinType coinType{};
	GLuint value{};
};