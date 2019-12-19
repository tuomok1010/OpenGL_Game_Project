#include "Game.h"

#include <iostream>

// shader indices
#define SHADER_BASIC	0
#define SHADER_SPRITE	1

// used in the ProcessInput function to reset the jumpCooldown variable
#define JUMP_COOLDOWN 1

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
	/*
		TODO fix: The SetPosition and GetPrevious position is used with the collision detection. However, 
		sometimes when the player jumps and falls back to the ground, instead of falling completely to the ground and touching it,
		he remains slightly in the air. 
	*/

	// Starts the game
	if (mainWindow.IsKeyPressed(GLFW_KEY_ENTER) && gameState == GameState::MENU)
		gameState = GameState::RUN;

	if (gameState == GameState::RUN)
	{
		// checks if player is colliding with any traps and if so, damages the player
		level.handleTrapDamage();
		if (player.GetIsDead())
			player.SetState(PlayerState::DEATH);

		// The MoveDown function basically acts as gravity
		if (level.gravityEnabled)
		{
			player.MoveDown(deltaTime);
			if (level.isPlayerCollidingWithBlocks())
				player.SetPosition(player.GetPreviousPosition());
		}

		if (!player.GetIsDead())
		{
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
					jumpCooldown = JUMP_COOLDOWN;
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
}

void Game::Draw(Level& level)
{
	mainWindow.PollEvents();

	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shaders[SHADER_SPRITE]->SetUniformMat4("projection", &projection);

	if (gameState == GameState::MENU)
	{
		glm::mat4 view = glm::mat4(1.0f);
		shaders[SHADER_SPRITE]->SetUniformMat4("view", &view);

		Texture2D* menu = new Texture2D("../textures/menu.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
		renderer->Draw(*menu, 0, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(800.0f, 600.0f), 0.0f);
	}
	else if(gameState == GameState::RUN)
	{
		glm::mat4 view = glm::mat4(1.0f);
		view = player.GetCameraViewMatrix();
		shaders[SHADER_SPRITE]->SetUniformMat4("view", &view);

		level.Draw();

		if(!player.GetIsDead())
			player.SetState(PlayerState::IDLE);
	}
	else
	{
		// process quitting
	}


	mainWindow.SwapBuffers();
}
