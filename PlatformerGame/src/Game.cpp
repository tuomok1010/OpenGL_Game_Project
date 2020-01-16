#include "Game.h"

#include <iostream>

// shader indices
#define SHADER_BASIC	0
#define SHADER_SPRITE	1

// used in the ProcessInput function to reset the jumpCooldown and attackCooldown variables
#define ATTACK_COOLDOWN 1

Game::Game(int scrnWidth, int scrnHeight)
	: 
	mainWindow(scrnWidth, scrnHeight), 
	projection(glm::mat4(1.0f)),
	gameState(GameState::MENU),
	levelLoadTimer(5.0f)
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
		delete shaders.at(i);

	delete renderer;
}

void Game::Run()
{
	while (!mainWindow.GetShouldClose())
	{
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if (advanceLevel)
		{
			if (level != nullptr)
				delete level;
			
			level = new Level(*renderer, player);

			std::cout << "Level number: " << level->levelNumber << std::endl;

			std::string levelNumberString = std::to_string(level->levelNumber);
			std::string levelPath = "../levels/OpenGLGame_Level" + levelNumberString + ".txt";
			std::string backGroundPath = "../textures/backGround" + levelNumberString + ".png";
			
			level->Load(levelPath, backGroundPath);
			advanceLevel = false;
		}
		if (level->quitGame)
			gameState = GameState::QUIT;

		if (gameState == GameState::QUIT)
			mainWindow.SetShouldClose(true);

		if (levelLoadTimer <= 0)
		{
			ProcessInput(*level);

			if(gameState == GameState::RUN)
				Update(*level);

			Draw(*level);
		}
		levelLoadTimer -= deltaTime;
	}

	glfwTerminate();
}

void Game::ProcessInput(Level& level)
{
	// Starts the game
	if (mainWindow.IsKeyPressed(GLFW_KEY_ENTER) && gameState == GameState::MENU)
		gameState = GameState::RUN;
	// exits the game
	else if (mainWindow.IsKeyPressed(GLFW_KEY_ESCAPE) && gameState == GameState::MENU)
		mainWindow.SetShouldClose(true);

	if (gameState == GameState::RUN)
	{
	
		if (!player.GetIsDead())
		{
			if (mainWindow.IsKeyPressed(GLFW_KEY_A) && !player.GetIsAttacking())
			{
				if (previusKeyPressed != GLFW_KEY_A)
					player.ResetAnimation(PlayerState::RUN);

				previusKeyPressed = GLFW_KEY_A;

				if(player.GetIsOnGround())
					player.SetState(PlayerState::RUN);

				player.SetOrientation(PlayerOrientation::LEFT);
				player.SetVelocityX(-1.0f);
			}
			else if (mainWindow.IsKeyPressed(GLFW_KEY_D) && !player.GetIsAttacking())
			{
				if (previusKeyPressed != GLFW_KEY_D)
					player.ResetAnimation(PlayerState::RUN);

				previusKeyPressed = GLFW_KEY_D;

				if (player.GetIsOnGround())
					player.SetState(PlayerState::RUN);

				player.SetOrientation(PlayerOrientation::RIGHT);
				player.SetVelocityX(1.0f);
			}
			else
			{
				player.SetVelocityX(0.0f);

				if (player.GetIsOnGround() && !player.GetIsAttacking())
					player.SetState(PlayerState::IDLE);
				else if (!player.GetIsOnGround())
					player.SetState(PlayerState::JUMP);
			}

			if (mainWindow.IsKeyPressed(GLFW_KEY_SPACE) && player.GetIsOnGround() && !player.GetIsAttacking())
			{
				player.SetState(PlayerState::JUMP);
				player.SetVelocityY(2.0f);
			}
			else if (mainWindow.IsKeyPressed(GLFW_KEY_E) && player.GetIsOnGround() && !player.GetIsAttacking())
			{
				player.SetIsAttacking(true);
				player.SetState(PlayerState::ATTACK);
			}
		}
	}
}

void Game::Update(Level& level)
{
	// checks if player is colliding with any objects in game such as traps and if so, damages the player if necessary
	level.UpdateAssets(deltaTime);

	// handles enemy related stuff such as damage to player
	level.RunEnemyBehaviour(deltaTime);

	if (player.GetIsDead())
		player.SetState(PlayerState::DEATH);

	player.Update(deltaTime);

	level.ProcessPlayerCollisionWithBlocks();

	if (level.levelComplete)
	{
		levelLoadTimer = 5.0f;
		advanceLevel = true;
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
		renderer->Draw(*menu, 0, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(mainWindow.GetBufferWidth(), mainWindow.GetBufferHeight()), 0.0f);
		menu->Unbind();
		delete menu;
	}
	else if(gameState == GameState::RUN)
	{
		glm::mat4 view = glm::mat4(1.0f);
		view = player.GetCameraViewMatrix();
		shaders[SHADER_SPRITE]->SetUniformMat4("view", &view);

		level.Draw(mainWindow, deltaTime);

		level.SetAnimationToAllAliveEnemies(EnemyState::IDLE);
	}
	else
	{
		// process quitting
	}
	mainWindow.SwapBuffers();
}
