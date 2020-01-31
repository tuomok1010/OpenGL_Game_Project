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
	velocity(glm::vec3(0.0f)),
	gravity(0.0f),
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

void GameObject::Update(GLfloat deltaTime)
{
	// Update movement
	previousPosition = position;

	position.x += velocity.x * speed * deltaTime;
	position.y += velocity.y * speed * deltaTime;
	velocity.y -= gravity * deltaTime;

	collisionBoxSimple.position = position;
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

	CollisionBox otherObjectColBox = obj.GetCollisionBox();

	GLboolean collisionX = collisionBoxSimple.position.x + collisionBoxSimple.size.x > otherObjectColBox.position.x && otherObjectColBox.position.x + otherObjectColBox.size.x > collisionBoxSimple.position.x;
	GLboolean collisionY = collisionBoxSimple.position.y + collisionBoxSimple.size.y > otherObjectColBox.position.y && otherObjectColBox.position.y + otherObjectColBox.size.y > collisionBoxSimple.position.y;


	return collisionX && collisionY;
}

void GameObject::ReverseVelocityX()
{
	if (velocity.x < 0.0f)
	{
		velocity.x = abs(velocity.x);
	}
	else if (velocity.x > 0.0f)
	{
		velocity.x -= velocity.x * 2;
	}
	else
	{
		velocity.x = 0.0f;
	}
}

void GameObject::SetPosition(glm::vec2 newPosition)
{
	previousPosition = position;
	position = newPosition;
	collisionBoxSimple.position = position;
}
