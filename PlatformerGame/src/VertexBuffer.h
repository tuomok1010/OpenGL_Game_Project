#pragma once

#include <glad/glad.h>

class VertexBuffer
{
public:
	VertexBuffer(GLsizeiptr sizeInBytes, GLfloat* data, GLenum usage = GL_STATIC_DRAW);
	~VertexBuffer();

	GLuint GetID() const { return ID; }

	void Bind() const;
	void Unbind() const;
private:
	GLuint ID{};
};

