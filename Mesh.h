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
	void SetScalo(glm::vec3 _s) { scale = _s; }
	void SetLightPosition(glm::vec3 _lightPosition) { lightPosition = _lightPosition; }
	void SetLightColor(glm::vec3 _lightColor) { lightColor = _lightColor; }
	void SetCameraPosition(glm::vec3 _camerPosition) { cameraPosition = _camerPosition; }

	void Create(Shader* _shader);
	void Cleanup();
	void CalculateTransform();
	void Render(glm::mat4 wvp);
	void SetRotation(float x, float y);

	size_t GetVertexDataSize() const;
	size_t GetIndexDataSize() const;

private:
	void SetShaderVariable(glm::mat4 _pv);
	void BindAttributes();

	Shader* shader;
	Texture texture{};
	Texture texture2{};
	GLuint vertexBuffer = 0;
	GLuint indexBuffer = 0;
	std::vector<GLfloat> vertexData;
	std::vector<GLbyte> indexData;

	glm::mat4 world = glm::mat4(1);
	glm::vec3 position{ 0.0f, 0.0f, 0.0f };
	glm::vec3 rotate{ 0.0f, 0.0f, 0.0f };
	glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
	glm::vec3 lightPosition{ 0.0f, 0.0f, 0.0f };
	glm::vec3 lightColor{ 1.0f, 1.0f, 1.0f };
	glm::vec3 cameraPosition{ 0.0f, 0.0f, 0.0f };
};

#endif // ! MESH_H