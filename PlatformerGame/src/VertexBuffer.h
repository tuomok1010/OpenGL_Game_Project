#pragma once

#include <vector>

#include <glad/glad.h>

class VertexBuffer
{
public:
	VertexBuffer(GLfloat* data, GLsizei numElements, GLenum usage = GL_STATIC_DRAW);
	~VertexBuffer();

	GLuint GetID() const { return ID; }

	void Bind() const;
	void Unbind() const;
private:
	GLuint ID{};
};

