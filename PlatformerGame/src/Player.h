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
	void Jump();
	void MoveDown(float deltaTime);

	void SetPosition(glm::vec3 newPosition);
	void SetOrientation(PlayerOrientation newOrientation);
	void SetState(PlayerState newState);

	glm::mat4 GetCameraViewMatrix() { return camera.GetViewMatrix(); }
	glm::vec3 GetPosition()const { return position; }
	glm::vec2 GetSize()const { return size; }
	glm::vec3 GetPreviousPosition()const { return previousPosition; }

private:
	std::vector<Texture2D*> texturesIdle;
	std::vector<Texture2D*> texturesRun;
	std::vector<Texture2D*> texturesJump;
	Texture2D* textureFall;

	glm::vec2 textureOffset{};

	PlayerState state{};
	PlayerOrientation orientation{};

	int textureIterator{};
	glm::vec3 previousPosition{};

	glm::vec3 position{};
	glm::vec2 size{};
	glm::vec3 color{};
	GLfloat rotation{};
	GLfloat speed{};

	Camera camera;
	// centers the camera so that the player character is in the niddle of the screen
	glm::vec3 cameraOffset{ -400, -300, 0 };
};