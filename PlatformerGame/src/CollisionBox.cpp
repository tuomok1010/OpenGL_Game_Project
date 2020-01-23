#include "CollisionBox.h"
#include <iostream>

CollisionBox::CollisionBox()
	:
	position(glm::vec2(0.0f)),
	size(50.0f),
	color(glm::vec4(1.0f)),
	rotation(0.0f),
	rotationAxis(glm::vec3(0.0f, 0.0f, 1.0f)),
	shape(Shape::RECTANGLE)
{
}

CollisionBox::CollisionBox(glm::vec2 position, glm::vec2 size, glm::vec4 color, GLfloat rotation, glm::vec3 rotationAxis)
	:
	position(position),
	size(size),
	color(color),
	rotation(rotation),
	rotationAxis(rotationAxis),
	shape(Shape::RECTANGLE)
{
}

CollisionBox::~CollisionBox()
{
}

void CollisionBox::Draw(PrimitiveRenderer& renderer)
{
	renderer.Draw(shape, color, position, size, rotation, rotationAxis);
}
