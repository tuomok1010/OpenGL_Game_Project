#include "Enemy.h"

#include <iostream>

Enemy::Enemy()
	:
	color(glm::vec3(1.0f)),
	position(glm::vec3(0.0f)),
	rotation(0.0f),
	velocity(glm::vec2(0.0f)),
	speed(200.0f),
	gravity(5.0f)
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
		{
			readyToDespawn = true;
			deathTexIterator = texturesDeath.size() - 1;
		}

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

void Enemy::DrawPuffEffect(SpriteRenderer& renderer)
{
	GLfloat puffEffectYOffset = -50.0f;
	GLfloat puffEffectXOffset = orientation == EnemyOrientation::RIGHT ? -40.0f : 40.0f;

	puffEffect.SetPosition(glm::vec3(position.x + size.x / 2.0f - puffEffect.GetSize().x / 2.0f + puffEffectXOffset, position.y + puffEffectYOffset, position.z));

	if (!puffEffect.GetShouldStop())
		puffEffect.Draw(renderer);
}

void Enemy::Update(GLfloat deltaTime)
{
	// Update movement
	previousPosition = position;

	if (abs(velocity.x) >= 1.0f && isOnGround)
	{
		state = EnemyState::RUN;
	}
	else if (!isOnGround)
	{
		state = EnemyState::JUMP;
	}
	else if (state != EnemyState::ATTACK)
	{
		state = EnemyState::IDLE;
	}

	position.x += velocity.x * speed * deltaTime;
	position.y += velocity.y * speed * deltaTime;
	velocity.y -= gravity * deltaTime;
}

// TODO perhaps add a sneak functionality to the player that allows player to sneak up behind enemy without him hearing the player
GLboolean Enemy::CheckIfHasSeenPlayer(const Player& player)
{
	if (isDead)
		return false;

	glm::vec2 playerSize = player.GetSize();
	glm::vec3 playerPos = player.GetPosition();
	playerPos.x = playerPos.x + (playerSize.x / 2.0f);

	glm::vec3 enemyPos = position;
	enemyPos.x = position.x + (size.x / 2.0f);

	// check if the player is (about )in the same height on the y axiis as the enemy. TODO adjust the y axis detection range
	if (playerPos.y + playerSize.y > position.y && position.y + size.y > playerPos.y)
	{
		if (orientation == EnemyOrientation::LEFT)
		{
			// when the enemy is facing the player, how close the player needs to be before the enemy "sees" him
			bool spottedFacingPlayer = (playerPos.x >= enemyPos.x - lineOfSightX) && (playerPos.x <= enemyPos.x);
			// when the enemy is NOT facing the player, how close the player needs to be before the enemy "hears" him
			bool spottedNotFacingPlayer = (playerPos.x <= enemyPos.x + lineOfSightX / 2.0f) && (playerPos.x >= enemyPos.x);

			if (spottedFacingPlayer)
			{
				hasSpottedPlayer = true;
			}
			else if (spottedNotFacingPlayer)
			{
				hasSpottedPlayer = true;
			}
			else
			{
				hasSpottedPlayer = false;
				SetVelocityX(0.0f);
			}
		}
		else if (orientation == EnemyOrientation::RIGHT)
		{
			// when the enemy is facing the player, how close the player needs to be before the enemy "sees" him
			bool spottedFacingPlayer = (playerPos.x <= enemyPos.x + lineOfSightX) && (playerPos.x >= enemyPos.x);
			// when the enemy is NOT facing the player, how close the player needs to be before the enemy "hears" him
			bool spottedNotFacingPlayer = (playerPos.x >= enemyPos.x - lineOfSightX / 2.0f) && (playerPos.x <= enemyPos.x);

			if (spottedFacingPlayer)
			{
				hasSpottedPlayer = true;
			}
			else if (spottedNotFacingPlayer)
			{
				hasSpottedPlayer = true;
			}
			else
			{
				hasSpottedPlayer = false;
				SetVelocityX(0.0f);
			}
		}
	}
	return hasSpottedPlayer;
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
				SetVelocityX(0.0f);
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
				SetVelocityX(0.0f);
				return;
			}
		}
		if (orientation == EnemyOrientation::LEFT)
			SetVelocityX(-1.0f);
		else if (orientation == EnemyOrientation::RIGHT)
			SetVelocityX(1.0f);
	}
}

void Enemy::TakeDamage(GLfloat damage)
{
	health -= damage;

	if (health <= 0.0f)
		isDead = true;
}

GLboolean Enemy::MoveTowardsPlayer(const Player& player, float deltaTime)
{
	glm::vec3 playerPos = player.GetPosition();
	glm::vec2 playerSize = player.GetSize();
	
	std::cout << "move towards player called" << std::endl;

	if (playerPos.x > position.x)
	{
		orientation = EnemyOrientation::RIGHT;
		// check if the enemy has reached the proper range in order to attack the player in melee
		if ((playerPos.x + playerSize.x / 2.0f) - (position.x + size.x) <= meleeRange)
		{
			std::cout << "enemy has reached melee range" << std::endl;
			isInRange = true;
			SetVelocityX(0.0f);
			return true;
		}

	}
	else if (playerPos.x < position.x)
	{
		orientation = EnemyOrientation::LEFT;
		// check if the enemy has reached the proper range in order to attack the player in melee
		if (position.x - (playerPos.x + playerSize.x / 2.0f) <= meleeRange)
		{
			std::cout << "enemy has reached melee range" << std::endl;
			isInRange = true;
			SetVelocityX(0.0f);
			return true;
		}
	}

	std::cout << "enemy is not in range" << std::endl;
	isInRange = false;

	if (state == EnemyState::ATTACK)
		state = EnemyState::IDLE;

	if (orientation == EnemyOrientation::LEFT)
		SetVelocityX(-1.0f);
	else if (orientation == EnemyOrientation::RIGHT)
		SetVelocityX(1.0f);

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
