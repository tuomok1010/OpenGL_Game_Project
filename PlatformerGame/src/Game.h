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

enum class GameState
{
	MENU,
	RUN,
	QUIT
};

class Game
{
public:
	Game(int scrnWidth, int scrnHeight);
	~Game();

	void Run();
	void ProcessInput(Level& level);
	void Draw(Level& level);
	void DrawRetryMenu();

public:
private:
private:
	Window mainWindow;
	float deltaTime{};
	float lastFrame{};
	GameState gameState;
	GLuint levelNumber{};
	GLboolean advanceLevel{ true };

	GLint previusKeyPressed{};

	glm::mat4 projection{};
	SpriteRenderer* renderer{};

	std::vector<Shader*> shaders{};
	Level* level{};

	Player player;

	bool canJumpAgain{ true };
	GLfloat jumpCooldown{};
	bool canAttackAgain{ true };
	GLfloat attackCooldown{};
};

