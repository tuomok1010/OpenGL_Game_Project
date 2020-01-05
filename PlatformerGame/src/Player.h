#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "SpriteRenderer.h"
#include "Camera.h"
#include "BloodEffect.h"

enum class PlayerState
{
	IDLE,
	RUN,
	JUMP,
	FALL,
	DEATH,
	ATTACK
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
	//void ResetHeightJumped() { heightJumped = 0.0f; } // not used anywhere
	GLboolean MeleeAttack();

	// this acts as the gravity in the game.cpp. Gets activated if gravity is enabled in the level
	void MoveDown(float deltaTime);

	void DrawBlood(SpriteRenderer& renderer);

	void SetPosition(glm::vec3 newPosition);
	void SetOrientation(PlayerOrientation newOrientation);
	void SetState(PlayerState newState);
	void SetHasCollided(GLboolean hasCollided);
	void SetHealth(GLfloat newHealth);
	void SetIsDead(GLboolean isDead);
	void SetShouldBleed(GLboolean newShouldBleed);
	void SetDamageDirection(DamageDirection newDirection);

	void ResetAnimation(PlayerState animationToReset);

	glm::mat4 GetCameraViewMatrix() { return camera.GetViewMatrix(); }
	glm::vec3 GetPosition()const { return position; }
	glm::vec2 GetSize()const { return size; }
	glm::vec3 GetPreviousPosition()const { return previousPosition; }
	GLboolean GetHasCollided()const { return hasCollided; }
	GLfloat GetHealth()const { return health; }
	GLboolean GetIsDead()const { return isDead; }
	PlayerState GetState()const { return state; }

private:
	std::vector<Texture2D*> texturesIdle{};
	std::vector<Texture2D*> texturesRun{};
	std::vector<Texture2D*> texturesJump{};
	std::vector<Texture2D*> texturesDeath{};
	std::vector<Texture2D*> texturesMeleeAttack{};
	Texture2D* textureFall{};

	glm::vec2 textureOffset{};
	glm::vec2 textureScale{}; // the "textureZoom" variable in the renderer draw functions

	PlayerState state{};
	PlayerOrientation orientation{};

	GLuint idleTexIterator{};
	GLuint runTexIterator{};
	GLuint jumpTexIterator{};
	GLuint deathTexIterator{};
	GLuint meleeAttackIterator{};

	glm::vec3 previousPosition{};

	glm::vec3 position{};
	glm::vec2 size{};
	glm::vec3 color{};
	GLfloat rotation{};
	GLfloat speed{};

	GLfloat maxJumpHeight{};
	GLfloat heightJumped{};

	GLfloat health{};
	GLboolean isDead{ false };

	// TODO consider removing as it is not used anywhere(i think...)
	GLboolean hasCollided{ false };

	BloodEffect bloodEffect;
	GLboolean shouldBleed{ false };

	Camera camera;
	// centers the camera so that the player character is in the niddle of the screen
	glm::vec3 cameraOffset{ -400, -300, 0 };


};