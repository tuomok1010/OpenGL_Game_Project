#pragma once

#include "GameObject.h"

class Target : public GameObject
{
public:
	Target();
	~Target();

	void TakeDamage(GLfloat damage);

private:
	GLfloat health{};
};