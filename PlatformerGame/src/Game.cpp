#include "Game.h"
#include <iostream>

Game::Game(int scrnWidth, int scrnHeight)
	: mainWindow(scrnWidth, scrnHeight)
{
	shaders.emplace_back(new Shader("shaders/shader.vert", "shaders/shader.frag"));
}

Game::~Game()
{
	for (unsigned int i = 0; i < shaders.size(); ++i)
		delete shaders[i];
}

void Game::Run()
{
	GLfloat vertices[]
	{	
		// Pos			// Tex coords
		-0.5f, -0.5f,	0.0f, 0.0f,
		 0.5f, -0.5f,	1.0f, 0.0f,
		-0.5f,  0.5f,	0.0f, 1.0f,
		 0.5f,  0.5f,	1.0f, 1.0f
	};

	unsigned int indices[]
	{
		0, 1, 2,
		3, 2, 1,
	};

	VertexBuffer VBO(sizeof(vertices[0]) * 8 * 2, vertices);
	IndexBuffer IBO(sizeof(indices[0]) * 6, indices, 6);
	VertexArray VAO(VBO, IBO);

	Texture2D smiley("../textures/smiley03b.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
	smiley.Bind(0);

	// Set up the vertex positions
	VAO.SetVertexLayout(0, 2, GL_FLOAT, 4 * sizeof(GLfloat), 0);

	// Set up the texture coordinates
	VAO.SetVertexLayout(1, 2, GL_FLOAT, 4 * sizeof(GLfloat), 2 * sizeof(GLfloat));

	// Set up texture coordinates

	VAO.Bind();

	shaders[0]->Bind();
	shaders[0]->SetUniformi("ourTexture", 0);

	while (!mainWindow.GetShouldClose())
	{
		mainWindow.PollEvents();

		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		mainWindow.SwapBuffers();
	}
}
