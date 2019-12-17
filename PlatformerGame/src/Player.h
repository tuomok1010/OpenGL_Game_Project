#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "SpriteRenderer.h"
#include "Camera.h"

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

	GLboolean Jump(float deltaTime, GLboolean& gravityEnabled);
	void ResetHeightJumped() { heightJumped = 0.0f; }

	// this acts as the gravity in the game.cpp. Gets activated if gravity is enabled in the level
	void MoveDown(float deltaTime);

	void SetPosition(glm::vec3 newPosition);
	void SetOrientation(PlayerOrientation newOrientation);
	void SetState(PlayerState newState);
	void SetHasCollided(GLboolean hasCollided);

	void ResetAnimation(PlayerState animationToReset);

	glm::mat4 GetCameraViewMatrix() { return camera.GetViewMatrix(); }
	glm::vec3 GetPosition()const { return position; }
	glm::vec2 GetSize()const { return size; }
	glm::vec3 GetPreviousPosition()const { return previousPosition; }
	GLboolean GetHasCollided()const { return hasCollided; }

private:
	std::vector<Texture2D*> texturesIdle;
	std::vector<Texture2D*> texturesRun;
	std::vector<Texture2D*> texturesJump;
	Texture2D* textureFall;

	glm::vec2 textureOffset{};

	PlayerState state{};
	PlayerOrientation orientation{};

	unsigned int idleTexIterator{};
	unsigned int runTexIterator{};
	unsigned int jumpTexIterator{};

	glm::vec3 previousPosition{};

	glm::vec3 position{};
	glm::vec2 size{};
	glm::vec3 color{};
	GLfloat rotation{};
	GLfloat speed{};

	GLfloat maxJumpHeight{};
	GLfloat heightJumped{};

	// TODO consider removing as it is not used anywhere(i think...)
	GLboolean hasCollided{ false };

	Camera camera;
	// centers the camera so that the player character is in the niddle of the screen
	glm::vec3 cameraOffset{ -400, -300, 0 };
};