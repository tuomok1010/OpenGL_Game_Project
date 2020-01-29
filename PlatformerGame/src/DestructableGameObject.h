#pragma once

#include "GameObject.h"

class DestructableGameObject : public GameObject
{
public:
	DestructableGameObject(glm::vec2 position, glm::vec2 size, Texture2D& texture, glm::vec3 color = glm::vec3(1.0f), GLfloat speed = 100.0f, 
		glm::vec2 textureOffset = glm::vec2(0.0f), glm::vec2 textureScale = glm::vec2(1.0f));
	~DestructableGameObject();

	void Draw(SpriteRenderer& renderer, PrimitiveRenderer& colBoxRenderer, GLboolean renderCollisionBox = false, GLuint textureUnit = 0) override;

	void TakeDamage(GLfloat damage);
private:
	GLboolean isDestructable{};
	GLfloat health{};
};