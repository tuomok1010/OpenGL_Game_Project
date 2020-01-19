#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "SpriteRenderer.h"
#include "Camera.h"
#include "BloodEffect.h"
#include "PuffEffect.h"

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
	void Update(float deltaTime);

	GLboolean IsMeleeAttackFinished();

	void DrawBloodEffect(SpriteRenderer& renderer);
	void ResetBloodAnimation();
	void DrawPuffEffect(SpriteRenderer& renderer);
	
	void IncrementScore(GLint amountToAdd) { score += amountToAdd; }

	void SetPosition(glm::vec3 newPosition);
	void SetOrientation(PlayerOrientation newOrientation);
	void SetState(PlayerState newState);
	void SetHasCollided(GLboolean hasCollided);
	void SetHealth(GLfloat newHealth);
	void SetIsDead(GLboolean isDead);
	void SetIsInMeleeRange(GLboolean newVal) { isInMeleeRange = newVal; }
	void SetShouldBleed(GLboolean newVal) { shouldBleed = newVal; }
	void SetVelocityX(GLfloat val) { velocityX = val; }
	void SetVelocityY(GLfloat val) { velocityY = val; }
	void SetIsOnGround(GLboolean newVal) { isOnGround = newVal; }
	void SetIsAttacking(GLboolean newVal) { isAttacking = newVal; }
	void SetColor(glm::vec3 newColor) { color = newColor; }

	void ResetAnimation(PlayerState animationToReset);

	glm::mat4 GetCameraViewMatrix() { return camera.GetViewMatrix(); }
	glm::vec3 GetPosition()const { return position; }
	glm::vec2 GetSize()const { return size; }
	glm::vec3 GetPreviousPosition()const { return previousPosition; }
	GLboolean GetHasCollided()const { return hasCollided; }
	GLfloat GetHealth()const { return health; }
	GLboolean GetIsDead()const { return isDead; }
	PlayerState GetState()const { return state; }
	PlayerOrientation GetOrientation()const { return orientation; }
	GLboolean GetIsInMeleeRange()const { return isInMeleeRange; }
	GLfloat GetDamage()const { return damage; }
	GLboolean GetShouldDespawn()const { return readyToDespawn; }
	GLboolean GetIsOnGround()const { return isOnGround; }
	GLboolean GetIsAttacking()const { return isAttacking; }
	GLuint GetScore()const { return score; }

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
	GLfloat velocityX{};
	GLfloat velocityY{};
	GLfloat speed{};
	GLfloat gravity{};
	GLboolean isOnGround{ true };

	GLfloat health{};
	GLboolean isDead{ false };
	GLfloat damage{};
	GLboolean shouldBleed{ false };

	BloodEffect bloodEffect;
	PuffEffect puffEffect;
	GLboolean readyToDespawn{ false };

	// TODO consider removing as it is not used anywhere(i think...)
	GLboolean hasCollided{ false };

	Camera camera;
	// centers the camera so that the player character is in the niddle of the screen
	glm::vec3 cameraOffset{ -400, -300, 0 };

	GLboolean isInMeleeRange{ false };
	GLboolean isAttacking{ false };

	GLuint score{};
};