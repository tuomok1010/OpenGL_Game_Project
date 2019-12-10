#pragma once

#include "Texture2D.h"
#include "SpriteRenderer.h"

class GameObject
{
public:
	GameObject(glm::vec2 position, glm::vec2 size, Texture2D& texture, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	~GameObject();

	void Draw(SpriteRenderer& sprite, GLuint textureUnit);

private:
	glm::vec2 position{};
	glm::vec2 size{};
	glm::vec2 velocity{};
	glm::vec3 color{};
	GLfloat rotation{};
	GLboolean isSolid{};
	GLboolean isDestroyed{};
	Texture2D& texture;
};