#include "GameObject.h"

GameObject::GameObject(glm::vec2 position, glm::vec2 size, Texture2D& texture, glm::vec3 color, GLfloat speed, glm::vec2 textureOffset, glm::vec2 textureZoom)
	:
	position(position),
	size(size),
	speed(speed),
	texture(texture),
	color(color),
	rotation(0.0f),
	rotationAxis(0.0f, 0.0f, 1.0f),
	collisionEnabled(true),
	isDestroyed(false),
	textureZoom(textureZoom),
	textureOffset(textureOffset),
	type(Type::BLOCK)
{
}

GameObject::~GameObject()
{
}

void GameObject::Draw(SpriteRenderer& renderer, GLuint textureUnit)
{
	renderer.Draw(texture, textureUnit, color, position, size, rotation, textureZoom, textureOffset, rotationAxis);
}

void GameObject::Rotate(GLfloat degrees, glm::vec3 rotationAxis)
{
	this->rotationAxis = rotationAxis;
	rotation = degrees;
}

void GameObject::SetPosition(glm::vec2 newPosition)
{
	position = newPosition;
}
