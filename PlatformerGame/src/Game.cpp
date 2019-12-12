#include "Game.h"

#include <iostream>

// shader indices
#define SHADER_BASIC	0
#define SHADER_SPRITE	1

Game::Game(int scrnWidth, int scrnHeight)
	: 
	mainWindow(scrnWidth, scrnHeight), 
	projection(glm::mat4(1.0f))
{
	projection = glm::ortho(0.0f, (float)mainWindow.GetBufferWidth(), 0.0f, (float)mainWindow.GetBufferHeight(), -2.0f, 2.0f);

	// init shaders list
	shaders.emplace_back(new Shader("shaders/shader.vert", "shaders/shader.frag"));
	shaders.emplace_back(new Shader("shaders/simple_sprite.vert", "shaders/simple_sprite.frag"));

	renderer = new SpriteRenderer(*shaders[SHADER_SPRITE]);
}

Game::~Game()
{
	for (int i = 0; i < shaders.size(); ++i)
		delete shaders[i];

	delete renderer;
}

void Game::Run()
{
	Level lvl(*renderer, player);
	lvl.Load("../levels/OpenGLGame_Level1.txt");

	while (!mainWindow.GetShouldClose())
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ProcessInput();

		Draw(lvl);
	}

	glfwTerminate();
}

void Game::ProcessInput()
{
	if (mainWindow.IsKeyPressed(GLFW_KEY_D))
	{
		player.SetOrientation(PlayerOrientation::RIGHT);
		player.SetState(PlayerState::RUN);
		player.Move(deltaTime);
	}

	if (mainWindow.IsKeyPressed(GLFW_KEY_A))
	{
		player.SetOrientation(PlayerOrientation::LEFT);
		player.SetState(PlayerState::RUN);
		player.Move(deltaTime);
	}
}

void Game::Draw(Level& level)
{
	mainWindow.PollEvents();

	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shaders[SHADER_SPRITE]->SetUniformMat4("projection", &projection);

	glm::mat4 view = glm::mat4(1.0f);
	view = player.GetCameraViewMatrix();
	shaders[SHADER_SPRITE]->SetUniformMat4("view", &view);

	level.Draw();
	player.SetState(PlayerState::IDLE);

	mainWindow.SwapBuffers();
}
