#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardInclude.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

#include <array>

class GameController : public Singleton< GameController>
{
public:
	GameController();
	virtual ~GameController() = default;

	void Initialize();
	void RunGame();
	void CyCamera();
	void CyResolution();

private:
	Shader shaderColor = {};
	Shader shaderDiffuse = {};
	std::vector<Mesh*> meshBoxes;
	Mesh* meshLight = {};

	Camera camera = {};
	std::array<Camera, 3> cameras;
	std::array<Resolution, 3> resolutions;
	int currentCameraIndex = 0;
	int currentResolutionIndex = 0;
	float lastFrameTime = 0.0f;
	glm::vec3 cameraPosition = { 10.0f, 10.0f, 10.0f };  // Initial camera position
	glm::vec3 lookAtTarget = { 0.0f, 0.0f, 0.0f };      // Initial LookAt target
	float cameraSpeed = 0.1f;
};

#endif // !GAME_CONTROLLER_H