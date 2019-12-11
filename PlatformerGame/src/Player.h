#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "SpriteRenderer.h"

enum PlayerState
{
	IDLE,
	RUN_RIGHT,
	JUMPING,
	FALLING
};

class Player
{
public:
	Player();
	~Player();

	void Draw(SpriteRenderer& renderer);

	void SetPosition(glm::vec2 newPosition);

private:
	std::vector<Texture2D*> texturesIdle;
	std::vector<Texture2D*> texturesRun;
	std::vector<Texture2D*> texturesJump;
	PlayerState state{};

	int textureIterator{};

	glm::vec2 position{};
	glm::vec2 size{};
	glm::vec2 velocity{};
	glm::vec3 color{};
	GLfloat rotation{};
};