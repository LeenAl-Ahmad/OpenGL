#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "WindowController.h"
#include "Shader.h"
#include "Mesh.h"
#include "SKYBOX.h"
#include "Camera.h"



class GameController : public Singleton< GameController>
{
public:
	GameController() = default;
	virtual ~GameController() = default;

	void Initialize();
	void RunGame();

	//Mouse
	void UpdateObjToMouse(double mouseX, double mouseY);
	void UpdateObj(double mouseX, double mouseY);
	bool ResetLightPos();
	bool ResetObjPos();
	void UpdateScene(GLFWwindow* window);
	void SetSpecularStrength(float strength){specularStrength = strength; }

	std::vector<Mesh*>& GetLights() { return lights; }
	const Camera& GetCamera() { return camera; }

	bool moveLight = false;
	bool colorPosition = false;
	bool moveCube = false;
	bool clickL = false;
	bool clickO = false;
	void HandleMouseClick(GLFWwindow* window);
	void HandleMouseClickForColorByPosition(GLFWwindow* window);
	Mesh* GetSuzanne() const { return suzanne; }
private:
	Camera camera = {};

	Shader shaderColor = {};
	Shader shaderDiffuse = {};
	Shader shaderFont = {};
	Shader shaderSkybox = {};
	Shader shader = {};

	std::vector<Mesh*> meshes;
	std::vector<Mesh*> lights;
	std::vector<Mesh*> cubes;
	SkyBox* skybox = nullptr;

	GLuint vao;

	//Mouse
	int screenWidth, screenHeight;
	glm::mat4 projMatrix;
	glm::mat4 viewMatrix;
	Mesh* light;
	Mesh* suzanne;
	Mesh* cube;
	Mesh* sphere;
	Mesh* newCube;
	
	glm::vec3 lastLightPosition;
	glm::vec3 lastObjPosition;
	float specularStrength = 4.0f;
	
	const float sphereRadius = 0.5f;           // Radius of the sphere
	const float cubeSpeed = 1.0f;
	int minCubesToSpawn = 10;                  // Minimum number of cubes to spawn
	int maxCubesToSpawn = 20;
	float deltaTime = 0.016f;
};

#endif // !GAME_CONTROLLER_H