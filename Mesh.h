#ifndef MESH_H
#define MESH_H 

#include "StandardInclude.h"
#include "Texture.h"
#include "OBJ_Loader.h"

class Shader;

class Mesh
{
public:
	Mesh() = default;
	virtual ~Mesh();

	//mouse obj
	void SetPositionM(const glm::vec3& newPos);
	glm::vec3 GetPositionM() const;
	void SetRotationObj(const glm::mat4& rotationMatrix) { world = rotationMatrix * world; }
	glm::mat4 GetWorld() const { return world; }
	void SetPosition(glm::vec3 _p) { position = _p; UpdateWorldMatrix(); }
	glm::vec3 GetPosition() { return position; }
	void SetRotationObj(const glm::vec3& rot) { rotation = rot; UpdateWorldMatrix(); }
	glm::vec3 GetRotation1() { return rotation; }
	void SetScalo(glm::vec3 _s) { scale = _s; UpdateWorldMatrix(); }
	void SetColor(glm::vec3 _color) { color = _color; }
	glm::vec3 GetColor() { return color; }
	void SetLightDirection(glm::vec3 _lD) { lightDirection = _lD; }
	glm::vec3 GetLightDirection() { return lightDirection; }
	void SetCameraPosition(glm::vec3 _camerPosition) { cameraPosition = _camerPosition; }
	void SetSpecularStrength(float strength) { specularStrength = strength; }
	float GetSpecularStrength() { return specularStrength; }
	void SetSpecularColor(const glm::vec3& color) { specularColor = color; }
	glm::vec3 GetSpecularColor() const { return specularColor; }

	void Create(Shader* _shader, std::string _file, int _instanceCount = 1);
	void Cleanup();
	void CalculateTransform();
	void Render(glm::mat4 wvp);
	void SetRotation(float x, float y);

	size_t GetVertexDataSize() const;
	size_t GetIndexDataSize() const;

	void SetClicked(bool invert)
	{
		clicked = invert;
	}

	void Mesh::UpdateWorldMatrix() {
		world = glm::mat4(1.0f);
		world = glm::translate(world, position);                     // Apply translation
		world = glm::rotate(world, rotation.x, glm::vec3(1, 0, 0));  // Apply rotation X
		world = glm::rotate(world, rotation.y, glm::vec3(0, 1, 0));  // Apply rotation Y
		world = glm::rotate(world, rotation.z, glm::vec3(0, 0, 1));  // Apply rotation Z
		world = glm::scale(world, scale);
	}

private:
	void SetShaderVariable(glm::mat4 _pv);
	void BindAttributes();
	std::string Concat(const std::string& _s1, int _index, const std::string& _s2);
	std::string RemoveFolder(std::string& _map);
	void CalculateTangents(std::vector<objl::Vertex> _vertices, objl::Vector3& _tang, objl::Vector3& _bitang);

	Shader* shader = nullptr;
	Texture textureDiffuse{};
	Texture textureSpecular{};
	Texture textureNormal{};
	GLuint vertexBuffer = 0;
	GLuint indexBuffer = 0;
	GLuint instanceBuffer = 0;
	std::vector<GLfloat> vertexData;
	std::vector<GLbyte> indexData;
	std::vector<GLfloat> instanceData;
	bool enableNormalMaps = false;

	int instanceCount = 0;
	bool enableInstancing = false;

	int vertexStride = 0;

	glm::mat4 world = glm::mat4(1);
	glm::vec3 position{ 0.0f, 0.0f, 0.0f };
	glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
	glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
	glm::vec3 color{ 1.0f, 1.0f, 1.0f };

	glm::vec3 lightDirection{ 0.0f, 0.0f, 0.0f };
	glm::vec3 cameraPosition{ 0.0f, 0.0f, 0.0f };

	double mouseX, mouseY;

	bool clicked;
	float specularStrength = 1.0f;
	glm::vec3 specularColor;
};

#endif // ! MESH_H