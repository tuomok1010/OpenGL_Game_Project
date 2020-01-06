#include "SpikeTrap.h"

SpikeTrap::SpikeTrap(glm::vec2 position, glm::vec2 size, Texture2D& texture, glm::vec3 color, GLfloat speed, glm::vec2 textureOffset, glm::vec2 textureZoom)
	: 
	GameObject(position, size, texture, color, speed, textureOffset, textureZoom),
	damage(100.0f)
{
	type = Type::SPIKETRAP;
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
