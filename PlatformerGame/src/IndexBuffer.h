#pragma once

#include <glad/glad.h>

class IndexBuffer
{
public:
	IndexBuffer(GLuint* data, GLsizei numIndices, GLenum usage = GL_STATIC_DRAW);
	~IndexBuffer();

	GLsizei GetCount() const { return count; }

	void Bind() const;
	void Unbind() const;

	void Clear();
private:
	GLuint ID{};
	GLsizei count{};
};