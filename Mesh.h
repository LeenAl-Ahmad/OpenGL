#ifndef MESH_H
#define MESH_H 

#include "StandardInclude.h"
class Shader;

class Mesh
{
public:
	Mesh() = default;
	virtual ~Mesh();

	void CreatePlayer(Shader* _shader);
	void CreateNPCS(Shader* _shader, float r, float g, float b, float a);
	void Cleanup();
	void Render(glm::mat4 wvp);
	void SetRotation(float angle);
	void Move(float deltaX, float deltaY);
	glm::vec3 GetPosition() const;
	void Move(glm::vec3 delta); // for overload
	bool isTagged;
	 
	
	
	size_t GetVertexDataSize() const;
	size_t GetIndexDataSize() const;

private:
	Shader* shader;
	GLuint vertexBuffer = 0;
	GLuint indexBuffer = 0;
	std::vector<GLfloat> vertexData;
	std::vector<GLbyte> indexData;
	glm::mat4 world = glm::mat4(1);
	float lastFrameTime = 0.0f;
	
	glm::vec3 color;
	glm::vec3 position;
	float rotation;

	
};

#endif // ! MESH_H