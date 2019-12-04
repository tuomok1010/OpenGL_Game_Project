#include "VertexArray.h"

VertexArray::VertexArray(GLfloat* vertices, GLuint* indices, GLsizei vertexValueCount, GLsizei indexCount)
{
	VBO = new VertexBuffer(sizeof(vertices[0]) * vertexValueCount, vertices);
	IBO = new IndexBuffer(sizeof(indices[0]) * indexCount, indices, indexCount);

	glGenVertexArrays(1, &ID);
	shouldCleanMemory = true;
}

VertexArray::VertexArray(const VertexBuffer& VBO, const IndexBuffer& IBO)
	: VBO(&VBO), IBO(&IBO)
{
	glGenVertexArrays(1, &ID);
}

VertexArray::~VertexArray()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	if (shouldCleanMemory)
	{
		delete VBO;
		delete IBO;
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(ID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::SetVertexLayout(GLuint shaderLocationindex, GLint numValuesPerVertex, GLenum type, GLsizei stride, GLuint offset, GLboolean normalised)
{
	Bind();
	VBO->Bind();
	IBO->Bind();

	glVertexAttribPointer(shaderLocationindex, numValuesPerVertex, type, normalised, stride, (const void*)offset);
	glEnableVertexAttribArray(shaderLocationindex);

	Unbind();
	VBO->Unbind();
	IBO->Unbind();
}
