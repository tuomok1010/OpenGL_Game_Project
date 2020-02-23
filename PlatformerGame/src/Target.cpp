#include "Target.h"
#include <iostream>

Target::Target()
{
	health = 1;
	size = glm::vec2(50.0f);
	enemyType = EnemyType::TARGET;
	texturesIdle.emplace_back(new Texture2D("../textures/target.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	gravity = 0.0f;

	collisionBoxSimple.size = size;
	collisionBoxSimple.position = position;
}

Target::Target(const Target& src)
	: Enemy(src)
{
	health = src.health;
}

Target::~Target()
{
}

Target& Target::operator=(const Target& src)
{
	if (this == &src)
		return *this;

	Enemy::operator=(src);
	health = src.health;

	return *this;
}

void Target::Draw(SpriteRenderer& renderer, PrimitiveRenderer& collisionBoxRenderer, GLboolean drawCollisionBoxes)
{
	// If the enemy is facing right, we do not need to rotate the sprite, if the sprite is facing left we set the axis of rotation to be the Y axis.
	glm::vec3 rotationAxiis = (orientation == EnemyOrientation::RIGHT) ? glm::vec3(0.0f, 0.0f, 1.0f) : glm::vec3(0.0f, 1.0f, 0.0f);

	// If the enemy is facing right, set rotation to 0.0f, if the sprite is facing left set rotation to 180.0f.
	rotation = (orientation == EnemyOrientation::RIGHT) ? 0.0f : 180.0f;

	renderer.Draw(*texturesIdle.at(0), 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);

	if (drawCollisionBoxes)
		collisionBoxSimple.Draw(collisionBoxRenderer);
}

void Target::DrawPuffEffect(SpriteRenderer& renderer)
{
	GLfloat puffEffectYOffset = -50.0f;
	GLfloat puffEffectXOffset = orientation == EnemyOrientation::RIGHT ? -0.0f : 0.0f;

	puffEffect.SetPosition(glm::vec3(position.x + size.x / 2.0f - puffEffect.GetSize().x / 2.0f + puffEffectXOffset, position.y + puffEffectYOffset, position.z));

	if (!puffEffect.GetShouldStop())
		puffEffect.Draw(renderer);
}

void Target::Update(GLfloat deltaTime)
{
	// Update movement
	previousPosition = position;

	position.x += velocity.x * speed * deltaTime;
	position.y += velocity.y * speed * deltaTime;
	velocity.y -= gravity * deltaTime;

	// Update collision box positions
	collisionBoxSimple.position = position;
}

void Target::TakeDamage(GLfloat damage)
{
	health -= damage;
	if (health <= 0)
	{
		isDead = true;
		readyToDespawn = true;
	}
}

GLboolean Target::IsInPlayerMeleeRange(Player& player)
{
	glm::vec3 playerPos = player.GetPosition();
	glm::vec2 playerSize = player.GetSize();
	PlayerOrientation playerOrientation = player.GetOrientation();
	GLboolean isInRange = false;
	GLfloat xOffset = 15.0f;

	if (playerPos.y >= position.y - 50.0f && playerPos.y < position.y + 50.0f)	// TODO adjust later. This checks if enemy and player are about in the same level on y axis
	{
		switch (playerOrientation)
		{
		case PlayerOrientation::RIGHT:
		{
			if (playerPos.x + playerSize.x / 2.0f < position.x + size.x / 2.0f)
			{
				if (playerPos.x > position.x + size.x / 2.0f - playerSize.x - xOffset)
				{
					player.SetIsInMeleeRange(true);
					isInRange = true;
				}
			}
			break;
		}
		case PlayerOrientation::LEFT:
		{
			if (playerPos.x + playerSize.x / 2.0f > position.x + size.x / 2.0f)
			{
				if (playerPos.x < (position.x + size.x / 2.0f + xOffset))
				{
					player.SetIsInMeleeRange(true);
					isInRange = true;
				}
			}
			break;
		}
		}
	}
	else
	{
		player.SetIsInMeleeRange(false);
		isInRange = false;
	}
	return isInRange;
}
