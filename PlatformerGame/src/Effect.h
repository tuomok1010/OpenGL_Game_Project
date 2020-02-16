#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"

class Effect
{
public:
	Effect();
	Effect(const Effect& src);
	virtual ~Effect();

	virtual void Draw(SpriteRenderer& renderer) = 0;
	void ResetAnimation();
	void AddTexture(Texture2D* textureToAdd);
	void Rotate(GLfloat degrees) { rotation = degrees; }

	GLboolean GetShouldStop()const { return shouldStop; }

	void SetPosition(glm::vec2 newPos) { position = newPos; }
	void SetShouldStop(GLboolean newVal) { shouldStop = newVal; }

	glm::vec2 GetSize()const { return size; }

protected:
	std::vector<Texture2D*> textures{};

	glm::vec2 textureOffset{};
	glm::vec2 textureScale{};
	GLuint texIterator{};

	glm::vec2 position{};
	glm::vec2 size{};
	glm::vec3 color{};
	GLfloat rotation{};

	GLboolean shouldStop{ true };

};