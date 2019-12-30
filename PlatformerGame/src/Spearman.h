#pragma once

#include "Enemy.h"

class Spearman : public Enemy
{
public:
	Spearman();
	~Spearman();

	GLboolean MeleeAttack();

private:
};