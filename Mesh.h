#ifndef MESH_H
#define MESH_H 

#include "StandardInclude.h"
class Shader;

class Mesh
{
public:
	Mesh() = default;
	virtual ~Mesh();

	void Create(Shader* _shader);
	void Cleanup();
	void Render(glm::mat4 wvp);
	void SetRotation(float x, float y);

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
};

#endif // ! MESH_H