#pragma once

#include <glad/glad.h>

class IndexBuffer
{
public:
	IndexBuffer(GLsizeiptr sizeInBytes, GLuint* data, GLsizei numIndices, GLenum usage = GL_STATIC_DRAW);
	~IndexBuffer();

	GLuint GetID() const { return ID; }
	GLsizei GetCount() const { return count; }

	void Bind() const;
	void Unbind() const;
private:
	GLuint ID{};
	GLsizei count{};
};