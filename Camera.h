#ifndef CAMERA_H
#define CAMERA_H

#include "StandardInclude.h"

class Camera
{
public:
	Camera() = default;
	Camera(const Resolution& _reso, const float _n =0.1f, const float _f =1000.0f);
	virtual ~Camera() = default;

	
	void LookAt(const glm::vec3& _position, const glm::vec3& _lookAt, const glm::vec3& _up) {
		position = _position;
		view = glm::lookAt(_position, _lookAt, _up);
	}

	glm::mat4 GetProjection() { return projection; }
	glm::mat4 GetView() { return view; }
	glm::vec3 GetPosition() { return position; }

	void SetPosition(const glm::vec3& _pos);
	void UpdateProjection(const Resolution& _res);

private:
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::vec3 position = {};
};

#endif // !CAMERA_H