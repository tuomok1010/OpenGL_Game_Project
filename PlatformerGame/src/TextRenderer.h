#pragma once

#include <iostream>
#include <map>

#include <glm/gtc/matrix_transform.hpp>
#include <freetype/ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"
#include "VertexArray.h"

struct Character
{
	GLuint textureID{};
	glm::ivec2 size{};
	glm::ivec2 bearing{};
	GLuint advance{};
};

class TextRenderer
{
public:
	TextRenderer(Shader& shader);
	~TextRenderer();

	void Load(std::string font, GLuint fontSize);
	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color = glm::vec3(1.0f));

public:
	std::map<GLchar, Character> characters{};

private:
	Shader& shader;
	VertexArray* VAO{};
	GLfloat vertices[16]{};
	GLuint indices[6]{ 0, 1, 2, 2, 3, 0 };
};