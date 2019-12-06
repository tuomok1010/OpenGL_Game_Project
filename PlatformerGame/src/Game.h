#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture2D.h"

class Game
{
public:
	Game(int scrnWidth, int scrnHeight);
	~Game();

	void Run();

public:
private:
private:
	Window mainWindow;
	float deltaTime{};
	float lastFrame{};

	glm::mat4 projection{};
	glm::mat4 model{};
	glm::mat4 view{};

	std::vector<Shader*> shaders{};
	std::vector<Mesh*> meshList{};
};

