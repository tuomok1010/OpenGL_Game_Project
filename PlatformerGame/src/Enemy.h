#pragma once

#include <glm/glm.hpp>

#include "SpriteRenderer.h"
#include "PrimitiveRenderer.h"
#include "Player.h"
#include "CollisionBox.h"

#include <vector>

#define LINE_OF_SIGHT_DEFAULT_X 250.0f

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
	SPEARMAN,
	TARGET
};

class Enemy
{
public:
	Enemy();
	Enemy(const Enemy& src);
	virtual ~Enemy();

	virtual void Draw(SpriteRenderer& renderer, PrimitiveRenderer& collisionBoxRenderer, GLboolean drawCollisionBoxes = false);
	virtual void DrawPuffEffect(SpriteRenderer& renderer);

	virtual void Update(GLfloat deltaTime);

	GLboolean CheckIfHasSeenPlayer(const Player& player);

	void AddPatrolPoint(glm::vec3 patrolPoint);
	void MoveTowardsNextPatrolPoint(float deltaTime);

	void TakeDamage(GLfloat damage);

	// returns true when enemy has reached melee range to attack player
	GLboolean MoveTowardsPlayer(const Player& player, float deltaTime);

	// retuns an int based on which collision box is colliding. 0 = no collision, 1 = bottom, 2 = right, 3 = left, 4 = top
	GLint AdvancedCollisionCheck(GameObject& obj);

	GLboolean SimpleCollisionCheck(GameObject& obj);

	void SetPosition(glm::vec3 newPosition) { position = newPosition; }
	void SetOrientation(EnemyOrientation newOrientation) { orientation = newOrientation; }
	void SetState(EnemyState newState) { state = newState; }
	void SetHasCollided(GLboolean newHasCollided) { hasCollided = newHasCollided; }
	void SetHealth(GLfloat newHealth) { health = newHealth; }
	void SetIsDead(GLboolean newIsDead) { isDead = newIsDead; }
	void SetVelocityX(GLfloat val) { velocity.x = val; }
	void SetVelocityY(GLfloat val) { velocity.y = val; }
	void SetIsOnGround(GLboolean newVal) { isOnGround = newVal; }

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
	GLboolean GetShouldDespawn()const { return readyToDespawn; }
	glm::vec2 GetVelocity()const { return velocity; }
	GLboolean GetIsOnGround()const { return isOnGround; }

	CollisionBox GetCollisionBoxBottom()const { return collisionBottom; }
	CollisionBox GetCollisionBoxTop()const { return collisionTop; }
	CollisionBox GetCollisionBoxLeft()const { return collisionLeft; }
	CollisionBox GetCollisionBoxRight()const { return collisionRight; }

protected:
	std::vector<Texture2D*> texturesIdle{};
	std::vector<Texture2D*> texturesRun{};
	std::vector<Texture2D*> texturesJump{};
	std::vector<Texture2D*> texturesDeath{};
	std::vector<Texture2D*> texturesMeleeAttack{};
	Texture2D* textureFall{};

	glm::vec2 textureOffset;
	glm::vec2 textureScale; // the "textureZoom" variable in the renderer draw functions. TODO consider renaming it to textureScale

	EnemyState state{};
	EnemyOrientation orientation{};

	unsigned int idleTexIterator{};
	unsigned int runTexIterator{};
	unsigned int jumpTexIterator{};
	unsigned int deathTexIterator{};
	unsigned int meleeAttackIterator{};

	glm::vec3 previousPosition{};
	glm::vec3 position;
	glm::vec2 size{};
	glm::vec3 color;
	GLfloat rotation;
	glm::vec2 velocity;
	GLfloat speed;
	GLfloat gravity;
	GLboolean isOnGround{ true };

	GLfloat health{};
	GLboolean isDead{ false };
	GLboolean readyToDespawn{ false };

	GLboolean hasCollided{ false };

	std::vector<glm::vec3> patrolPoints{};
	GLuint previousPatrolPointIndex{};
	GLuint nextPatrolPointIndex{};
	glm::vec3 initialPosition{};	// the position the enemy spawns in

	GLfloat lineOfSightX;
	GLboolean isInRange{ false };
	GLboolean hasSpottedPlayer{ false };
	GLfloat meleeRange{};

	EnemyType enemyType{};

	PuffEffect puffEffect;

	CollisionBox collisionBottom;
	CollisionBox collisionTop;
	CollisionBox collisionLeft;
	CollisionBox collisionRight;
	CollisionBox collisionBoxSimple;

	const GLfloat collisionBoxThickness = 10.0f;
	const GLfloat collisionBoxHorizontalLength = 30.0f;
	const GLfloat collisionBoxVerticalLength = 80.0f;

	glm::vec2 colBoxOffsetBottom{};
	glm::vec2 colBoxOffsetTop{};
	glm::vec2 colBoxOffsetRight{};
	glm::vec2 colBoxOffsetLeft{};
	glm::vec2 colBoxOffsetSimple{};
};