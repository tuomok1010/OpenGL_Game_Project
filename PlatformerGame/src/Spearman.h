#pragma once

#include "Enemy.h"
#include "BloodEffect.h"

class Spearman : public Enemy
{
public:
	Spearman();
	~Spearman();

	void Draw(SpriteRenderer& renderer) override;
	void DrawBlood(SpriteRenderer& renderer, Player& player);

	void SetDamageDirection(DamageDirection newDirection);
	void SetEnableBloodEffect(GLboolean enableBlood) { enableBloodEffect = enableBlood; }

	GLboolean MeleeAttack();

	GLboolean DamagePlayer(Player& player);

private:
	GLfloat meleeDamage{};
	BloodEffect bloodEffect;
	GLboolean enableBloodEffect{ false };
};