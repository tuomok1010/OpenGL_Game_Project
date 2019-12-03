#include "Game.h"
#include <iostream>

Game::Game(int scrnWidth, int scrnHeight)
{
	mainWindow = Window(scrnWidth, scrnHeight);
	mainWindow.Init();
}

Game::~Game()
{
}

void Game::Run()
{
	while (!mainWindow.GetShouldClose())
	{
		mainWindow.PollEvents();

		if (mainWindow.IsKeyPressed(GLFW_KEY_A))
		{
			std::cout << "You pressed A" << std::endl;
		}

		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		mainWindow.SwapBuffers();
	}
}
