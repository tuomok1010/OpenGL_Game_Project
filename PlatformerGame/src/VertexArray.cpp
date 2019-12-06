#include "VertexArray.h"

VertexArray::VertexArray(GLfloat* vertices, GLuint* indices, GLsizei vertexValueCount, GLsizei indexCount, GLenum usage)
{
	VBO = new VertexBuffer(vertices, vertexValueCount, usage);
	IBO = new IndexBuffer(indices, indexCount, usage);

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
	VBO->Bind();
	IBO->Bind();
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
	VBO->Unbind();
	IBO->Unbind();
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
