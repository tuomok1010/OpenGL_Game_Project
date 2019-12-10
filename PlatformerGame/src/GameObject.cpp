#include "GameObject.h"

GameObject::GameObject(glm::vec2 position, glm::vec2 size, Texture2D& texture, glm::vec3 color, glm::vec2 velocity)
	:
	position(position),
	size(size),
	texture(texture),
	color(color),
	rotation(0.0f),
	isSolid(false),
	isDestroyed(false)
{
}

GameObject::~GameObject()
{
}

void GameObject::Draw(SpriteRenderer& sprite, GLuint textureUnit)
{
	sprite.Draw(texture, textureUnit, color, position, size, rotation);
}
