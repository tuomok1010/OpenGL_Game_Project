#pragma once

#include "GameObject.h"
#include "Player.h"

class SpikeTrap : public GameObject
{
public:
	SpikeTrap(glm::vec2 position, glm::vec2 size, Texture2D& texture, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f),
		glm::vec2 textureOffset = glm::vec2(0.0f), glm::vec2 textureZoom = glm::vec2(1.0f));
	~SpikeTrap();

	void DamagePlayer(Player& player);

	Type GetType()const override { return type; }

private:
	GLfloat damage{};
	Type type;
};