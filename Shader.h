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
	GLuint GetAttrTangents() { return attrTangents; }
	GLuint GetAttrBitangents() { return attrBitangents; }
	GLuint GetAttrInstanceMatrix() { return attrInstanceMatrix; }
	
	GLuint GetAttrSPS() {return attrSpStrength;}

	GLuint GetAttrML() {
		return MoveLight;
	}

	GLuint GetLightPos()
	{
		return lightPos;
	}
	
	GLuint GetAttrR() {
		return redbar;
	}
	GLuint GetAttrG() {
		return greenBar;
	}
	GLuint GetAttrB() {
		return blueBar;
	}
	GLuint GetAttrCP() {
		return posColor;
	}
	GLuint GetAttrROP() {
		return setObjPos;
	}
	GLuint GetAttrMC() {
		return moveCube;
	}

	// Methods
	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();
	void SetVec3(const char* _name, glm::vec3 _value);
	void SetMat4(const char* _name, glm::mat4 _value);
	void SetFloat(const char* _name, float _v);
	void SetTextureSampler(const char* _name, GLuint _texUint, int _texYintId, int _v);
	void SetInt(const char* _name, int _v);
	void SetUniform(const std::string& name, float value);

private:
	// Methods
	void CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath);
	GLuint LoadShaderFile(const char* _filePath, GLenum _type);
	void LoadAttributes();
	void EvaluateShader(int _infoLength, GLuint _id);
	

	// Members
	GLuint programID = 0;
	GLuint attrVertices = 0;
	GLuint attrColors = 0;
	GLuint attrWVP = 0;
	GLuint attrNormals = 0;
	GLuint attrTexCoords = 0;
	GLuint attrSpStrength = 0;

	GLint result = GL_FALSE;
	int infoLogLength = 0;

	GLuint attrTangents = 0;
	GLuint attrBitangents = 0;

	GLuint attrInstanceMatrix = 0;

	GLuint MoveLight = 0;
	GLuint lightPos = 0;
	GLuint redbar = 0;
	GLuint greenBar = 0;
	GLuint blueBar = 0;
	GLuint posColor = 0;
	GLuint setObjPos = 0;
	GLuint moveCube = 0;
};

#endif // !SHADER_H