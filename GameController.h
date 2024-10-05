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
	Shader shader = {};
	Mesh mesh = {};
	Camera camera = {};
	std::array<Camera, 3> cameras;
	std::array<Resolution, 3> resolutions;
	int currentCameraIndex = 0;
	int currentResolutionIndex = 0;
	float lastFrameTime = 0.0f;

	std::vector<Mesh> npcs;
};

#endif // !GAME_CONTROLLER_H