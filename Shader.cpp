#include "Shader.h"
#include <iostream>

Shader::~Shader()
{
	if (programID != 0)
	{
		glDeleteProgram(programID);
	}
}

void Shader::Cleanup()
{
	glDeleteProgram(programID);
	programID = 0;
}

void Shader::LoadAttridutes()
{
	attrVertices = glGetAttribLocation(programID, "vertices");
	attrColors = glGetAttribLocation(programID, "colors");
	attrWVP = glGetUniformLocation(programID, "WVP");
}

void Shader::EvaluateShader(int _infoLength, GLuint _id)
{
	if (_infoLength > 0)
	{

		std::vector<char> errorMessage(_infoLength + 1);
		glGetShaderInfoLog(_id, _infoLength, NULL, &errorMessage[0]);

		//print error
		std::cerr << "Shader Compilation/Linking Error:\n" << &errorMessage[0] << std::endl;

		M_ASSERT(0, ("%s\n", &errorMessage[0]));
	}
}

GLuint Shader::LoadShaderFile(const char* _filePath, GLenum _type)
{
	GLuint shaderID = glCreateShader(_type);

	// read the shader files
	std::string shaderCode;

	std::ifstream shaderStream(_filePath, std::ios::in);
	M_ASSERT(shaderStream.is_open(), ("Impossible to open %s. Are you in the right directory? Don't forget to read the FAQ!\n", _filePath));
	std::string Line = "";
	while (getline(shaderStream, Line))
	{
		shaderCode += "\n" + Line;
	}
	shaderStream.close();

	//compile
	char const* sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);

	//check
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	EvaluateShader(infoLogLength, shaderID);

	//Attach shader to program 
	glAttachShader(programID, shaderID);

	return shaderID;

}

void Shader::CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath)
{
	programID = glCreateProgram();
	GLuint vertexShaderID = LoadShaderFile(_vertexFilePath, GL_VERTEX_SHADER);
	GLuint fragmentShaderID = LoadShaderFile(_fragmentFilePath, GL_FRAGMENT_SHADER);
	glLinkProgram(programID);

	//check
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	EvaluateShader(infoLogLength, programID);

	//Free resources
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void Shader::LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath)
{
	CreateShaderProgram(_vertexFilePath, _fragmentFilePath);
	LoadAttridutes();
}