#pragma once

#include <glad/glad.h>

#include "VertexArray.h"

class Mesh
{
public:
	Mesh(GLfloat* vertices, GLuint* indices, GLsizei vertexValueCount, GLsizei indexCount, GLenum usage = GL_STATIC_DRAW);
	Mesh(VertexBuffer& VBO, IndexBuffer& IBO);
	Mesh(VertexArray& VAO);
	~Mesh();

	void Render();
	void Clear();

	GLsizei GetIndexCount() const { return VAO->GetIndexCount(); }
	void SetLayout(GLuint shaderLocationindex, GLint numValuesPerVertex, GLenum type, GLsizei stride, GLuint offset, GLboolean normalised = GL_FALSE);

private:
	VertexArray* VAO{};
	bool shouldCleanMemory{ false };
};