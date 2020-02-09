#include "CollisionBox.h"
#include <iostream>

CollisionBox::CollisionBox()
	: 
	CollisionBox(glm::vec2(0.0f), glm::vec2(50.0f), glm::vec4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f))
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

CollisionBox::CollisionBox(const CollisionBox& src)
	: CollisionBox(src.position, src.size, src.color, src.rotation, src.rotationAxis)
{
}

CollisionBox::~CollisionBox()
{
}

void CollisionBox::Draw(PrimitiveRenderer& renderer)
{
	renderer.Draw(shape, color, position, size, rotation, rotationAxis);
}
