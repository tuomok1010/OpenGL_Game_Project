#pragma once

#include <glm/glm.hpp>

#include "PrimitiveRenderer.h"

class CollisionBox
{
public:
	CollisionBox();
	CollisionBox(glm::vec2 position, glm::vec2 size, glm::vec4 color = glm::vec4(1.0f), GLfloat rotation = 0.0f, glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f));
	~CollisionBox();

	void Draw(PrimitiveRenderer& renderer);

	glm::vec2 position{};
	glm::vec2 size{};
	glm::vec4 color{};

private:
	GLfloat rotation{};
	glm::vec3 rotationAxis{};
	Shape shape{};
};