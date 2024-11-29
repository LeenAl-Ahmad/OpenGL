#ifndef MESH_H
#define MESH_H 

#include "StandardInclude.h"
#include "Texture.h"

class Shader;

class Mesh
{
public:
	Mesh() = default;
	virtual ~Mesh();

	void SetPosition(glm::vec3 _p) { position = _p; }
	glm::vec3 GetPosition() { return position; }
	//void SetRotation1(glm::vec3 _rotation1) { rotation1 = _rotation1; }
	//glm::vec3 GetRotation1() { return rotation1; }
	void SetScalo(glm::vec3 _s) { scale = _s; }
	void SetColor(glm::vec3 _color) { color = _color; }
	glm::vec3 GetColor() { return color; }
	void SetLightDirection(glm::vec3 _lD) { lightDirection = _lD; }
	glm::vec3 GetLightDirection() { return lightDirection; }
	void SetCameraPosition(glm::vec3 _camerPosition) { cameraPosition = _camerPosition; }

	void Create(Shader* _shader, std::string _file);
	void Cleanup();
	void CalculateTransform();
	void Render(glm::mat4 wvp);
	void SetRotation(float x, float y);

	size_t GetVertexDataSize() const;
	size_t GetIndexDataSize() const;

private:
	void SetShaderVariable(glm::mat4 _pv);
	void BindAttributes();
	std::string Concat(const std::string& _s1, int _index, const std::string& _s2);
	//std::string RemoveFolder(std::string& _map);

	Shader* shader;
	//Texture textureDiffuse{};
	//Texture textureSpecular{};
	//Texture textureNormal{};
	GLuint vertexBuffer = 0;
	GLuint indexBuffer = 0;
	std::vector<GLfloat> vertexData;
	std::vector<GLbyte> indexData;
	//bool enableNormalMaps = false;

	glm::mat4 world = glm::mat4(1);
	glm::vec3 position{ 0.0f, 0.0f, 0.0f };
	glm::vec3 lightDirection{ 0.0f, 0.0f, 0.0f };
	glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
	glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
	glm::vec3 color{ 1.0f, 1.0f, 1.0f };
	glm::vec3 cameraPosition{ 0.0f, 0.0f, 0.0f };
};

#endif // ! MESH_H