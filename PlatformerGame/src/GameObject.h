#pragma once

#include "Texture2D.h"
#include "SpriteRenderer.h"

class GameObject
{
public:
	GameObject(glm::vec2 position, glm::vec2 size, Texture2D& texture, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f), GLfloat textureZoom = 1.0f);
	~GameObject();

	virtual void Draw(SpriteRenderer& renderer, GLuint textureUnit, glm::vec3 rotationAxises = glm::vec3(0.0f, 0.0f, 1.0f));

protected:
	glm::vec2 position{};
	glm::vec2 size{};
	glm::vec2 velocity{};
	glm::vec3 color{};
	GLfloat rotation{};
private:
	GLboolean isSolid{};
	GLboolean isDestroyed{};
	Texture2D& texture;
	GLfloat textureZoom{};
};