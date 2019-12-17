#include "Game.h"

#include <iostream>

// shader indices
#define SHADER_BASIC	0
#define SHADER_SPRITE	1

Game::Game(int scrnWidth, int scrnHeight)
	: 
	mainWindow(scrnWidth, scrnHeight), 
	projection(glm::mat4(1.0f)),
	gameState(GameState::MENU),
	jumpCooldown(0.0f)
{
	projection = glm::ortho(0.0f, (float)mainWindow.GetBufferWidth(), 0.0f, (float)mainWindow.GetBufferHeight(), -2.0f, 2.0f);

	// init shaders list
	shaders.emplace_back(new Shader("shaders/shader.vert", "shaders/shader.frag"));
	shaders.emplace_back(new Shader("shaders/simple_sprite.vert", "shaders/simple_sprite.frag"));

	renderer = new SpriteRenderer(*shaders[SHADER_SPRITE]);
}

Game::~Game()
{
	for (unsigned int i = 0; i < shaders.size(); ++i)
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
	
		ProcessInput(lvl);

		Draw(lvl);
	}

	glfwTerminate();
}

void Game::ProcessInput(Level& level)
{
	// Starts the game
	if (mainWindow.IsKeyPressed(GLFW_KEY_ENTER) && gameState == GameState::MENU)
		gameState = GameState::RUN;

	if (gameState == GameState::RUN)
	{
		// The MoveDown function basically acts as gravity
		if (level.gravityEnabled)
		{
			player.MoveDown(deltaTime);
			if (level.isPlayerCollidingWithBlocks())
				player.SetPosition(player.GetPreviousPosition());
		}

		if (mainWindow.IsKeyPressed(GLFW_KEY_D))
		{
			if (previusKeyPressed != GLFW_KEY_D)
				player.ResetAnimation(PlayerState::RUN);

			previusKeyPressed = GLFW_KEY_D;
			player.SetOrientation(PlayerOrientation::RIGHT);
			player.Move(deltaTime);

			if (level.isPlayerCollidingWithBlocks())
				player.SetPosition(player.GetPreviousPosition());
		}

		if (mainWindow.IsKeyPressed(GLFW_KEY_A))
		{
			if (previusKeyPressed != GLFW_KEY_A)
				player.ResetAnimation(PlayerState::RUN);

			previusKeyPressed = GLFW_KEY_A;
			player.SetOrientation(PlayerOrientation::LEFT);
			player.Move(deltaTime);

			if (level.isPlayerCollidingWithBlocks())
				player.SetPosition(player.GetPreviousPosition());
		}


		if (mainWindow.IsKeyPressed(GLFW_KEY_SPACE) && canJumpAgain == true)
		{
			if (jumpCooldown <= 0.0f)
			{
				canJumpAgain = false;
				jumpCooldown = 1.0f;
			}
		}


		if (!canJumpAgain)
		{
			if (!player.Jump(deltaTime, level.gravityEnabled))
				canJumpAgain = true;
		}
		jumpCooldown -= deltaTime;
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

	if (gameState == GameState::MENU)
	{
		Texture2D* menu = new Texture2D("../textures/menu.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
		renderer->Draw(*menu, 0, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(410, 410.0f), glm::vec2(800.0f, 600.0f), 0.0f);
	}
	else if(gameState == GameState::RUN)
	{
		level.Draw();
		player.SetState(PlayerState::IDLE);
	}
	else
	{
		// process quitting
	}


	mainWindow.SwapBuffers();
}
