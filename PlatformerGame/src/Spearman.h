#pragma once

#include "Enemy.h"

class Spearman : public Enemy
{
public:
	Spearman();
	~Spearman();

	GLboolean MeleeAttack();

	void DamagePlayer(Player& player);

private:
	GLfloat meleeDamage{};
};