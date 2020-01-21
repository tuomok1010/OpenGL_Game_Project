#include "Spearman.h"

#include <iostream>

Spearman::Spearman()
{
	state = EnemyState::IDLE;
	orientation = EnemyOrientation::LEFT;
	textureOffset = glm::vec2(-0.35f, 0.07f);
	textureScale = glm::vec2(1.45f, 1.1f);
	color = glm::vec3(1.0f);
	position = glm::vec3(0.0f);
	size = glm::vec2(250.0f, 100.0f);
	rotation = 0.0f;
	speed = 100.0f;
	maxJumpHeight = 75.0f;
	heightJumped = 0.0f;
	health = 50.0f;
	lineOfSightX = 250.0f;
	enemyType = EnemyType::SPEARMAN;
	meleeDamage = 20;
	meleeRange = -15.0f;

	for(unsigned int i = 0; i < 26; ++i)
		texturesIdle.emplace_back(new Texture2D("../enemies/Ancient Turkish Warrior/Animations/Idle/Idle_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE));

	for (unsigned int i = 0; i < 13; ++i)
		texturesRun.emplace_back(new Texture2D("../enemies/Ancient Turkish Warrior/Animations/Run/Run_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE));

	for(unsigned int i = 0; i < 18; ++i)
		texturesDeath.emplace_back(new Texture2D("../enemies/Ancient Turkish Warrior/Animations/Die/Die_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, GL_CLAMP_TO_EDGE));

	for(unsigned int i = 0; i < 11; ++i)
		texturesMeleeAttack.emplace_back(new Texture2D("../enemies/Ancient Turkish Warrior/Animations/Attack/Attack_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE));
}

Spearman::~Spearman()
{
}

void Spearman::Draw(SpriteRenderer& renderer)
{
	// If the enemy is facing right, we do not need to rotate the sprite, if the sprite is facing left we set the axis of rotation to be the Y axis.
	glm::vec3 rotationAxiis = (orientation == EnemyOrientation::RIGHT) ? glm::vec3(0.0f, 0.0f, 1.0f) : glm::vec3(0.0f, 1.0f, 0.0f);

	// If the enemy is facing right, set rotation to 0.0f, if the sprite is facing left set rotation to 180.0f.
	rotation = (orientation == EnemyOrientation::RIGHT) ? 0.0f : 180.0f;

	if (state == EnemyState::IDLE)
	{
		if (idleTexIterator >= texturesIdle.size())
			idleTexIterator = 0;

		textureScale = glm::vec2(2.4f, 1.1f);
		renderer.Draw(*texturesIdle.at(idleTexIterator), 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
		++idleTexIterator;
	}
	else if (state == EnemyState::RUN)
	{
		if (runTexIterator >= texturesRun.size())
			runTexIterator = 0;

		textureScale = glm::vec2(2.25f, 1.1f);
		renderer.Draw(*texturesRun.at(runTexIterator), 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
		++runTexIterator;
	}
	else if (state == EnemyState::JUMP)
	{
		if (jumpTexIterator >= texturesJump.size())
			jumpTexIterator = texturesJump.size() - 1;

		textureScale = glm::vec2(1.45f, 1.1f);
		renderer.Draw(*texturesJump.at(jumpTexIterator), 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
		++jumpTexIterator;
	}
	else if (state == EnemyState::FALL)
	{
		textureScale = glm::vec2(1.45f, 1.1f);
		renderer.Draw(*textureFall, 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
	}
	else if (state == EnemyState::DEATH)
	{
		if (deathTexIterator >= texturesDeath.size())
		{
			readyToDespawn = true;
			deathTexIterator = texturesDeath.size() - 1;
		}


		textureScale = glm::vec2(1.2f, 1.0f);
		textureOffset.x = 0.0f;

		renderer.Draw(*texturesDeath.at(deathTexIterator), 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);

		++deathTexIterator;
	}
	else if (state == EnemyState::ATTACK)
	{
		if (meleeAttackIterator >= texturesMeleeAttack.size())
			meleeAttackIterator = 0;

		textureScale = glm::vec2(1.75f, 1.1f);
		renderer.Draw(*texturesMeleeAttack.at(meleeAttackIterator), 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
		++meleeAttackIterator;
	} 
}

GLboolean Spearman::MeleeAttack()
{
	state = EnemyState::ATTACK;

	if (meleeAttackIterator == texturesMeleeAttack.size() - 1)
		return false;
	else
		return true;
}

GLboolean Spearman::DamagePlayer(Player& player)
{
	if (meleeAttackIterator > texturesMeleeAttack.size() - 1)
	{
		if (!player.GetIsDead())
		{
			player.SetHealth(player.GetHealth() - meleeDamage);
			std::cout << "Spearman damages player by " << meleeDamage << " points! Player health: " << player.GetHealth() << std::endl;
			return true;
		}
	}
	return false;
}

GLboolean Spearman::IsInPlayerMeleeRange(Player& player)
{
	glm::vec3 playerPos = player.GetPosition();
	glm::vec2 playerSize = player.GetSize();
	PlayerOrientation playerOrientation = player.GetOrientation();
	GLboolean isInRange = false;
	GLfloat xOffset = 15.0f;

	if (playerPos.y >= position.y - 50.0f && playerPos.y < position.y + 50.0f)	// TODO adjust later. This checks if enemy and player are about in the same level on y axis
	{
		switch (playerOrientation)
		{
			case PlayerOrientation::RIGHT:
			{
				if (playerPos.x + playerSize.x / 2.0f < position.x + size.x / 2.0f)
				{
					if (playerPos.x > position.x + size.x / 2.0f - playerSize.x - xOffset)
					{
						player.SetIsInMeleeRange(true);
						isInRange = true;
					}
				}
				break;
			}
			case PlayerOrientation::LEFT:
			{
				if (playerPos.x + playerSize.x / 2.0f > position.x + size.x / 2.0f)
				{
					if (playerPos.x < (position.x + size.x / 2.0f + xOffset))
					{
						player.SetIsInMeleeRange(true);
						isInRange = true;

					}
				}
				break;
			}
		}
	}
	else
	{
		player.SetIsInMeleeRange(false);
		isInRange = false;
	}
	return isInRange;
}

void Spearman::DrawBloodEffect(SpriteRenderer& renderer)
{
	if (shouldBleed)
	{
		bloodEffect.SetPosition(glm::vec3(position.x + size.x / 2.0f - bloodEffect.GetSize().x / 2.0f, position.y + size.y / 2.0f - bloodEffect.GetSize().y / 2.0f, position.z));
		bloodEffect.Draw(renderer);
	}

	if (bloodEffect.GetShouldStop())
		shouldBleed = false;
	else
		shouldBleed = true;
}

void Spearman::ResetBloodAnimation()
{
	bloodEffect.ResetAnimation();
}