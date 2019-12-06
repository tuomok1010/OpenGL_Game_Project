#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera();
	~Camera();
private:

private:
	glm::vec3 position{};
	glm::vec3 front{};
	glm::vec3 up{};

	GLfloat speed{};
};