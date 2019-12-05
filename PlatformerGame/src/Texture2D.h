#pragma once

#include <string>

#include <glad/glad.h>

class Texture2D
{
public:
	Texture2D
		(const std::string& filePath, GLint internalFormat, GLenum format, GLenum dataType, 
		GLint wrapModeS = GL_REPEAT, GLint wrapModeT = GL_REPEAT, GLint filterMin = GL_LINEAR, GLint filterMag = GL_LINEAR);

	~Texture2D();

	GLsizei GetWidth() const { return width; }
	GLsizei GetHeight() const { return height; }

	void Bind(GLuint textureUnit = 0) const;
	void Unbind() const;

private:
	GLuint ID{};
	GLsizei width{};
	GLsizei height{};
	int numChannels{};
};

