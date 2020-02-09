#include "TextRenderer.h"

TextRenderer::TextRenderer(Shader& shader)
	: shader(shader)
{
	shader.SetUniformi("text", 0);
	VAO = new VertexArray(vertices, indices, 16, 6, GL_DYNAMIC_DRAW);
	VAO->SetVertexLayout(0, 4, GL_FLOAT, 4 * sizeof(float), 0, GL_FALSE);
}

TextRenderer::TextRenderer(const TextRenderer& src)
	: TextRenderer(src.shader)
{
}

TextRenderer::~TextRenderer()
{
	delete VAO;
}

void TextRenderer::Load(std::string font, GLuint fontSize)
{
	characters.clear();

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "Error! Failed to initialize FreeType!" << std::endl;

	FT_Face face;
	if (FT_New_Face(ft, font.c_str(), 0, &face))
		std::cout << "Error! Failed to load font!" << std::endl;

	FT_Set_Pixel_Sizes(face, fontSize, fontSize);	// May be an error here
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte c = 0; c < 128; ++c)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "Error! Failed to load glyph!" << std::endl;
			continue;
		}
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character =
		{
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		characters.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void TextRenderer::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	shader.Bind();
	shader.SetUniform3f("textColor", color);
	glActiveTexture(GL_TEXTURE0);
	VAO->Bind();

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); ++c)
	{
		Character ch = characters[*c];

		GLfloat xPos = x + ch.bearing.x * scale;
		GLfloat yPos = y - (ch.size.y - ch.bearing.y) * scale;

		GLfloat w = ch.size.x * scale;
		GLfloat h = ch.size.y * scale;

		vertices[0] = xPos;
		vertices[1] = yPos + h;
		vertices[2] = 0.0f;
		vertices[3] = 0.0f;

		vertices[4] = xPos;
		vertices[5] = yPos;
		vertices[6] = 0.0f;
		vertices[7] = 1.0f;

		vertices[8] = xPos + w;
		vertices[9] = yPos;
		vertices[10] = 1.0f;
		vertices[11] = 1.0f;

		vertices[12] = xPos + w;
		vertices[13] = yPos + h;
		vertices[14] = 1.0f;
		vertices[15] = 0.0f;

		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glDrawElements(GL_TRIANGLES, VAO->GetIndexCount(), GL_UNSIGNED_INT, nullptr);

		x += (ch.advance >> 6)* scale;
	}
	VAO->Unbind();
	glBindTexture(GL_TEXTURE_2D, 0);
}
