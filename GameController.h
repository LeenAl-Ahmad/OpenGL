#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "WindowController.h"
#include "Shader.h"
#include "Mesh.h"
#include "SKYBOX.h"
#include "Camera.h"
#include "PostProcessor.h"
#include "StandardInclude.h"

class GameController : public Singleton< GameController>
{
public:
	GameController() = default;
	virtual ~GameController() = default;

	void Initialize();
	void RunGame();

	//Mouse
	void UpdateObjToMouse(double mouseX, double mouseY, GLFWwindow* window, Mesh* mesh);
	bool ResetLightPos();
	bool ResetObjPos();
	void UpdateScene(GLFWwindow* window, Mesh* newCube);
	void SetSpecularStrength(float strength) { specularStrength = strength; }
	float SetR(float r) {return red = r; }
	float GetR() { return red; }
	float SetG(float g) {return green = g; }
	float GetG() { return green; }
	float SetB(float b) {return blue = b; }
	float GetB() { return blue; }

	float setf(float f) { return frequency = f; }
	float Getf() { return frequency; }
	float setA(float a) { return amplitude = a; }
	float GetA() { return amplitude; }

	std::vector<Mesh*>& GetLights() { return lights; }
	const Camera& GetCamera() { return camera; }

	bool moveLight = false;
	bool Transform = false;
	bool translate = false;
	bool rotate = false;
	bool scale = false;
	bool waterScene = false;
	bool wireFrame = false;
	bool tint = false;
	bool space = false;

	bool colorPosition = false;
	bool UpdatedRed = false;
	bool UpdatedGreen = false;
	bool UpdatedBlue = false;
	bool UpdateFrequency = false;
	bool UpdateAmplitude = false;
	bool clickL = false;
	bool clickT = false;
	bool clickO = false;
	float red =0;
	float green =0;
	float blue=0;
	float frequency = 0;
	float amplitude = 0;
	glm::vec3 lightColor = {red, green , blue};
	
	Mesh* GetSuzanne() const { return suzanne; }
	float specularStrength ;

private:
	Camera camera = Camera(WindowController::GetInstance().GetResolution());
	PostProcessor pP = { };

	Shader shaderColor = {};
	Shader shaderDiffuse = {};
	Shader shaderFont = {};
	Shader shaderPixel = {};
	Shader shaderPost = {};
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
	Mesh* suzanne = nullptr;
	Mesh* cube;
	Mesh* sphere;
	Mesh* newCube;
	
	glm::vec3 lastLightPosition;
	glm::vec3 lastObjPosition;
	
	glm::vec3 rotationSpeed = { 0, 0.2, 0 };
	const float sphereRadius = 0.5f;           // Radius of the sphere
	const float cubeSpeed = 1.0f;
	int minCubesToSpawn = 10;                  // Minimum number of cubes to spawn
	int maxCubesToSpawn = 20;
	float deltaTime = 0.016f;
};

#endif // !GAME_CONTROLLER_H