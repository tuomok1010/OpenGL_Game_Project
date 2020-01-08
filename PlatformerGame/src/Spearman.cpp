#include "Spearman.h"

#include <iostream>

Spearman::Spearman()
{
	state = EnemyState::IDLE;
	orientation = EnemyOrientation::LEFT;
	textureOffset = glm::vec2(-0.2f, 0.07f);
	textureScale = glm::vec2(1.45f, 1.1f);
	color = glm::vec3(1.0f);
	position = glm::vec3(0.0f);
	size = glm::vec2(160.0f, 100.0f);
	rotation = 0.0f;
	speed = 100.0f;
	maxJumpHeight = 75.0f;
	heightJumped = 0.0f;
	health = 100.0f;
	lineOfSightX = 150.0f;
	enemyType = EnemyType::SPEARMAN;
	meleeDamage = 25.0f;

	for(unsigned int i = 0; i < 26; ++i)
		texturesIdle.emplace_back(new Texture2D("../enemies/Ancient Turkish Warrior/Animations/Idle/Idle_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE));

	for (unsigned int i = 0; i < 13; ++i)
		texturesRun.emplace_back(new Texture2D("../enemies/Ancient Turkish Warrior/Animations/Run/Run_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE));

	for(unsigned int i = 0; i < 18; ++i)
		texturesDeath.emplace_back(new Texture2D("../enemies/Ancient Turkish Warrior/Animations/Die/Die_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));

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

		textureScale = glm::vec2(1.45f, 1.1f);
		renderer.Draw(*texturesIdle.at(idleTexIterator), 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
		++idleTexIterator;
	}
	else if (state == EnemyState::RUN)
	{
		if (runTexIterator >= texturesRun.size())
			runTexIterator = 0;

		textureScale = glm::vec2(1.45f, 1.1f);
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
			deathTexIterator = texturesDeath.size() - 1;

		textureScale = glm::vec2(1.45f, 1.1f);
		renderer.Draw(*texturesDeath.at(deathTexIterator), 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
		++deathTexIterator;
	}
	else if (state == EnemyState::ATTACK)
	{
		if (meleeAttackIterator >= texturesMeleeAttack.size())
			meleeAttackIterator = 0;

		textureScale = glm::vec2(1.20f, 1.1f);
		renderer.Draw(*texturesMeleeAttack.at(meleeAttackIterator), 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
		++meleeAttackIterator;
	} 
}

void Spearman::DrawBlood(SpriteRenderer& renderer, Player& player)
{
	if (enableBloodEffect)
	{
		GLfloat xOffset = 5.0f;
		GLfloat yOffset = 25.0f;
		switch (bloodEffect.damageDirection)
		{
			case DamageDirection::RIGHT:
			{
				bloodEffect.SetPosition(glm::vec3(position.x + xOffset, position.y + (size.y / 2.0f) - yOffset, position.z));
				bloodEffect.Rotate(-90.0f);
				break;
			}
			case DamageDirection::LEFT:
			{
				bloodEffect.SetPosition(glm::vec3(position.x + size.x - bloodEffect.GetSize().x, position.y + (size.y / 2.0f) - yOffset, position.z));
				bloodEffect.Rotate(90.0f);
				break;
			}
		}

		bloodEffect.Draw(renderer);
		bloodEffect.Rotate(0.0f);

		if (bloodEffect.GetShouldStop())
			enableBloodEffect = false;
		else
			enableBloodEffect = true;
	}
}

void Spearman::SetDamageDirection(DamageDirection newDirection)
{
	bloodEffect.SetDamageDirection(newDirection);
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
