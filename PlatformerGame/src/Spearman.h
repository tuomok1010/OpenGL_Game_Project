#pragma once

#include "Enemy.h"
#include "BloodEffect.h"

class Spearman : public Enemy
{
public:
	Spearman();
	~Spearman();

	void Draw(SpriteRenderer& renderer) override;
	void DrawBlood(SpriteRenderer& renderer);

	GLboolean MeleeAttack();
	GLboolean DamagePlayer(Player& player);

	GLboolean IsInPlayerMeleeRange(Player& player);

private:
	GLfloat meleeDamage{};
};