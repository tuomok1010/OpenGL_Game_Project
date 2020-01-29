#include "GameObject.h"

GameObject::GameObject(glm::vec2 position, glm::vec2 size, Texture2D& texture, glm::vec3 color, GLfloat speed, glm::vec2 textureOffset, glm::vec2 textureScale)
	:
	position(position),
	size(size),
	speed(speed),
	texture(texture),
	color(color),
	rotation(0.0f),
	rotationAxis(0.0f, 0.0f, 1.0f),
	textureScale(textureScale),
	textureOffset(textureOffset),
	type(Type::BLOCK),
	collisionEnabled(true)
{
	collisionBoxSimple = CollisionBox(this->position, this->size, glm::vec4(1.0f, 1.0f, 0.0f, 0.5f));
}

GameObject::~GameObject()
{
}

void GameObject::Draw(SpriteRenderer& renderer, PrimitiveRenderer& colBoxRenderer, GLboolean renderCollisionBox, GLuint textureUnit)
{
	renderer.Draw(texture, textureUnit, color, position, size, rotation, textureScale, textureOffset, rotationAxis);
	if (renderCollisionBox)
		collisionBoxSimple.Draw(colBoxRenderer);
}

void GameObject::Rotate(GLfloat degrees, glm::vec3 rotationAxis)
{
	this->rotationAxis = rotationAxis;
	rotation = degrees;
}

GLboolean GameObject::SimpleCollisionCheck(GameObject& obj)
{
	glm::vec2 objPos = obj.GetPosition();
	glm::vec2 objSize = obj.GetSize();

	GLboolean collisionX = collisionBoxSimple.position.x + collisionBoxSimple.size.x > objPos.x&& objPos.x + objSize.x > collisionBoxSimple.position.x;
	GLboolean collisionY = collisionBoxSimple.position.y + collisionBoxSimple.size.y > objPos.y&& objPos.y + objSize.y > collisionBoxSimple.position.y;
	return collisionX && collisionY;

	return false;
}

void GameObject::SetPosition(glm::vec2 newPosition)
{
	position = newPosition;
	collisionBoxSimple.position = position;
}
