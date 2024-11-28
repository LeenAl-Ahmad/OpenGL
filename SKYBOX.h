#ifndef SKYBOX_H
#define SKYBOX_H

#include "Mesh.h"

class SkyBox
{
public:
	~SkyBox();

	void Create(Shader* _shader, std::string _fiile, std::vector<std::string> _faces);
	void Cleanup();
	void Render(glm::mat4 _pv);

private:
	void SetShaderVariables(glm::mat4 _pv);
	void BindAttributes();

	Shader* shader = nullptr;
	Texture texture = { };
	GLuint vertexBuffer = -1;
	std::vector<GLfloat> vertexData;
};
#endif // SKYBOX_H