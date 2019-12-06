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
		// Pos				// Tex coords
		-1.0f,  0.5f,		0.0f, 0.0f,
		-0.5f,  0.5f,		1.0f, 0.0f,
		-1.0f,  1.0f,		0.0f, 1.0f,
		-0.5f,  1.0f,		1.0f, 1.0f
	};

	GLfloat vertices2[]
	{
		// Pos				// Tex coords
		 0.5f,  0.5f,		0.0f, 0.0f,
		 1.0f,  0.5f,		1.0f, 0.0f,
		 0.5f,  1.0f,		0.0f, 1.0f,
		 1.0f,  1.0f,		1.0f, 1.0f
	};

	GLfloat vertices3[]
	{	// Pos				// Tex coords
		-0.25f, -0.25f,		0.0f, 0.0f,
		 0.25f, -0.25f,		1.0f, 0.0f,
		-0.25f,  0.25f,		0.0f, 1.0f,
		 0.25f,  0.25f,		1.0f, 1.0f
	};

	unsigned int indices[]
	{
		0, 1, 2,
		3, 2, 1,
	};

	Texture2D smiley("../textures/smiley03b.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
	smiley.Bind(0);

	// Using the first Mesh constructor
	Mesh obj1(vertices, indices, 16, 6);
	obj1.SetLayout(0, 2, GL_FLOAT, 4 * sizeof(GLfloat), 0);
	obj1.SetLayout(1, 2, GL_FLOAT, 4 * sizeof(GLfloat), 2 * sizeof(GLfloat));

	// Using the second Mesh constructor
	VertexBuffer VBO(vertices2, 16);
	IndexBuffer IBO(indices, 6);
	Mesh obj2(VBO, IBO);
	obj2.SetLayout(0, 2, GL_FLOAT, 4 * sizeof(GLfloat), 0);
	obj2.SetLayout(1, 2, GL_FLOAT, 4 * sizeof(GLfloat), 2 * sizeof(GLfloat));

	// Using the third Mesh constructor
	VertexArray VAO(vertices3, indices, 16, 6);
	Mesh obj3(VAO);
	obj3.SetLayout(0, 2, GL_FLOAT, 4 * sizeof(GLfloat), 0);
	obj3.SetLayout(1, 2, GL_FLOAT, 4 * sizeof(GLfloat), 2 * sizeof(GLfloat));


	shaders[0]->Bind();
	shaders[0]->SetUniformi("ourTexture", 0);

	while (!mainWindow.GetShouldClose())
	{
		mainWindow.PollEvents();

		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		obj1.Render();
		obj2.Render();
		obj3.Render();

		mainWindow.SwapBuffers();
	}
}
