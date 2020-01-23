#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Mesh.h"

enum class Shape
{
	TRIANGLE,
	RECTANGLE
};

class PrimitiveRenderer
{
public:
	PrimitiveRenderer(Shader& shader);
	~PrimitiveRenderer();

	void Draw(Shape shape, glm::vec4 color, glm::vec2 position, glm::vec2 sizeInPixels, GLfloat rotationInDegrees, glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f));

private:
	void DrawTriangle(glm::vec4 color, glm::vec2 position, glm::vec2 sizeInPixels, GLfloat rotationInDegrees, glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f));
	void DrawRectangle(glm::vec4 color, glm::vec2 position, glm::vec2 sizeInPixels, GLfloat rotationInDegrees, glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f));
	Shader& shader;
	Mesh* mesh{};
};