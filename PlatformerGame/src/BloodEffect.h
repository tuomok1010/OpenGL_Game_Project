#pragma once

// 12.29

#include <vector>

#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"

class BloodEffect
{
public:
	BloodEffect();
	~BloodEffect();

	void Draw(SpriteRenderer& renderer);
	void ResetAnimation();

	GLboolean GetShouldStop()const { return shouldStop; }

	void SetPosition(glm::vec3 newPos) { position = newPos; }

	glm::vec2 GetSize()const { return size; }

private:
	Texture2D* texture{};
	glm::vec2 textureOffset{};
	glm::vec2 textureScale{}; // the "textureZoom" variable in the renderer draw functions
	GLuint texIterator{};

	glm::vec3 position{};
	glm::vec2 size{};
	glm::vec3 color{};
	GLfloat rotation{};

	GLboolean shouldStop{ true };
};