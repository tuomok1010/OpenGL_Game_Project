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
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		-0.5f,  0.5f,
		 0.5f,  0.5f,
	};

	unsigned int indices[]
	{
		0, 1, 2,
		3, 2, 1,
	};

	VertexBuffer VBO(sizeof(vertices[0]) * 8, vertices);
	IndexBuffer IBO(sizeof(indices[0]) * 6, indices, 6);

	VertexArray VAO(VBO, IBO);

	// OR use the second constructor to create the VBO and IBO in the heap.
	//VertexArray VAO(vertices, indices, 8, 6);

	VAO.SetVertexLayout(0, 2, GL_FLOAT, 2 * sizeof(GLfloat), 0);
	VAO.Bind();

	shaders[0]->Bind();

	while (!mainWindow.GetShouldClose())
	{
		mainWindow.PollEvents();

		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		mainWindow.SwapBuffers();
	}
}
