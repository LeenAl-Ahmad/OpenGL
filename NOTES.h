












in vec3 tangents;
in vec3 bitangents;

out mat3 retTBN;

vec3 T = normalize(vec3(World * vec4(tangents, 0.0)));
vec3 B = normalize(vec3(World * vec4(bitangents, 0.0)));
vec3 N = normalize(vec3(World * vec4(normals, 0.0)));
retTBN = mat3(T, B, N);


#include "StandardInclude.h"

class GameTime : public Singleton<GameTime>
{
public:
	void Intialize();
	void Update();

	int FrameCount() { return frameCount; }
	int Fps() { return fps; }
	double DeltaTime() { return deltaTime; }
	double StartTime() { return startTime; }
	double CurrentTime() { return currentTime; }

private:
	int frameCount = 0;
	double deltaTime = 0.0;
	double startTime = 0.0;
	double currentTime = 0.0;

	int fps = 0;
	int fpsCounter = 0;
	double lastTime = 0.0;
};

#include "GameTime.h"

void GameTime::Initialize()
{
	stratTime = glfwGetTime();
}

void GameTime::Update()
{
	currentTime = glfwGetTime();
	fpsCounter++;
	if (currentTime - lastTime >= 1.0)
	{
		fps = fpsCounter;
		fpsCounter = 0;
		lastTime += 1.0;
	}
	deltaTime = currentTime - startTime;
	startTime = currentTime;
}

arialFont->RenderText(std::to_string(GameTime::GetInstance().fps()), 100, 100, 0.5f, { 1.0f, 1.0f, 0.0f });

