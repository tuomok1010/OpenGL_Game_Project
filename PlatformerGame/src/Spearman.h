#pragma once

#include "Enemy.h"

class Spearman : public Enemy
{
public:
	Spearman();
	~Spearman();

	void Draw(SpriteRenderer& renderer) override;

	GLboolean MeleeAttack();

	GLboolean DamagePlayer(Player& player);

private:
	GLfloat meleeDamage{};
};