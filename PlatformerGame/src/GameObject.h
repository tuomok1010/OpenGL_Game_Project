#pragma once

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "CollisionBox.h"

enum class Type
{
	BLOCK,
	SPIKETRAP,
	SIGNSTART,		// this is only used in the "menu" level. Will start the game if the player moves to it
	SIGNQUIT,		// this is only used in the "menu" level. Will quit the game if the player moves to it
	CHEST,
	PLATFORM_HORIZONTAL,
	PLATFORM_VERTICAL
};

class GameObject
{
public:
	GameObject(Type type, glm::vec2 position, glm::vec2 size, Texture2D& texture, glm::vec3 color = glm::vec3(1.0f), GLfloat speed = 100.0f, 
		glm::vec2 textureOffset = glm::vec2(0.0f), glm::vec2 textureScale = glm::vec2(1.0f));
	GameObject(const GameObject& src);
	virtual ~GameObject();

	virtual void Draw(SpriteRenderer& renderer, PrimitiveRenderer& colBoxRenderer, GLboolean renderCollisionBox = false, GLuint textureUnit = 0);
	void Update(GLfloat deltaTime);
	void Rotate(GLfloat degrees, glm::vec3 rotationAxis);

	// uses the object's collision box to detect collision
	GLboolean SimpleCollisionCheck(GameObject& obj);

	// creates a collision box on the fly in the given pos and uses it to check collision with the other object's collisionbox
	GLboolean SimpleCollisionCheck(GameObject& obj, glm::vec2 pos, glm::vec2 size);

	void ReverseVelocityX();
	void ReverseVelocityY();

	glm::vec2 GetSize() const { return size; }
	glm::vec2 GetPosition()const { return position; }
	GLboolean isCollisionEnabled() const { return collisionEnabled; }
	virtual Type GetType()const { return type; }
	CollisionBox GetCollisionBox()const { return collisionBoxSimple; }
	glm::vec2 GetPreviousPosition()const { return previousPosition; }
	glm::vec2 GetVelocity()const { return velocity; }
	GLfloat GetSpeed()const { return speed; }

	void SetIsCollisionEnabled(GLboolean newValue) { collisionEnabled = newValue; }
	void SetType(Type newType) { type = newType; }
	void SetPosition(glm::vec2 newPosition);
	void SetCollisionBoxSize(glm::vec2 newSize) { collisionBoxSimple.size = newSize; }
	void SetVelocity(glm::vec2 newVelocity) { velocity = newVelocity; }

protected:
	glm::vec2 previousPosition;
	glm::vec2 position;
	glm::vec2 size;
	GLfloat speed;
	glm::vec3 color;
	GLfloat rotation;
	glm::vec3 rotationAxis;
	glm::vec2 velocity;
	GLfloat gravity;

	Texture2D& texture;
	glm::vec2 textureScale;
	glm::vec2 textureOffset;

	Type type;

	GLboolean collisionEnabled;
	CollisionBox collisionBoxSimple;
};