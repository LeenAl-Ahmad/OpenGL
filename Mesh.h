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
	void Render();

private:
	Shader* shader;
	GLuint vertexBuffer = 0;
	std::vector<GLfloat> vertexData;
};

#endif // ! MESH_H

