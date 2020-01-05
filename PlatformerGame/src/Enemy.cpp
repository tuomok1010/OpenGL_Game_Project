#include "Enemy.h"

#include <iostream>

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	for (unsigned int i = 0; i < texturesIdle.size(); ++i)
	{
		texturesIdle.at(i)->Unbind();
		delete texturesIdle.at(i);
	}

	for (unsigned int i = 0; i < texturesRun.size(); ++i)
	{
		texturesRun.at(i)->Unbind();
		delete texturesRun.at(i);
	}

	for (unsigned int i = 0; i < texturesJump.size(); ++i)
	{
		texturesJump.at(i)->Unbind();
		delete texturesJump.at(i);
	}

	for (unsigned int i = 0; i < texturesDeath.size(); ++i)
	{
		texturesDeath.at(i)->Unbind();
		delete texturesDeath.at(i);
	}

	textureFall->Unbind();
	delete textureFall;
}

void Enemy::Draw(SpriteRenderer& renderer)
{
	// If the enemy is facing right, we do not need to rotate the sprite, if the sprite is facing left we set the axis of rotation to be the Y axis.
	glm::vec3 rotationAxiis = (orientation == EnemyOrientation::RIGHT) ? glm::vec3(0.0f, 0.0f, 1.0f) : glm::vec3(0.0f, 1.0f, 0.0f);

	// If the enemy is facing right, set rotation to 0.0f, if the sprite is facing left set rotation to 180.0f.
	rotation = (orientation == EnemyOrientation::RIGHT) ? 0.0f : 180.0f;

	if (state == EnemyState::IDLE)
	{
		if (idleTexIterator >= texturesIdle.size())
			idleTexIterator = 0;

		renderer.Draw(*texturesIdle.at(idleTexIterator), 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
		++idleTexIterator;
	}
	else if (state == EnemyState::RUN)
	{
		if (runTexIterator >= texturesRun.size())
			runTexIterator = 0;

		renderer.Draw(*texturesRun.at(runTexIterator), 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
		++runTexIterator;
	}
	else if (state == EnemyState::JUMP)
	{
		if (jumpTexIterator >= texturesJump.size())
			jumpTexIterator = texturesJump.size() - 1;

		renderer.Draw(*texturesJump.at(jumpTexIterator), 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
		++jumpTexIterator;
	}
	else if (state == EnemyState::FALL)
	{
		renderer.Draw(*textureFall, 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
	}
	else if (state == EnemyState::DEATH)
	{
		if (deathTexIterator >= texturesDeath.size())
			deathTexIterator = texturesDeath.size() - 1;

		renderer.Draw(*texturesDeath.at(deathTexIterator), 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
		++deathTexIterator;
	}
	else if (state == EnemyState::ATTACK)
	{
		if (meleeAttackIterator >= texturesMeleeAttack.size())
			meleeAttackIterator = 0;

		renderer.Draw(*texturesMeleeAttack.at(meleeAttackIterator), 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
		++meleeAttackIterator;
	}
}

void Enemy::Move(float deltaTime)
{
	GLfloat velocity = speed * deltaTime;
	state = EnemyState::RUN;

	switch (orientation)
	{
	case EnemyOrientation::RIGHT:
		previousPosition = position;
		position += glm::vec3(1.0f, 0.0f, 0.0f) * velocity;
		break;
	case EnemyOrientation::LEFT:
		previousPosition = position;
		position -= glm::vec3(1.0f, 0.0f, 0.0f) * velocity;
		break;
	}
}

void Enemy::MoveDown(float deltaTime)
{
	GLfloat velocity = speed * deltaTime;
	previousPosition = position;
	position -= glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
}

GLboolean Enemy::CheckIfHasSeenPlayer(const Player& player)
{
	GLboolean hasBeenSpotted{ false };

	glm::vec3 playerPos = player.GetPosition();
	glm::vec2 playerSize = player.GetSize();

	// check if the enemy if facing the player, thus would he be able to spot the player in the first place
	// && if the player is (about )in the same height on the y axiis as the enemy
	if (((position.x + (size.x / 2.0f) > playerPos.x + (size.x / 2.0f) && orientation == EnemyOrientation::LEFT) ||
		(position.x + (size.x / 2.0f) < playerPos.x + (size.x / 2.0f) && orientation == EnemyOrientation::RIGHT)) &&
		(playerPos.y + playerSize.y > position.y && position.y + size.y > playerPos.y))
	{
		if (orientation == EnemyOrientation::LEFT)
		{
			bool spotted = (playerPos.x + (playerSize.x / 2.0f)) >= (position.x - lineOfSightX);
			if (spotted)
			{
				std::cout << "Player was spotted by an enemy!" << std::endl;
				hasBeenSpotted = true;
			}
		}
		else if (orientation == EnemyOrientation::RIGHT)
		{
			bool spotted = (playerPos.x + (playerSize.x / 2.0f)) <= ((position.x + size.x) + lineOfSightX);
			if (spotted)
			{
				std::cout << "Player was spotted by an enemy!" << std::endl;
				hasBeenSpotted = true;
			}
		}
	}
	return hasBeenSpotted;
}

void Enemy::AddPatrolPoint(glm::vec3 patrolPoint)
{
	patrolPoints.emplace_back(patrolPoint);
}

void Enemy::MoveTowardsNextPatrolPoint(float deltaTime)
{
	GLfloat threshold{ 0.05f };
	glm::vec3 nextPoint{};

	if (nextPatrolPointIndex >= patrolPoints.size())
		nextPatrolPointIndex = 0;

	if (!patrolPoints.empty())
	{
		glm::vec3 nextPoint = patrolPoints.at(nextPatrolPointIndex);

		if (nextPoint.x > (position.x + (size.x / 2.0f)))
		{
			orientation = EnemyOrientation::RIGHT;
			if ((nextPoint.x - position.x) <= threshold)
			{
				std::cout << "Enemy has reached a patrol point" << std::endl;
				previousPatrolPointIndex = nextPatrolPointIndex;
				++nextPatrolPointIndex;
				return;
			}
		}
		else if (nextPoint.x < (position.x + (size.x / 2.0f)))
		{
			orientation = EnemyOrientation::LEFT;
			if (position.x - nextPoint.x <= threshold)
			{
				std::cout << "Enemy has reached a patrol point" << std::endl;
				previousPatrolPointIndex = nextPatrolPointIndex;
				++nextPatrolPointIndex;
				return;
			}
		}
		Move(deltaTime);
	}
}

GLboolean Enemy::MoveTowardsPlayer(const Player& player, float deltaTime)
{
	glm::vec3 playerPos = player.GetPosition();
	glm::vec2 playerSize = player.GetSize();

	if (playerPos.x > position.x)
	{
		orientation = EnemyOrientation::RIGHT;
		// check if the enemy has reached the proper range in order to attack the player in melee
		if ((playerPos.x + playerSize.x / 2.0f) - (position.x + size.x) <= meleeRange)
		{
			std::cout << "Enemy has reached melee range" << std::endl;
			isInRange = true;
			return true;
		}

	}
	else if (playerPos.x < position.x)
	{
		orientation = EnemyOrientation::LEFT;
		// check if the enemy has reached the proper range in order to attack the player in melee
		if (position.x - (playerPos.x + playerSize.x / 2.0f) <= meleeRange)
		{
			std::cout << "Enemy has reached melee range" << std::endl;
			isInRange = true;
			return true;
		}
	}

	isInRange = false;
	Move(deltaTime);
	return false;
}

void Enemy::ResetAnimation(EnemyState animationToReset)
{
	switch (animationToReset)
	{
	case EnemyState::IDLE:
		idleTexIterator = 0;
		break;
	case EnemyState::RUN:
		runTexIterator = 0;
		break;
	case EnemyState::JUMP:
		jumpTexIterator = 0;
		break;
	case EnemyState::DEATH:
		deathTexIterator = 0;
		break;
	case EnemyState::ATTACK:
		meleeAttackIterator = 0;
		break;
	}
}
