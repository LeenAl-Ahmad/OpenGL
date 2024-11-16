#ifndef CAMERA_H
#define CAMERA_H

#include "StandardInclude.h"

class Camera
{
public:
	Camera() = default;
	Camera(const Resolution& _reso, const float _n =0.1f, const float _f =1000.0f);
	virtual ~Camera() = default;

	void SetLookAtTarget(const glm::vec3& _lookAt);
	void LookAt(const glm::vec3& _position, const glm::vec3& _lookAt, const glm::vec3& _up) {
		position = _position;
		view = glm::lookAt(_position, _lookAt, _up);
	}

	glm::mat4 GetProjection() { return projection; }
	glm::mat4 GetView() { return view; }
	glm::vec3 GetPosition() { return position; }
	glm::vec3 GetLookAtTarget() const { return target; }

	void SetPosition(const glm::vec3& _pos);
	void UpdateProjection(const Resolution& _res);

private:
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::vec3 position = {};
	glm::vec3 target = glm::vec3(0.0f);     // Look-at target for the camera
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // Up vector for the camera (default is Y-axis)
};

#endif // !CAMERA_H