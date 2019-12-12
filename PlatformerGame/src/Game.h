#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "Level.h"
#include "Camera.h"
#include "Player.h"

class Game
{
public:
	Game(int scrnWidth, int scrnHeight);
	~Game();

	void Run();
	void ProcessInput();
	void Draw(Level& level);

public:
private:
private:
	Window mainWindow;
	float deltaTime{};
	float lastFrame{};

	glm::mat4 projection{};
	SpriteRenderer* renderer{};

	std::vector<Shader*> shaders{};

	Player player;
};

