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
	SpriteRenderer(const SpriteRenderer& src);
	~SpriteRenderer();

	void Draw(Texture2D& texture, GLuint textureUnit, glm::vec3 color, glm::vec2 position, glm::vec2 sizeInPixels, GLfloat rotationInDegrees, 
		glm::vec2 textureZoom = glm::vec2(1.0f), glm::vec2 textureOffset = glm::vec2(0.0f), glm::vec3 rotationAxises = glm::vec3(0.0f, 0.0f, 1.0f));

private:
	void InitMeshData();
	Shader& shader;
	Mesh* mesh;
};