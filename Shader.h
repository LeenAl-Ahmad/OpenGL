#ifndef SHADER_H
#define SHADER_H

#include "..\OpenGL\StandardInclude.h"

class Shader
{
public:
	//Constructor / Destructor
	Shader() = default;
	virtual ~Shader();

	//Accessors
	GLuint GetProgramID() { return programID; }
	GLuint GetAttrVertices() { return attrVertices; }
	GLuint GetAttrColors() { return attrColors; }
	GLuint GetAttrWVP() { return attrWVP; }
	GLuint GetAttrNormals() { return attrNormals; }
	GLuint GetAttrTexCoords() { return  attrTexCoords; }
	GLuint GetSampler1() { return sampler1; }
	GLuint GetSampler2() { return sampler2; }
	// Methods
	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();
	void SetVec3(const char* _name, glm::vec3 _value);
	

private:
	// Methods
	void CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath);
	GLuint LoadShaderFile(const char* _filePath, GLenum _type);
	void LoadAttridutes();
	void EvaluateShader(int _infoLength, GLuint _id);
	

	// Members
	GLuint programID = 0;
	GLuint attrVertices = 0;
	GLuint attrColors = 0;
	GLuint attrWVP = 0;
	GLuint attrNormals = 0;
	GLuint attrTexCoords = 0;
	GLuint sampler1 = 0;
	GLuint sampler2 = 0;
	GLint result = GL_FALSE;
	int infoLogLength = 0;
};

#endif // !SHADER_H