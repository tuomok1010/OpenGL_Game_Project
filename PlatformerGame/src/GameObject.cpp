#include "GameObject.h"

GameObject::GameObject(glm::vec2 position, glm::vec2 size, Texture2D& texture, glm::vec3 color, glm::vec2 velocity, glm::vec2 textureOffset, glm::vec2 textureZoom)
	:
	position(position),
	size(size),
	texture(texture),
	color(color),
	rotation(0.0f),
	collisionEnabled(true),
	isDestroyed(false),
	textureZoom(textureZoom),
	textureOffset(textureOffset)
{
}

GameObject::~GameObject()
{
}

void GameObject::Draw(SpriteRenderer& renderer, GLuint textureUnit, glm::vec3 rotationAxises)
{
	renderer.Draw(texture, textureUnit, color, position, size, rotation, textureZoom, textureOffset, rotationAxises);
}

void GameObject::SetPosition(glm::vec2 newPosition)
{
	position = newPosition;
}
