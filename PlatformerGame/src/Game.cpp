#include "Game.h"
#include <iostream>

Game::Game(int scrnWidth, int scrnHeight)
	: mainWindow(scrnWidth, scrnHeight), tempShader("shaders/shader.vert", "shaders/shader.frag")
{
}

Game::~Game()
{
}

void Game::Run()
{
	GLfloat vertices[]
	{
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.0f,  0.5f
	};

	GLuint VBO{}, VAO{};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * 6, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(vertices[0]), 0);
	glEnableVertexAttribArray(0);

	tempShader.Bind();

	while (!mainWindow.GetShouldClose())
	{
		mainWindow.PollEvents();

		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		mainWindow.SwapBuffers();
	}
}
