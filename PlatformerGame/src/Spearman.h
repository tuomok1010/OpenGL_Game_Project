#pragma once

#include "Enemy.h"
#include "BloodEffect.h"

class Spearman : public Enemy
{
public:
	Spearman();
	~Spearman();

	void Draw(SpriteRenderer& renderer) override;

	GLboolean MeleeAttack();
	GLboolean DamagePlayer(Player& player);
	void DrawBloodEffect(SpriteRenderer& renderer);
	void ResetBloodAnimation();
	void SetShouldBleed(GLboolean newVal) { shouldBleed = newVal; }

	GLboolean IsInPlayerMeleeRange(Player& player);

private:
	GLint meleeDamage{};
	BloodEffect bloodEffect;
	GLboolean shouldBleed{ false };
};