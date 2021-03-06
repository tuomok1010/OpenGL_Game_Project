#pragma once

#include "Enemy.h"
#include "BloodEffect.h"

class Spearman : public Enemy
{
public:
	Spearman();
	Spearman(const Spearman& src);
	~Spearman();

	Spearman& operator=(const Spearman& src);

	void Draw(SpriteRenderer& renderer, PrimitiveRenderer& collisionBoxRenderer, GLboolean drawCollisionBoxes = false) override;

	GLboolean MeleeAttack();
	GLboolean DamagePlayer(Player& player);
	void DrawBloodEffect(SpriteRenderer& renderer);
	void ResetBloodAnimation();
	void SetShouldBleed(GLboolean newVal) { shouldBleed = newVal; }

	GLboolean IsInPlayerMeleeRange(Player& player);

private:
	GLint meleeDamage;
	BloodEffect bloodEffect;
	GLboolean shouldBleed{ false };
};