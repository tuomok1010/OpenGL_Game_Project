#include "Camera.h"

Camera::Camera()
	:
	position(glm::vec3(0.0f, 0.0f, 1.0f)),
	front(glm::vec3(0.0f, 0.0f, -1.0f)),
	up(glm::vec3(0.0f, 1.0f, 0.0f)),
	right(glm::vec3(1.0f, 0.0f, 0.0f))
{
}

Camera::~Camera()
{

}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::Move(CameraDirection direction, float deltaTime)
{
	if (direction == CameraDirection::RIGHT)
		position += right;

	if (direction == CameraDirection::LEFT)
		position -= right;

	if (direction == CameraDirection::UP)
		position += up;

	if (direction == CameraDirection::DOWN)
		position -= up;
}
