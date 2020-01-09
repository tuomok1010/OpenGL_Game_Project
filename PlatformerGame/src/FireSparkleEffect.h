#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"

class FireSparkleEffect
{
public:
	FireSparkleEffect();
	~FireSparkleEffect();

	void Draw(SpriteRenderer& renderer);
	void ResetAnimation();

	void SetPosition(glm::vec3 newPos) { position = newPos; }
	void Rotate(GLfloat degrees) { rotation = degrees; }

	glm::vec2 GetSize()const { return size; }
	GLboolean GetIsDestroyed()const { return isDestroyed; }

private:
	std::vector<Texture2D*> textures{};
	glm::vec2 textureOffset{};
	glm::vec2 textureScale{}; // the "textureZoom" variable in the renderer draw functions
	GLuint texIterator{};

	glm::vec3 position{};
	glm::vec2 size{};
	glm::vec3 color{};
	GLfloat rotation{};

	GLboolean isDestroyed{ false };
};