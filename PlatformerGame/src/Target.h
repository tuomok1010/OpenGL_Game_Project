#pragma once

#include "Enemy.h"

class Target : public Enemy
{
public:
	Target();
	Target(const Target& src);
	~Target();

	Target& operator=(const Target& src);

	void Draw(SpriteRenderer& renderer, PrimitiveRenderer& collisionBoxRenderer, GLboolean drawCollisionBoxes = false) override;
	void DrawPuffEffect(SpriteRenderer& renderer) override;

	void Update(GLfloat deltaTime) override;

	void TakeDamage(GLfloat damage);

	GLboolean IsInPlayerMeleeRange(Player& player);

private:
	GLfloat health{};
};