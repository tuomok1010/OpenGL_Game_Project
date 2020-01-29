#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "FireSparkleEffect.h"

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
	Coin(CoinType type, glm::vec3 position = glm::vec3(0.0f));
	~Coin();

	void Draw(SpriteRenderer& renderer);
	void ResetAnimation();

	void SetPosition(glm::vec3 newPos) { position = newPos; }
	void Rotate(GLfloat degrees) { rotation = degrees; }
	void SetIsCollected(GLboolean newVal) { isCollected = newVal; }

	glm::vec2 GetSize()const { return size; }
	glm::vec3 GetPosition()const { return position; }
	GLboolean GetIsCollected()const { return isCollected; }
	GLuint GetValue()const { return value; }
	GLboolean GetShouldBeDestroyed()const { return sparkleEffect.GetShouldStop(); }

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

	FireSparkleEffect sparkleEffect;
	GLboolean isCollected{ false }; // this will change to "true" when the player collides with the coin
};