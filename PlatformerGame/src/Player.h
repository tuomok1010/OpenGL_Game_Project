#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "SpriteRenderer.h"
#include "PrimitiveRenderer.h"
#include "CollisionBox.h"
#include "Camera.h"
#include "BloodEffect.h"
#include "PuffEffect.h"
#include "GameObject.h"
#include "Coin.h"

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

	void Draw(SpriteRenderer& renderer, PrimitiveRenderer& collisionBoxRenderer, GLboolean drawCollisionBoxes = false);
	void Update(float deltaTime);

	GLboolean IsMeleeAttackFinished();

	void DrawBloodEffect(SpriteRenderer& renderer);
	void ResetBloodAnimation();
	void DrawPuffEffect(SpriteRenderer& renderer);
	void IncrementScore(GLint amountToAdd) { score += amountToAdd; }
	void ResetSpeed() { speed = 200.0f; }

	// retuns an int based on which collision box is colliding. 0 = no collision, 1 = bottom, 2 = right, 3 = left, 4 = top
	GLint AdvancedCollisionCheck(GameObject& obj);

	// uses only one large collision box to check if it is overlapping with the obj
	GLboolean SimpleCollisionCheck(GameObject& obj);
	GLboolean SimpleCollisionCheck(Coin& coin);
	GLboolean SimpleCollisionCheck(CollisionBox& colBox);

	void SetPosition(glm::vec3 newPosition);
	void SetOrientation(PlayerOrientation newOrientation);
	void SetState(PlayerState newState);
	void SetHasCollided(GLboolean hasCollided);
	void SetHealth(GLint newHealth);
	void SetIsDead(GLboolean isDead);
	void SetIsInMeleeRange(GLboolean newVal) { isInMeleeRange = newVal; }
	void SetShouldBleed(GLboolean newVal) { shouldBleed = newVal; }
	void SetVelocityX(GLfloat val) { velocity.x = val; }
	void SetVelocityY(GLfloat val) { velocity.y = val; }
	void SetIsOnGround(GLboolean newVal) { isOnGround = newVal; }
	void SetIsAttacking(GLboolean newVal) { isAttacking = newVal; }
	void SetColor(glm::vec3 newColor) { color = newColor; }
	void SetScore(GLuint newScore) { score = newScore; }
	void SetLives(GLuint amount) { lives = amount; }
	void SetIsOnMovingSurface(GLboolean newVal) { isOnMovingSurface = newVal; }
	void SetSpeed(GLfloat newSpeed) { speed = newSpeed; }

	void ResetAnimation(PlayerState animationToReset);

	glm::mat4 GetCameraViewMatrix() { return camera.GetViewMatrix(); }
	glm::vec3 GetCameraPos()const { return camera.GetPosition(); }
	glm::vec3 GetPosition()const { return position; }
	glm::vec2 GetSize()const { return size; }
	glm::vec3 GetPreviousPosition()const { return previousPosition; }
	GLboolean GetHasCollided()const { return hasCollided; }
	GLint GetHealth()const { return health; }
	GLboolean GetIsDead()const { return isDead; }
	PlayerState GetState()const { return state; }
	PlayerOrientation GetOrientation()const { return orientation; }
	GLboolean GetIsInMeleeRange()const { return isInMeleeRange; }
	GLfloat GetDamage()const { return damage; }
	GLboolean GetShouldDespawn()const { return readyToDespawn; }
	GLboolean GetIsOnGround()const { return isOnGround; }
	GLboolean GetIsAttacking()const { return isAttacking; }
	GLuint GetScore()const { return score; }
	GLuint GetLives()const { return lives; }
	glm::vec2 GetVelocity()const { return velocity; }
	GLboolean GetIsOnMovingSurface()const { return isOnMovingSurface; }

	CollisionBox GetCollisionBoxBottom()const { return collisionBottom; }
	CollisionBox GetCollisionBoxTop()const { return collisionTop; }
	CollisionBox GetCollisionBoxLeft()const { return collisionLeft; }
	CollisionBox GetCollisionBoxRight()const { return collisionRight; }

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
	glm::vec2 velocity{};
	GLfloat speed{};
	GLfloat gravity{};
	GLboolean isOnGround{ true };

	GLint health{};
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
	GLuint lives{};

	CollisionBox collisionBottom;
	CollisionBox collisionTop;
	CollisionBox collisionRight;
	CollisionBox collisionLeft;
	CollisionBox collisionBoxSimple;

	const GLfloat collisionBoxThickness = 10.0f;
	const GLfloat collisionBoxHorizontalLength = 30.0f;
	const GLfloat collisionBoxVerticalLength = 80.0f;
	
	glm::vec2 colBoxOffsetBottom{};
	glm::vec2 colBoxOffsetTop{};
	glm::vec2 colBoxOffsetRight{};
	glm::vec2 colBoxOffsetLeft{};
	glm::vec2 colBoxOffsetSimple{};

	GLboolean isOnMovingSurface{ false };
};