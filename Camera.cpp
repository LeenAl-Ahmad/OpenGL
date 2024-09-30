#include "Camera.h"

Camera::Camera(const Resolution& _resolution, const float _n, const float _f)
{
	projection = glm::perspective(glm::radians(45.0f),
		(float)_resolution.width / (float)_resolution.height,
		_n,
		_f);
	 view = glm::lookAt(
		glm::vec3(0, 0, 0),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0));
}

void Camera::SetPosition(const glm::vec3& position) 
{
	// Set the view matrix based on the new camera position
	view = glm::lookAt(position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Look at the origin
}

void Camera::UpdateProjection(const Resolution& _res)
{
	projection = glm::perspective(glm::radians(_res.FoV),
		(float)_res.width / (float)_res.height,
		0.1f,
		1000.0f);
}