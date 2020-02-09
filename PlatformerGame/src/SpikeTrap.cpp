#include "SpikeTrap.h"

SpikeTrap::SpikeTrap(glm::vec2 position, glm::vec2 size, Texture2D& texture, glm::vec3 color, GLfloat speed, glm::vec2 textureOffset, glm::vec2 textureZoom)
	: 
	GameObject(Type::SPIKETRAP, position, size, texture, color, speed, textureOffset, textureZoom),
	damage(100.0f)
{
	type = Type::SPIKETRAP;
}

SpikeTrap::SpikeTrap(const SpikeTrap& src)
	: SpikeTrap(src.position, src.size, src.texture, src.color, src.speed, src.textureOffset, src.textureScale)
{
}

SpikeTrap::~SpikeTrap()
{
}

void SpikeTrap::DamagePlayer(Player& player)
{
	if (!player.GetIsDead())
	{
		// making sure the spikes always kills the player
		damage = player.GetHealth() + 1.0f;
		player.SetHealth(player.GetHealth() - damage);
	}
}

void SpikeTrap::DamageEnemy(Enemy& enemy)
{
	if (!enemy.GetIsDead())
	{
		// making sure the spikes always kills the enemy
		damage = enemy.GetHealth() + 1.0f;
		enemy.SetHealth(enemy.GetHealth() - damage);
	}
}
