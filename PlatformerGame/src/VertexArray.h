#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexArray
{
public:
	VertexArray(GLfloat* vertices, GLuint* indices, GLsizei vertexValueCount, GLsizei indexCount, GLenum usage = GL_STATIC_DRAW);
	VertexArray(const VertexBuffer& VBO, const IndexBuffer& IBO);
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void SetVertexLayout(GLuint shaderLocationindex, GLint numValuesPerVertex, GLenum type, GLsizei stride, GLuint offset, GLboolean normalised = GL_FALSE);

	GLsizei GetIndexCount() const { return IBO->GetCount(); }

private:
	GLuint ID{};
	const VertexBuffer* VBO{};
	const IndexBuffer* IBO{};

	bool shouldCleanMemory{ false };
};