#include "Camera.h"

Camera::Camera(Resolution _resolution)
{
	projection = glm::perspective(glm::radians(45.0f), (float)_resolution.width / (float)_resolution.height, 0.1f, 1000.0f);
	view = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}