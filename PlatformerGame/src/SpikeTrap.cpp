#include "SpikeTrap.h"

SpikeTrap::SpikeTrap(glm::vec2 position, glm::vec2 size, Texture2D& texture, glm::vec3 color, glm::vec2 velocity, glm::vec2 textureOffset, glm::vec2 textureZoom)
	: 
	GameObject(position, size, texture, color, velocity, textureOffset, textureZoom),
	damage(100.0f)
{
}

SpikeTrap::~SpikeTrap()
{
}

void SpikeTrap::DamagePlayer(Player& player)
{
	// making sure the spikes always kills the player
	damage = player.GetHealth() + 1.0f;

	player.SetHealth(player.GetHealth() - damage);
}
