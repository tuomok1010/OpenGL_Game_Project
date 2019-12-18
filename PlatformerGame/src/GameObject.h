#pragma once

#include "Texture2D.h"
#include "SpriteRenderer.h"

class GameObject
{
public:
	GameObject(glm::vec2 position, glm::vec2 size, Texture2D& texture, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f), 
		glm::vec2 textureOffset = glm::vec2(0.0f), glm::vec2 textureZoom = glm::vec2(1.0f));
	virtual ~GameObject();

	void Draw(SpriteRenderer& renderer, GLuint textureUnit, glm::vec3 rotationAxises = glm::vec3(0.0f, 0.0f, 1.0f));
	void SetPosition(glm::vec2 newPosition);

	glm::vec2 GetSize() const { return size; }
	glm::vec2 GetPosition()const { return position; }
	GLboolean isCollisionEnabled() const { return collisionEnabled; }
	void SetIsCollisionEnabled(GLboolean newValue) { collisionEnabled = newValue; }

protected:
	glm::vec2 position{};
	glm::vec2 size{};
	glm::vec2 velocity{};
	glm::vec3 color{};
	GLfloat rotation{};
	GLboolean collisionEnabled{};
	GLboolean isDestroyed{};
	Texture2D& texture;
	glm::vec2 textureZoom{};
	glm::vec2 textureOffset{};
};