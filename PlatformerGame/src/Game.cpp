#include "Game.h"

#include <iostream>

// shader indices
#define SHADER_BASIC	0
#define SHADER_BLOCK	1
#define SHADER_PLAYER	2

// texture indices
#define TEXTURE_SMILEY	0
#define TEXTURE_PLAYER	1
#define TEXTURE_BLOCK	2

Game::Game(int scrnWidth, int scrnHeight)
	: 
	mainWindow(scrnWidth, scrnHeight), 
	projection(glm::mat4(1.0f))
{
	//projection = glm::ortho(0.0f, (float)mainWindow.GetBufferWidth(), 0.0f, (float)mainWindow.GetBufferHeight(), -1.0f, 1.0f);
	projection = glm::ortho(0.0f, (float)mainWindow.GetBufferWidth(), 0.0f, (float)mainWindow.GetBufferHeight(), -1.0f, 1.0f);

	// init shaders list
	shaders.emplace_back(new Shader("shaders/shader.vert", "shaders/shader.frag"));
	shaders.emplace_back(new Shader("shaders/simple_sprite.vert", "shaders/simple_sprite.frag"));

	// init textures
	textures.emplace_back(new Texture2D("../textures/smiley03b.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	textures.emplace_back(new Texture2D("../textures/smiley30b.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	textures.emplace_back(new Texture2D("../textures/TexturesCom_Brick_Rustic2_512_albedo.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
}

Game::~Game()
{
	for (int i = 0; i < shaders.size(); ++i)
		delete shaders[i];

	for (int i = 0; i < textures.size(); ++i)
		delete textures[i];
}

void Game::Run()
{
	SpriteRenderer block(*shaders[SHADER_BLOCK]);

	GLfloat rotation = 0.0f;
	glm::vec2 pos = glm::vec2(0.0f, 0.0f);
	glm::vec2 size = glm::vec2(50, 50);

	GameObject object(pos, size, *textures[TEXTURE_BLOCK]);

	Level lvl(*shaders[SHADER_BLOCK], block, *textures[TEXTURE_BLOCK]);
	lvl.Load("../levels/OpenGLGame_Level1.txt");

	while (!mainWindow.GetShouldClose())
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if (mainWindow.IsKeyPressed(GLFW_KEY_D))
			camera.Move(CameraDirection::RIGHT, deltaTime);
		if (mainWindow.IsKeyPressed(GLFW_KEY_A))
			camera.Move(CameraDirection::LEFT, deltaTime);
		if (mainWindow.IsKeyPressed(GLFW_KEY_W))
			camera.Move(CameraDirection::UP, deltaTime);
		if (mainWindow.IsKeyPressed(GLFW_KEY_S))
			camera.Move(CameraDirection::DOWN, deltaTime);

		mainWindow.PollEvents();

		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaders[SHADER_BLOCK]->SetUniformMat4("projection", &projection);

		glm::mat4 view = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		shaders[SHADER_BLOCK]->SetUniformMat4("view", &view);

		//object.Draw(block, 0);
		lvl.Draw();

		mainWindow.SwapBuffers();
	}

	glfwTerminate();
}
