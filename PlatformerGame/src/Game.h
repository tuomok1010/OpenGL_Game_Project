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
#include "UI.h"

#define JUMP_COOLDOWN 1

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
	void Update(Level& level);
	void Draw(Level& level);

public:
private:
private:
	Window mainWindow;
	float deltaTime{};
	float lastFrame{};
	GameState gameState;
	GLboolean advanceLevel{ true };

	GLint previusKeyPressed{};

	glm::mat4 projection{};
	SpriteRenderer* renderer{};
	TextRenderer* textRenderer{};

	std::vector<Shader*> shaders{};
	Level* level{};

	Player player;

	UI* ui{};

	bool canAttackAgain{ true };
	GLfloat attackCooldown{};

	GLfloat jumpCooldown{};

	GLfloat levelLoadTimer{};
};

