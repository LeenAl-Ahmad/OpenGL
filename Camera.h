#ifndef CAMERA_H
#define CAMERA_H

#include "StandardInclude.h"

class Camera
{
public:
	Camera() = default;
	Camera(Resolution _reso);
	virtual ~Camera() = default;

	glm::mat4 GetProjection() { return projection; }
	glm::mat4 GetView() { return view; }

private:
	glm::mat4 projection = {};
	glm::mat4 view = {};
};

#endif // !CAMERA_H


