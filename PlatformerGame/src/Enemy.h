#pragma once

#include <glm/glm.hpp>

#include "SpriteRenderer.h"
#include "Player.h"

#include <vector>

enum class EnemyState
{
	IDLE,
	RUN,
	JUMP,
	FALL,
	DEATH,
	ATTACK
};

enum class EnemyOrientation
{
	RIGHT,
	LEFT
};

enum class EnemyType
{
	SPEARMAN
};

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void Draw(SpriteRenderer& renderer);
	void Move(float deltaTime);

	// this acts as the gravity in the game.cpp. Gets activated if gravity is enabled in the level
	void MoveDown(float deltaTime);

	GLboolean CheckIfHasSeenPlayer(const Player& player);

	void AddPatrolPoint(glm::vec3 patrolPoint);
	void MoveTowardsNextPatrolPoint(float deltaTime);

	void TakeDamage(GLfloat damage);

	// returns true when enemy has reached melee range to attack player
	GLboolean MoveTowardsPlayer(const Player& player, float deltaTime);

	void SetPosition(glm::vec3 newPosition) { position = newPosition; }
	void SetOrientation(EnemyOrientation newOrientation) { orientation = newOrientation; }
	void SetState(EnemyState newState) { state = newState; }
	void SetHasCollided(GLboolean newHasCollided) { hasCollided = newHasCollided; }
	void SetHealth(GLfloat newHealth) { health = newHealth; }
	void SetIsDead(GLboolean newIsDead) { isDead = newIsDead; }

	void ResetAnimation(EnemyState animationToReset);

	glm::vec3 GetPosition()const { return position; }
	EnemyOrientation GetOrientation()const { return orientation; }
	glm::vec2 GetSize()const { return size; }
	glm::vec3 GetPreviousPosition()const { return previousPosition; }
	GLboolean GetHasCollided()const { return hasCollided; }
	GLfloat GetHealth()const { return health; }
	GLboolean GetIsDead()const { return isDead; }
	EnemyState GetState()const { return state; }
	GLfloat GetLineOfSightX()const { return lineOfSightX; }
	EnemyType GetEnemyType()const { return enemyType; }

protected:
	std::vector<Texture2D*> texturesIdle{};
	std::vector<Texture2D*> texturesRun{};
	std::vector<Texture2D*> texturesJump{};
	std::vector<Texture2D*> texturesDeath{};
	std::vector<Texture2D*> texturesMeleeAttack{};
	Texture2D* textureFall{};

	glm::vec2 textureOffset{};
	glm::vec2 textureScale{}; // the "textureZoom" variable in the renderer draw functions. TODO consider renaming it to textureScale

	EnemyState state{};
	EnemyOrientation orientation{};

	unsigned int idleTexIterator{};
	unsigned int runTexIterator{};
	unsigned int jumpTexIterator{};
	unsigned int deathTexIterator{};
	unsigned int meleeAttackIterator{};

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

	GLboolean hasCollided{ false };

	GLfloat lineOfSightX{};

	std::vector<glm::vec3> patrolPoints{};
	GLuint previousPatrolPointIndex{};
	GLuint nextPatrolPointIndex{};

	GLfloat meleeRange{};
	GLboolean isInRange{ false };
	GLboolean hasSpottedPlayer{ false };

	EnemyType enemyType{};
};