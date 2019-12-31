#include "Spearman.h"

Spearman::Spearman()
{
	state = EnemyState::IDLE;
	orientation = EnemyOrientation::LEFT;
	textureOffset = glm::vec2(-0.2f, 0.07f);
	textureScale = glm::vec2(1.25f, 0.9f);
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

	for(unsigned int i = 0; i < 26; ++i)
		texturesIdle.emplace_back(new Texture2D("../enemies/Ancient Turkish Warrior/Animations/Idle/Idle_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, GL_CLAMP_TO_EDGE));

	for (unsigned int i = 0; i < 13; ++i)
		texturesRun.emplace_back(new Texture2D("../enemies/Ancient Turkish Warrior/Animations/Run/Run_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));

	for(unsigned int i = 0; i < 18; ++i)
		texturesDeath.emplace_back(new Texture2D("../enemies/Ancient Turkish Warrior/Animations/Die/Die_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));

	for(unsigned int i = 0; i < 11; ++i)
		texturesMeleeAttack.emplace_back(new Texture2D("../enemies/Ancient Turkish Warrior/Animations/Attack/Attack_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
}

Spearman::~Spearman()
{
}

GLboolean Spearman::MeleeAttack()
{
	state = EnemyState::ATTACK;

	if (meleeAttackIterator == texturesMeleeAttack.size() - 1)
		return false;
	else
		return true;
}
