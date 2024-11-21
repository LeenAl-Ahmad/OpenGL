#include "Mesh.h"
#include "Shader.h"
#include "GameController.h"
#include <OBJ_Loader.h>

Mesh::~Mesh()
{
	if (vertexBuffer != 0)
	{
		glDeleteBuffers(1, &vertexBuffer);
	}
	if (indexBuffer != 0)
	{
		glDeleteBuffers(1, &indexBuffer);
	}
	texture.Cleanup();
	texture2.Cleanup();
}

size_t Mesh::GetVertexDataSize() const {
	return vertexData.size();
}

size_t Mesh::GetIndexDataSize() const {
	return indexData.size();
}

void Mesh::Create(Shader* _shader, std::string _file)
{
	shader = _shader;
	
	objl::Loader loader;
	M_ASSERT(loader.LoadFile(_file) == true, "Failed to load mesh");

	for (unsigned int i = 0; i < loader.LoadedMeshes.size(); i++)
	{
		objl::Mesh curMesh = loader.LoadedMeshes[i];
		for (unsigned int j = 0; j < curMesh.Vertices.size(); j++)
		{
			vertexData.push_back(curMesh.Vertices[j].Position.X);
			vertexData.push_back(curMesh.Vertices[j].Position.Y);
			vertexData.push_back(curMesh.Vertices[j].Position.Z);
			vertexData.push_back(curMesh.Vertices[j].Normal.X);
			vertexData.push_back(curMesh.Vertices[j].Normal.Y);
			vertexData.push_back(curMesh.Vertices[j].Normal.Z);
			vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.X);
			vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.Y);
		}
	}

	std::string diffuseMap = loader.LoadedMaterials[0].map_Kd;
	const size_t last_slash_idx = diffuseMap.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		diffuseMap.erase(0, last_slash_idx + 1);
	}

	texture = Texture();
	texture.LoadTexture("C:/Users/leana/source/repos/OpenGL/Assets/Models/" + diffuseMap);

	texture2 = Texture();
	texture2.LoadTexture("C:/Users/leana/source/repos/OpenGL/Assets/Models/" + diffuseMap);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

}


void Mesh::Cleanup()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	texture.Cleanup();
	texture2.Cleanup();
	vertexBuffer = 0;
	indexBuffer = 0;
}

void Mesh::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
#pragma region vertices attribute buffer 
	glEnableVertexAttribArray(shader->GetAttrVertices());
	glVertexAttribPointer(
		shader->GetAttrVertices(),
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(float),
		(void*)0
	);
	
#pragma endregion

#pragma region normals attribute buffer 
	glEnableVertexAttribArray(shader->GetAttrNormals());
	glVertexAttribPointer(
		shader->GetAttrNormals(),
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(float),
		(void*)(3 * sizeof(float))
	);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
#pragma endregion

#pragma region  TexCoords attribute buffer 
	glEnableVertexAttribArray(shader->GetAttrTexCoords());
	glVertexAttribPointer(
		shader->GetAttrTexCoords(),
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(float),
		(void*)(6 * sizeof(float))
	);
#pragma endregion

}

void Mesh::Render(glm::mat4 _pv) {
	glUseProgram(shader->GetProgramID());


	rotate.y += 0.005f;
	
	CalculateTransform();
	SetShaderVariable(_pv);
	BindAttributes();


	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(unsigned int), indexData.data(), GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_INT, 0);

}

void Mesh::SetRotation(float rotationX, float rotationY) {
	world = glm::rotate(glm::mat4(1.0f), glm::radians(rotationY), glm::vec3(0, 1, 0)); // Y-axis rotation
	world = glm::rotate(world, glm::radians(rotationX), glm::vec3(1, 0, 0));
}

void Mesh::CalculateTransform() {
	world = glm::translate(glm::mat4(1.0f), position);
	//world = glm::rotate(world, rotate.y, glm::vec3(0, 1, 0));
	//world = glm::rotate(world, rotate.x, glm::vec3(1, 0, 0));
	//world = glm::rotate(world, rotate.z, glm::vec3(0, 0, 1));
	world = glm::scale(world, scale);
}

void Mesh::SetShaderVariable(glm::mat4 _pv)
{
	shader->SetMat4("World", world);
	shader->SetMat4("WVP", _pv * world);
	shader->SetVec3("CameraPosition", cameraPosition);

	std::vector<Mesh*>& lights = GameController::GetInstance().GetLights();
	for (int i = 0; i < lights.size(); i++)
	{
		shader->SetVec3(Concat("light[", i,"].ambientColor").c_str(), {0.1f, 0.1f, 0.1f});
		shader->SetVec3(Concat("light[", i, "].diffuseColor").c_str(), lights[i]->GetColor());
		shader->SetVec3(Concat("light[", i, "].specularColor").c_str(), { 3.0f, 3.0f, 3.0f });

		shader->SetVec3(Concat("light[", i, "].position").c_str(), lights[i]->GetPosition());
		shader->SetVec3(Concat("light[", i, "].direction").c_str(), lights[i]->GetLightDirection());
		
		shader->SetFloat(Concat("light[", i, "].constant").c_str(), 1.0f);
		shader->SetFloat(Concat("light[", i, "].linear").c_str(), 0.09f);
		shader->SetFloat(Concat("light[", i, "].quadratic").c_str(), 0.032f);

		shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(15.0f));
		shader->SetFloat(Concat("light[", i, "].falloff").c_str(), 100);
	}
	

	shader->SetFloat("material.specularStrength", 8.0f);
	shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, texture.GetTexture());
	shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, texture2.GetTexture());
}

std::string Mesh::Concat(const std::string& _s1, int _index, const std::string& _s2)
{
	std::string index = std::to_string(_index);
	return (_s1 + index + _s2);
}