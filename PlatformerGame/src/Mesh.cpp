#include "Mesh.h"

Mesh::Mesh(GLfloat* vertices, GLuint* indices, GLsizei vertexValueCount, GLsizei indexCount, GLenum usage)
{
	VAO = new VertexArray(vertices, indices, vertexValueCount, indexCount, usage);
	shouldCleanMemory = true;
}

Mesh::Mesh(VertexBuffer& VBO, IndexBuffer& IBO)
{
	VAO = new VertexArray(VBO, IBO);
	shouldCleanMemory = true;
}

Mesh::Mesh(VertexArray& VAO)
	: VAO(&VAO)
{
}

Mesh::~Mesh()
{
	Clear();

	if (shouldCleanMemory)
		delete VAO;
}

void Mesh::Render()
{
	VAO->Bind();
	glDrawElements(GL_TRIANGLES, VAO->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
	VAO->Unbind();
}

void Mesh::Clear()
{
	VAO->Clear();
}

void Mesh::SetLayout(GLuint shaderLocationindex, GLint numValuesPerVertex, GLenum type, GLsizei stride, GLuint offset, GLboolean normalised)
{
	VAO->SetVertexLayout(shaderLocationindex, numValuesPerVertex, type, stride, offset, normalised);
}
