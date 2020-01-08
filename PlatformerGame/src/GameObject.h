#pragma once

#include "Texture2D.h"
#include "SpriteRenderer.h"

enum class Type
{
	BLOCK,
	SPIKETRAP,
	SIGNSTART,		// this is only used in the "menu" level. Will start the game if the player moves to it
	SIGNQUIT,		// this is only used in the "menu" level. Will quit the game if the player moves to it
	CHEST
};

class GameObject
{
public:
	GameObject(glm::vec2 position, glm::vec2 size, Texture2D& texture, glm::vec3 color = glm::vec3(1.0f), GLfloat speed = 100.0f, 
		glm::vec2 textureOffset = glm::vec2(0.0f), glm::vec2 textureZoom = glm::vec2(1.0f));
	virtual ~GameObject();

	void Draw(SpriteRenderer& renderer, GLuint textureUnit = 0);
	void Rotate(GLfloat degrees, glm::vec3 rotationAxis);

	glm::vec2 GetSize() const { return size; }
	glm::vec2 GetPosition()const { return position; }
	GLboolean isCollisionEnabled() const { return collisionEnabled; }
	virtual Type GetType()const { return type; }

	void SetIsCollisionEnabled(GLboolean newValue) { collisionEnabled = newValue; }
	void SetType(Type newType) { type = newType; }
	void SetPosition(glm::vec2 newPosition);

protected:
	glm::vec2 position{};
	glm::vec2 size{};
	GLfloat speed{};
	glm::vec3 color{};
	GLfloat rotation{};
	glm::vec3 rotationAxis{};
	GLboolean collisionEnabled{};
	GLboolean isDestroyed{};
	Texture2D& texture;
	glm::vec2 textureZoom{};
	glm::vec2 textureOffset{};
	Type type;
};