#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraDirection
{
	RIGHT,
	LEFT,
	UP,
	DOWN
};

class Camera
{
public:
	Camera();
	Camera(glm::vec3 position);
	~Camera();

	glm::mat4 GetViewMatrix();

	void Move(CameraDirection direction);
	void SetPosition(glm::vec3 position);
private:

private:

	glm::vec3 position{};
	glm::vec3 front{};
	glm::vec3 up{};
	glm::vec3 right{};

	GLfloat speed{};
};