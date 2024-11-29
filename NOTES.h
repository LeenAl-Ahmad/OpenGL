

	

	


	



void Mesh::CalculateTangents(std::vector<objl::Vertex> _v, objl::Vector3& _t, objl::Vector3& _bt)
{
	objl::Vector3 edge1 = _vertices[1].Position - _vertices[0].Position;
	objl::Vector3 edge2 = _vertices[2].Position - _vertices[0].Position;
	objl::Vector2 deltaUV1 = _vertices[1].TextureCoordinate - _vertices[0].TextureCoordinate;
	objl::Vector2 deltaUV2 = _vertices[2].TextureCoordinate - _vertices[0].TextureCoordinate;

	float f = 1.0f / (deltaUV1.X * deltaUV2.Y - deltaUV2.X * deltaUV1.Y);

	_t.X = f * (deltaUV3.Y * edge1.X - deltaUV1.Y * edge2.X);
	_t.Y = f * (deltaUV3.Y * edge1.Y - deltaUV1.Y * edge2.Y);
	_t.Z = f * (deltaUV3.Y * edge1.Z - deltaUV1.Y * edge2.Z);

	_bt.X = f * (-deltaUV2.X * edge1.X + deltaUV1.X * edge2.X);
	_bt.Y = f * (-deltaUV2.X * edge1.Y + deltaUV1.X * edge2.Y);
	_bt.Z = f * (-deltaUV2.X * edge1.Z + deltaUV1.X * edge2.Z);

}

std::vector<objl::Vector3> tangents;
std::vector<objl::Vector3> bitangents;
std::vector<objl::Vertex> triangle;
objl::Vector3 tangent;
objl::Vector3 bitangent;
for (unsigned int j = 0; j < curMesh.Vertices.size(); j += 3)
{
	triangle.clear();
	triangle.push_back(curMesh.Vertices[j]);
	triangle.push_back(curMesh.Vertices[j + 1]);
	triangle.push_back(curMesh.Vertices[j + 2]);
	CalcculateTangents(triangle, tangent, bitangents);
	tangents.push_back(tangent);
	bitangents.push_back(bitangent);



}

if (loader.LoadedMaterials[0].map_bump != "")
{
	int index = j / 3;
	vertexData.push_back(tangents[index].X);
	vertexData.push_back(tangents[index].Y);
	vertexData.push_back(tangents[index].Z);
	vertexData.push_back(bitangents[index].X);
	vertexData.push_back(bitangents[index].Y);
	vertexData.push_back(bitangents[index].Z);
}

vertexStride = 8;
if (enablesNormalMaps)
{
	vertexStride += 6;
}

#pragma region BindNormalMapData

if (enablesNormalMaps)
{
	glEnableVertexAttribArray(shader->GetAttrTangents());
	glVertexAttribPointer(shader->GetAttrBitangents(),
		3, GL_FLOAT, GL_FALSE, vertexStride* sizeof(float), (void*)(8 * sizeof(float)));

		glEnableVertexAttribArray(shader->GetAttrTangents());
		glVertexAttribPointer(shader->GetAttrBitangents()),
			3, GL_FLOAT, GL_FALSE, vertexStride * sizeof(float), (void*)(11 * sizeof(float)));
}

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

