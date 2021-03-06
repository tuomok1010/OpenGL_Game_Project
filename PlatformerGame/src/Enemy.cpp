#include "Enemy.h"

#include <iostream>

Enemy::Enemy()
	:
	textureOffset(glm::vec2(0.0f)),
	textureScale(glm::vec2(1.0f)),
	color(glm::vec3(1.0f)),
	position(glm::vec3(0.0f)),
	rotation(0.0f),
	velocity(glm::vec2(0.0f)),
	speed(200.0f),
	gravity(5.0f),
	lineOfSightX(LINE_OF_SIGHT_DEFAULT_X)
{
	// Initialise collision boxes
	colBoxOffsetSimple.x = size.x / 2.0f - collisionBoxHorizontalLength / 2.0f;
	collisionBoxSimple = CollisionBox(glm::vec2(position.x + colBoxOffsetSimple.x + 200, position.y), glm::vec2(collisionBoxHorizontalLength, collisionBoxVerticalLength), glm::vec4(1.0f, 1.0f, 0.0f, 0.5f));

	colBoxOffsetBottom.x = size.x / 2.0f - collisionBoxSimple.size.x / 2.0f + collisionBoxThickness;
	collisionBottom = CollisionBox(glm::vec2(position.x + colBoxOffsetBottom.x, position.y), glm::vec2(collisionBoxSimple.size.x - 2 * collisionBoxThickness, collisionBoxThickness), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));

	colBoxOffsetTop.x = size.x / 2.0f - collisionBoxSimple.size.x / 2.0f + collisionBoxThickness;
	colBoxOffsetTop.y = collisionBoxSimple.size.y - collisionBoxThickness + 1.0f;
	collisionTop = CollisionBox(glm::vec2(position.x + colBoxOffsetTop.x, position.y + colBoxOffsetTop.y), glm::vec2(collisionBoxSimple.size.x - 2 * collisionBoxThickness, collisionBoxThickness), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));

	colBoxOffsetLeft.x = size.x / 2.0f - collisionBoxSimple.size.x / 2.0f - 1.0f;
	collisionLeft = CollisionBox(glm::vec2(position.x + colBoxOffsetLeft.x, collisionBoxSimple.position.y + collisionBottom.size.y), glm::vec2(collisionBoxThickness, collisionBoxSimple.size.y - collisionBoxThickness * 2), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));

	colBoxOffsetRight.x = size.x / 2.0f + collisionBoxSimple.size.x / 2.0f - collisionBoxThickness + 1.0f;
	collisionRight = CollisionBox(glm::vec2(position.x + colBoxOffsetRight.x, collisionBoxSimple.position.y + collisionBottom.size.y), glm::vec2(collisionBoxThickness, collisionBoxSimple.size.y - collisionBoxThickness * 2), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));
}

Enemy::Enemy(const Enemy& src)
	: Enemy()
{
	textureOffset = src.textureOffset;
	textureScale = src.textureScale;

	state = src.state;
	orientation = src.orientation;

	idleTexIterator = src.idleTexIterator;
	runTexIterator = src.runTexIterator;
	jumpTexIterator = src.jumpTexIterator;
	deathTexIterator = src.deathTexIterator;
	meleeAttackIterator = src.meleeAttackIterator;

	previousPosition = src.previousPosition;
	position = src.position;
	size = src.size;
	color = src.color;
	rotation = src.rotation;
	velocity = src.velocity;
	speed = src.speed;
	gravity = src.gravity;
	isOnGround = src.isOnGround;

	health = src.health;
	isDead = src.isDead;
	readyToDespawn = src.readyToDespawn;

	hasCollided = src.hasCollided;

	patrolPoints = src.patrolPoints;
	previousPatrolPointIndex = src.previousPatrolPointIndex;
	nextPatrolPointIndex = src.nextPatrolPointIndex;
	initialPosition = src.initialPosition;

	lineOfSightX = src.lineOfSightX;
	isInRange = src.isInRange;
	hasSpottedPlayer = src.hasSpottedPlayer;
	meleeRange = src.meleeRange;

	enemyType = src.enemyType;

	puffEffect = src.puffEffect;

	collisionBottom = src.collisionBottom;
	collisionTop = src.collisionTop;
	collisionLeft = src.collisionLeft;
	collisionRight = src.collisionRight;
	collisionBoxSimple = src.collisionBoxSimple;

	collisionBoxThickness = src.collisionBoxThickness;
	collisionBoxHorizontalLength = src.collisionBoxHorizontalLength;
	collisionBoxVerticalLength = src.collisionBoxVerticalLength;

	colBoxOffsetBottom = src.colBoxOffsetBottom;
	colBoxOffsetTop = src.colBoxOffsetTop;
	colBoxOffsetRight = src.colBoxOffsetRight;
	colBoxOffsetLeft = src.colBoxOffsetLeft;
	colBoxOffsetSimple = src.colBoxOffsetSimple;

	for (const auto& texture : src.texturesIdle)
		texturesIdle.emplace_back(new Texture2D(*texture));

	for (const auto& texture : src.texturesRun)
		texturesRun.emplace_back(new Texture2D(*texture));

	for (const auto& texture : src.texturesJump)
		texturesJump.emplace_back(new Texture2D(*texture));

	for (const auto& texture : src.texturesDeath)
		texturesDeath.emplace_back(new Texture2D(*texture));

	for (const auto& texture : src.texturesMeleeAttack)
		texturesMeleeAttack.emplace_back(new Texture2D(*texture));

	textureFall = new Texture2D(*src.textureFall);
}

Enemy::~Enemy()
{
	for (unsigned int i = 0; i < texturesIdle.size(); ++i)
	{
		if (texturesIdle.at(i) != nullptr)
		{
			texturesIdle.at(i)->Unbind();
			delete texturesIdle.at(i);
		}
	}

	for (unsigned int i = 0; i < texturesRun.size(); ++i)
	{
		if (texturesRun.at(i) != nullptr)
		{
			texturesRun.at(i)->Unbind();
			delete texturesRun.at(i);
		}
	}

	for (unsigned int i = 0; i < texturesJump.size(); ++i)
	{
		if (texturesJump.at(i) != nullptr)
		{
			texturesJump.at(i)->Unbind();
			delete texturesJump.at(i);
		}
	}

	for (unsigned int i = 0; i < texturesDeath.size(); ++i)
	{
		if (texturesDeath.at(i) != nullptr)
		{
			texturesDeath.at(i)->Unbind();
			delete texturesDeath.at(i);
		}
	}

	if (textureFall != nullptr)
	{
		textureFall->Unbind();
		delete textureFall;
	}
}

Enemy& Enemy::operator=(const Enemy& src)
{
	if (this == &src)
		return *this;

	textureOffset = src.textureOffset;
	textureScale = src.textureScale;

	state = src.state;
	orientation = src.orientation;

	idleTexIterator = src.idleTexIterator;
	runTexIterator = src.runTexIterator;
	jumpTexIterator = src.jumpTexIterator;
	deathTexIterator = src.deathTexIterator;
	meleeAttackIterator = src.meleeAttackIterator;

	previousPosition = src.previousPosition;
	position = src.position;
	size = src.size;
	color = src.color;
	rotation = src.rotation;
	velocity = src.velocity;
	speed = src.speed;
	gravity = src.gravity;
	isOnGround = src.isOnGround;

	health = src.health;
	isDead = src.isDead;
	readyToDespawn = src.readyToDespawn;

	hasCollided = src.hasCollided;

	patrolPoints = src.patrolPoints;
	previousPatrolPointIndex = src.previousPatrolPointIndex;
	nextPatrolPointIndex = src.nextPatrolPointIndex;
	initialPosition = src.initialPosition;

	lineOfSightX = src.lineOfSightX;
	isInRange = src.isInRange;
	hasSpottedPlayer = src.hasSpottedPlayer;
	meleeRange = src.meleeRange;

	enemyType = src.enemyType;

	puffEffect = src.puffEffect;

	collisionBottom = src.collisionBottom;
	collisionTop = src.collisionTop;
	collisionLeft = src.collisionLeft;
	collisionRight = src.collisionRight;
	collisionBoxSimple = src.collisionBoxSimple;

	collisionBoxThickness = src.collisionBoxThickness;
	collisionBoxHorizontalLength = src.collisionBoxHorizontalLength;
	collisionBoxVerticalLength = src.collisionBoxVerticalLength;

	colBoxOffsetBottom = src.colBoxOffsetBottom;
	colBoxOffsetTop = src.colBoxOffsetTop;
	colBoxOffsetRight = src.colBoxOffsetRight;
	colBoxOffsetLeft = src.colBoxOffsetLeft;
	colBoxOffsetSimple = src.colBoxOffsetSimple;

	for (const auto& texture : src.texturesIdle)
		texturesIdle.emplace_back(new Texture2D(*texture));

	for (const auto& texture : src.texturesRun)
		texturesRun.emplace_back(new Texture2D(*texture));

	for (const auto& texture : src.texturesJump)
		texturesJump.emplace_back(new Texture2D(*texture));

	for (const auto& texture : src.texturesDeath)
		texturesDeath.emplace_back(new Texture2D(*texture));

	for (const auto& texture : src.texturesMeleeAttack)
		texturesMeleeAttack.emplace_back(new Texture2D(*texture));

	textureFall = new Texture2D(*src.textureFall);

	return *this;
}

void Enemy::Draw(SpriteRenderer& renderer, PrimitiveRenderer& collisionBoxRenderer, GLboolean drawCollisionBoxes)
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

	if (drawCollisionBoxes)
	{
		collisionBottom.Draw(collisionBoxRenderer);
		collisionTop.Draw(collisionBoxRenderer);
		collisionLeft.Draw(collisionBoxRenderer);
		collisionRight.Draw(collisionBoxRenderer);
		collisionBoxSimple.Draw(collisionBoxRenderer);
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
		ResetAnimation(EnemyState::ATTACK);
	}

	position.x += velocity.x * speed * deltaTime;
	position.y += velocity.y * speed * deltaTime;
	velocity.y -= gravity * deltaTime;

	// Update collision box positions
	collisionBoxSimple.position = glm::vec2(position.x + colBoxOffsetSimple.x, position.y);
	collisionBottom.position = glm::vec2(position.x + colBoxOffsetBottom.x, position.y - 1.0f);
	collisionTop.position = glm::vec2(position.x + colBoxOffsetTop.x, position.y + colBoxOffsetTop.y);
	collisionRight.position = glm::vec2(position.x + colBoxOffsetRight.x, collisionBoxSimple.position.y + collisionBottom.size.y);
	collisionLeft.position = glm::vec2(position.x + colBoxOffsetLeft.x, collisionBoxSimple.position.y + collisionBottom.size.y);
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
				if (lineOfSightX <= LINE_OF_SIGHT_DEFAULT_X)
					lineOfSightX *= 2;
			}
			else if (spottedNotFacingPlayer)
			{
				hasSpottedPlayer = true;
				if (lineOfSightX <= LINE_OF_SIGHT_DEFAULT_X)
					lineOfSightX *= 2;
			}
			else
			{
				hasSpottedPlayer = false;
				lineOfSightX = LINE_OF_SIGHT_DEFAULT_X;
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
				if (lineOfSightX <= LINE_OF_SIGHT_DEFAULT_X)
					lineOfSightX *= 2;
			}
			else if (spottedNotFacingPlayer)
			{
				hasSpottedPlayer = true;
				if (lineOfSightX <= LINE_OF_SIGHT_DEFAULT_X)
					lineOfSightX *= 2;
			}
			else
			{
				hasSpottedPlayer = false;
				lineOfSightX = LINE_OF_SIGHT_DEFAULT_X;
				SetVelocityX(0.0f);
			}
		}
	}
	else
	{
		hasSpottedPlayer = false;
		SetVelocityX(0.0f);
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

	if (health <= 0)
		isDead = true;
}

GLboolean Enemy::MoveTowardsPlayer(const Player& player, float deltaTime)
{
	glm::vec3 playerPos = player.GetPosition();
	glm::vec2 playerSize = player.GetSize();
	GLboolean isInYRange{ false };
	GLboolean isInXRangeRight{ false };
	GLboolean isInXRangeLeft{ false };

	isInYRange = (playerPos.y >= (position.y - playerSize.y / 2.0f + 20.0f)) && (playerPos.y <= (position.y + size.y / 2.0f - 20.0f));

	if (playerPos.x + playerSize.x / 2.0f > position.x + size.x / 2.0f)
	{
		isInXRangeRight = (playerPos.x + playerSize.x / 2.0f) - (position.x + size.x) <= meleeRange;
		orientation = EnemyOrientation::RIGHT;
		// check if the enemy has reached the proper range in order to attack the player in melee
		if (isInXRangeRight)
		{
			SetVelocityX(0.0f);

			if (isInYRange)
			{
				isInRange = true;
				return true;
			}
		}
	}
	else if (playerPos.x + playerSize.x / 2.0f < position.x + size.x / 2.0f)
	{
		isInXRangeLeft = position.x - (playerPos.x + playerSize.x / 2.0f) <= meleeRange;
		orientation = EnemyOrientation::LEFT;
		// check if the enemy has reached the proper range in order to attack the player in melee
		if (isInXRangeLeft)
		{
			SetVelocityX(0.0f);

			if (isInYRange)
			{
				isInRange = true;
				return true;
			}
		}
	}
	isInRange = false;

	if (state == EnemyState::ATTACK)
		state = EnemyState::IDLE;

	if (orientation == EnemyOrientation::LEFT && !isInXRangeLeft && hasSpottedPlayer)
		SetVelocityX(-1.0f);
	else if (orientation == EnemyOrientation::RIGHT && !isInXRangeRight && hasSpottedPlayer)
		SetVelocityX(1.0f);
	else
		SetVelocityX(0.0f);

	return false;
}

GLint Enemy::AdvancedCollisionCheck(GameObject& obj)
{
	glm::vec2 objPos = obj.GetPosition();
	glm::vec2 objSize = obj.GetSize();

	GLboolean collisionX = collisionBottom.position.x + collisionBottom.size.x > objPos.x&& objPos.x + objSize.x > collisionBottom.position.x;
	GLboolean collisionY = collisionBottom.position.y + collisionBottom.size.y > objPos.y&& objPos.y + objSize.y > collisionBottom.position.y;
	if (collisionX && collisionY)
	{
		return 1;
	}

	collisionX = collisionRight.position.x + collisionRight.size.x > objPos.x&& objPos.x + objSize.x > collisionRight.position.x;
	collisionY = collisionRight.position.y + collisionRight.size.y > objPos.y&& objPos.y + objSize.y > collisionRight.position.y;
	if (collisionX && collisionY)
	{
		return 2;
	}

	collisionX = collisionLeft.position.x + collisionLeft.size.x > objPos.x&& objPos.x + objSize.x > collisionLeft.position.x;
	collisionY = collisionLeft.position.y + collisionLeft.size.y > objPos.y&& objPos.y + objSize.y > collisionLeft.position.y;
	if (collisionX && collisionY)
	{
		return 3;
	}

	collisionX = collisionTop.position.x + collisionTop.size.x > objPos.x&& objPos.x + objSize.x > collisionTop.position.x;
	collisionY = collisionTop.position.y + collisionTop.size.y > objPos.y&& objPos.y + objSize.y > collisionTop.position.y;
	if (collisionX && collisionY)
	{
		return 4;
	}
	return 0;
}

GLboolean Enemy::SimpleCollisionCheck(GameObject& obj)
{
	glm::vec2 objPos = obj.GetPosition();
	glm::vec2 objSize = obj.GetSize();

	GLboolean collisionX = collisionBoxSimple.position.x + collisionBoxSimple.size.x > objPos.x&& objPos.x + objSize.x > collisionBoxSimple.position.x;
	GLboolean collisionY = collisionBoxSimple.position.y + collisionBoxSimple.size.y > objPos.y&& objPos.y + objSize.y > collisionBoxSimple.position.y;
	return collisionX && collisionY;

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
