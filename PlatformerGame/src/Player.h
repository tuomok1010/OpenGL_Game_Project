#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "SpriteRenderer.h"

enum class PlayerState
{
	IDLE,
	RUN,
	JUMP,
	FALL
};

enum class PlayerOrientation
{
	RIGHT,
	LEFT
};

class Player
{
public:
	Player();
	~Player();

	void Draw(SpriteRenderer& renderer);
	void Move(float deltaTime);
	void Jump();

	void SetPosition(glm::vec3 newPosition);
	void SetOrientation(PlayerOrientation newOrientation);
	void SetState(PlayerState newState);

private:
	std::vector<Texture2D*> texturesIdle;
	std::vector<Texture2D*> texturesRun;
	std::vector<Texture2D*> texturesJump;
	Texture2D* textureFall;

	glm::vec2 textureOffset{};

	PlayerState state{};
	PlayerOrientation orientation{};

	int textureIterator{};

	glm::vec3 position{};
	glm::vec2 size{};
	glm::vec3 color{};
	GLfloat rotation{};
	GLfloat speed{};
};