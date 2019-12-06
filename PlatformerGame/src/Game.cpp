#include "Game.h"

#include <iostream>



Game::Game(int scrnWidth, int scrnHeight)
	: 
	mainWindow(scrnWidth, scrnHeight), 
	projection(glm::mat4(1.0f)),
	model(glm::mat4(1.0f)),
	view(glm::mat4(1.0f))
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
		// Pos				// Tex coords
		-0.5f, -0.5f,		0.0f, 0.0f,
		 0.5f, -0.5f,		1.0f, 0.0f,
		-0.5f,  0.5f,		0.0f, 1.0f,
		 0.5f,  0.5f,		1.0f, 1.0f
	};

	unsigned int indices[]
	{
		0, 1, 2,
		3, 2, 1,
	};

	Texture2D smiley("../textures/smiley03b.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
	smiley.Bind(0);

	meshList.emplace_back(new Mesh(vertices, indices, 16, 6));
	meshList[0]->SetLayout(0, 2, GL_FLOAT, 4 * sizeof(GLfloat), 0);
	meshList[0]->SetLayout(1, 2, GL_FLOAT, 4 * sizeof(GLfloat), 2 * sizeof(GLfloat));

	shaders[0]->Bind();
	shaders[0]->SetUniformi("ourTexture", 0);

	projection = glm::mat4(1.0f);
	projection = glm::ortho(0.0f, (float)mainWindow.GetBufferWidth(), 0.0f, (float)mainWindow.GetBufferHeight(), 0.1f, 100.0f);

	float rotation = 0.0f;
	float xPos = 0.0f; 
	float yPos = 0.0f;

	while (!mainWindow.GetShouldClose())
	{
		mainWindow.PollEvents();

		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (mainWindow.IsKeyPressed(GLFW_KEY_E))
			rotation += 1.0f;

		if (mainWindow.IsKeyPressed(GLFW_KEY_Q))
			rotation -= 1.0f;

		if (rotation >= 360.0f)
			rotation = 0.0f;
		else if (rotation <= -360.0f)
			rotation = 0.0f;

		if (mainWindow.IsKeyPressed(GLFW_KEY_D))
			xPos += 1.0f;

		if (mainWindow.IsKeyPressed(GLFW_KEY_A))
			xPos -= 1.0f;

		if (mainWindow.IsKeyPressed(GLFW_KEY_W))
			yPos += 1.0f;

		if (mainWindow.IsKeyPressed(GLFW_KEY_S))
			yPos -= 1.0f;
	
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(xPos, yPos, 0.0f));
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 1.0f));

		view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3((float)mainWindow.GetBufferWidth() / 2, (float)mainWindow.GetBufferHeight() / 2, -3.0f));

		shaders[0]->SetUniformMat4("model", &model);
		shaders[0]->SetUniformMat4("view", &view);
		shaders[0]->SetUniformMat4("projection", &projection);

		meshList[0]->Render();

		mainWindow.SwapBuffers();
	}

	for (int i = 0; i < meshList.size(); ++i)
		meshList[i]->Clear();

	glfwTerminate();
}
