#include "PrimitiveRenderer.h"
#include <iostream>

PrimitiveRenderer::PrimitiveRenderer(Shader& shader)
	: shader(shader)
{
}

PrimitiveRenderer::PrimitiveRenderer(PrimitiveRenderer& src)
	: PrimitiveRenderer(src.shader)
{
}

PrimitiveRenderer::~PrimitiveRenderer()
{
	if(mesh != nullptr)
		delete mesh;
}

void PrimitiveRenderer::Draw(Shape shape, glm::vec4 color, glm::vec2 position, glm::vec2 sizeInPixels, GLfloat rotationInDegrees, glm::vec3 rotationAxis)
{
	switch (shape)
	{
		case Shape::TRIANGLE:
		{
			DrawTriangle(color, position, sizeInPixels, rotationInDegrees, rotationAxis);
			break;
		}
		case Shape::RECTANGLE:
		{
			DrawRectangle(color, position, sizeInPixels, rotationInDegrees, rotationAxis);
			break;
		}
	}
}

void PrimitiveRenderer::DrawTriangle(glm::vec4 color, glm::vec2 position, glm::vec2 sizeInPixels, GLfloat rotationInDegrees, glm::vec3 rotationAxises)
{
	GLfloat vertices[]
	{
		// Pos				// color
		 0.0f,  0.0f,		color.r, color.g, color.b, color.a,
		 1.0f,  0.0f,		color.r, color.g, color.b, color.a,
		 0.5f,  1.0f,		color.r, color.g, color.b, color.a
	};

	unsigned int indices[]
	{
		0, 1, 2
	};

	mesh = new Mesh(vertices, indices, 18, 3);
	mesh->SetLayout(0, 2, GL_FLOAT, 6 * sizeof(GLfloat), 0);
	mesh->SetLayout(1, 4, GL_FLOAT, 6 * sizeof(GLfloat), 2 * sizeof(GLfloat));

	shader.Bind();

	// position the sprite
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));

	// rotate the sprite
	model = glm::translate(model, glm::vec3(0.5f * sizeInPixels.x, 0.5f * sizeInPixels.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotationInDegrees), rotationAxises);
	model = glm::translate(model, glm::vec3(-0.5f * sizeInPixels.x, -0.5f * sizeInPixels.y, 0.0f));

	// scale the sprite
	model = glm::scale(model, glm::vec3(sizeInPixels, 1.0f));

	shader.SetUniformMat4("model", &model);

	mesh->Render();
	delete mesh;
}

void PrimitiveRenderer::DrawRectangle(glm::vec4 color, glm::vec2 position, glm::vec2 sizeInPixels, GLfloat rotationInDegrees, glm::vec3 rotationAxises)
{
	GLfloat vertices[]
	{
		// Pos				// color
		 0.0f,  1.0f,		color.r, color.g, color.b, color.a,
		 0.0f,  0.0f,		color.r, color.g, color.b, color.a,
		 1.0f,  0.0f,		color.r, color.g, color.b, color.a,
		 1.0f,  1.0f,		color.r, color.g, color.b, color.a
	};

	unsigned int indices[]
	{
		0, 1, 2,
		2, 3, 0
	};

	mesh = new Mesh(vertices, indices, 24, 6);
	mesh->SetLayout(0, 2, GL_FLOAT, 6 * sizeof(GLfloat), 0);
	mesh->SetLayout(1, 4, GL_FLOAT, 6 * sizeof(GLfloat), 2 * sizeof(GLfloat));

	shader.Bind();

	// position the sprite
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));

	// rotate the sprite
	model = glm::translate(model, glm::vec3(0.5f * sizeInPixels.x, 0.5f * sizeInPixels.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotationInDegrees), rotationAxises);
	model = glm::translate(model, glm::vec3(-0.5f * sizeInPixels.x, -0.5f * sizeInPixels.y, 0.0f));

	// scale the sprite
	model = glm::scale(model, glm::vec3(sizeInPixels, 1.0f));

	shader.SetUniformMat4("model", &model);

	mesh->Render();
	delete mesh;
}