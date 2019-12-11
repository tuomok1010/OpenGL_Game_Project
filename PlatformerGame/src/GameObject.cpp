#include "GameObject.h"

GameObject::GameObject(glm::vec2 position, glm::vec2 size, Texture2D& texture, glm::vec3 color, glm::vec2 velocity, GLfloat textureZoom)
	:
	position(position),
	size(size),
	texture(texture),
	color(color),
	rotation(0.0f),
	isSolid(false),
	isDestroyed(false),
	textureZoom(textureZoom)
{
}

GameObject::~GameObject()
{
}

void GameObject::Draw(SpriteRenderer& renderer, GLuint textureUnit, glm::vec3 rotationAxises)
{
	renderer.Draw(texture, textureUnit, color, position, size, rotation, textureZoom);
}
