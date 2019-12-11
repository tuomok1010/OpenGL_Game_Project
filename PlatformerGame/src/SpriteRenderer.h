#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "Texture2D.h"

class SpriteRenderer
{
public:
	SpriteRenderer(Shader& shader);
	virtual ~SpriteRenderer();

	void Draw(Texture2D& texture, GLuint textureUnit, glm::vec3 color, glm::vec2 position, glm::vec2 sizeInPixels, GLfloat rotationInDegrees, glm::vec2 textureZoom, glm::vec3 rotationAxises = glm::vec3(0.0f, 0.0f, 1.0f));

private:
	void InitMeshData();
private:
	Mesh* mesh;
	Shader& shader;
};