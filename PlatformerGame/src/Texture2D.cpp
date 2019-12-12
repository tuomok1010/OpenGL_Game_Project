#include "Texture2D.h"

#include <iostream>

#include "stb_image.h"

Texture2D::Texture2D
	(const std::string& filePath, GLint internalFormat, GLenum format, GLenum dataType,
	GLint wrapModeS, GLint wrapModeT, GLint filterMin, GLint filterMag)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModeS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModeT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMag);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &numChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, dataType, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Error loading texture" << std::endl;
	}

	stbi_image_free(data);
}

Texture2D::~Texture2D()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &ID);
}

void Texture2D::Bind(GLuint textureUnit) const
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture2D::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
