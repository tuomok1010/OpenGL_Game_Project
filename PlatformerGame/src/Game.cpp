#include "Game.h"

#include <iostream>

// shader indices
#define SHADER_BASIC	0
#define SHADER_SPRITE	1

// used in the ProcessInput function to reset the jumpCooldown and attackCooldown variables
#define JUMP_COOLDOWN 1
#define ATTACK_COOLDOWN 1

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

			std::string levelNumberString = std::to_string(levelNumber);
			std::string levelPath = "../levels/OpenGLGame_Level" + levelNumberString + ".txt";
			std::string backGroundPath = "../textures/backGround" + levelNumberString + ".jpg"; // the backGround image must be in jpg format with no alpha channel
			
			level->Load(levelPath, backGroundPath);
			advanceLevel = false;
		}
		if (level->quitGame)
			gameState = GameState::QUIT;

		if (gameState == GameState::QUIT)
			mainWindow.SetShouldClose(true);

		ProcessInput(*level);

		Draw(*level);

	}

	glfwTerminate();
}

void Game::ProcessInput(Level& level)
{
	/*
		TODO fix: The SetPosition and GetPrevious position is used with the collision detection. However, 
		sometimes when the player jumps and falls back to the ground, instead of falling completely to the ground and touching it,
		he remains slightly in the air. <-- this is most likely because of lost frames. Running the game in release mode minimizes this issue.
		Should still look for a proper solution for it. 
	*/

	// Starts the game
	if (mainWindow.IsKeyPressed(GLFW_KEY_SPACE) && gameState == GameState::MENU)
		gameState = GameState::RUN;
	// exits the game
	else if (mainWindow.IsKeyPressed(GLFW_KEY_ESCAPE) && gameState == GameState::MENU)
		mainWindow.SetShouldClose(true);

	if (gameState == GameState::RUN)
	{
		// checks if player is colliding with any objects in game such as traps and if so, damages the player if necessary
		level.UpdateAssets(deltaTime);

		// handles enemy related stuff such as damage to player
		level.RunEnemyBehaviour(deltaTime);

		if (player.GetIsDead())
			player.SetState(PlayerState::DEATH);

		// The MoveDown function basically acts as gravity
		if (level.gravityEnabled)
		{
			player.MoveDown(deltaTime);
			if (level.IsPlayerCollidingWithBlocks())
			{
				// if player is jumping, this will reset the animation to idle when he collides with the ground again
				if(!player.GetIsDead())
					player.SetState(PlayerState::IDLE);

				player.SetPosition(player.GetPreviousPosition());
			}
			else
			{
				// if player falls downwards without the player having pressed the jump button(falling off a ledge for example), this will make sure that the jump animation is used when he falls
				player.SetState(PlayerState::JUMP);
			}
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

				if (level.IsPlayerCollidingWithBlocks())
					player.SetPosition(player.GetPreviousPosition());
			}
			else if (mainWindow.IsKeyPressed(GLFW_KEY_A))
			{
				if (previusKeyPressed != GLFW_KEY_A)
					player.ResetAnimation(PlayerState::RUN);

				previusKeyPressed = GLFW_KEY_A;
				player.SetOrientation(PlayerOrientation::LEFT);
				player.Move(deltaTime);

				if (level.IsPlayerCollidingWithBlocks())
					player.SetPosition(player.GetPreviousPosition());
			}
			// Jump logic **********************************
			if (mainWindow.IsKeyPressed(GLFW_KEY_SPACE) && canJumpAgain)
			{
				if (previusKeyPressed != GLFW_KEY_SPACE)
					player.ResetAnimation(PlayerState::JUMP);

				previusKeyPressed = GLFW_KEY_SPACE;

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

				if (level.IsPlayerCollidingWithBlocks())
					player.SetPosition(player.GetPreviousPosition());
			}
			jumpCooldown -= deltaTime;

			// ***********************************************

			if (mainWindow.IsKeyPressed(GLFW_KEY_E) && canAttackAgain)
			{
				if (previusKeyPressed != GLFW_KEY_E)
					player.ResetAnimation(PlayerState::ATTACK);

				previusKeyPressed = GLFW_KEY_E;

				if (attackCooldown <= 0.0f)
				{
					canAttackAgain = false;
					attackCooldown = ATTACK_COOLDOWN;
				}
			}

			if (!canAttackAgain)
			{
				if (!player.MeleeAttack())
					canAttackAgain = true;
			}
			attackCooldown -= deltaTime;
		}
	}
	if (level.levelComplete)
	{
		advanceLevel = true;
		++levelNumber;
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

		Texture2D* menu = new Texture2D("../textures/menu.jpg", GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
		renderer->Draw(*menu, 0, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(mainWindow.GetBufferWidth(), mainWindow.GetBufferHeight()), 0.0f);
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
