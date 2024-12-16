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
	GLuint GetTracKBarR() { return trackBarR; }
	GLuint GetTracKBarG() { return trackBarG; }
	GLuint GetTracKBarB() { return trackBarB; }
	GLuint GetAttrSPS() {return attrSpStrength;}
	GLuint GetAttrCP() {return attrColorByPos;}

	GLuint GetAttrFrequency() { return frequency; }
	GLuint GetAttrAmplitude() { return amplitude; }
	GLuint GetAttrTime() { return time; }

	GLuint GetIfTrue() { return answer; }

	GLuint GetAttrML() {
		return MoveLight;
	}

	GLuint GetLightPos()
	{
		return lightPos;
	}
	
	GLuint GetAttrROP() {
		return setObjPos;
	}
	GLuint GetAttrWire() {
		return wireframe;
	}
	GLuint GetTint()
	{
		return tint;
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
	void SetBool(const char* _name, bool _value);

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
	GLuint attrColorByPos = 0;
	GLuint trackBarR = 0;
	GLuint trackBarG = 0;
	GLuint trackBarB = 0;
	GLuint attrModel = 0;
	GLuint attrView = 0;
	GLuint attrProjection = 0;
	GLuint screenTexture = 0;
	GLuint frequency = 0;
	GLuint amplitude = 0;
	GLuint time = 0;
	GLuint wireframe = 0;
	GLuint tint = 0;
	GLuint answer = 0;

	GLint result = GL_FALSE;
	int infoLogLength = 0;

	GLuint attrTangents = 0;
	GLuint attrBitangents = 0;

	GLuint attrInstanceMatrix = 0;

	GLuint MoveLight = 0;
	GLuint lightPos = 0;
	
	GLuint setObjPos = 0;
	GLuint moveCube = 0;
};

#endif // !SHADER_H