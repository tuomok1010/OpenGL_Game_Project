#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader& shader)
	: 
	shader(shader)
{
	InitMeshData();
}

SpriteRenderer::~SpriteRenderer()
{
	mesh->Clear();

	if(mesh != nullptr)
		delete mesh;
}

void SpriteRenderer::InitMeshData()
{
	GLfloat vertices[]
	{
		// Pos				// Tex coords
		 0.0f,  1.0f,		0.0f, 1.0f,
		 0.0f,  0.0f,		0.0f, 0.0f,
		 1.0f,  0.0f,		1.0f, 0.0f,
		 1.0f,  1.0f,		1.0f, 1.0f
	};

	unsigned int indices[]
	{
		0, 1, 2,
		2, 3, 0
	};

	mesh = new Mesh(vertices, indices, 16, 6);
	mesh->SetLayout(0, 2, GL_FLOAT, 4 * sizeof(GLfloat), 0);
	mesh->SetLayout(1, 2, GL_FLOAT, 4 * sizeof(GLfloat), 2 * sizeof(GLfloat));
}

void SpriteRenderer::Draw(Texture2D& texture, GLuint textureUnit, glm::vec3 color, glm::vec2 position, glm::vec2 sizeInPixels, GLfloat rotationInDegrees, glm::vec2 textureZoom, glm::vec2 textureOffset, glm::vec3 rotationAxises)
{
	// setup texture
	texture.Bind(textureUnit);
	shader.Bind();
	shader.SetUniformi("ourTexture", 0);


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
	shader.SetUniform3f("spriteColor", color);
	shader.SetUniform2f("textureZoom", textureZoom);
	shader.SetUniform2f("textureOffset", textureOffset);

	mesh->Render();
	texture.Unbind();
}
