#include "Mesh.h"
#include "Shader.h"

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

void Mesh::Create(Shader* _shader)
{
	shader = _shader;
	
	texture = Texture();
	texture.LoadTexture("C:/Users/leana/source/repos/OpenGL/Assets/MetalFrameWood.jpg");
	
	texture2 = Texture();
	texture2.LoadTexture("C:/Users/leana/source/repos/OpenGL/Assets/MetalFrame.jpg");
	
	float a =5.0f;
	
	/*vertexData = {
		// Positions      // Colors (R, G, B)  // Texture coordinates 
		 a,  a, 0.0f,     1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 
		 a, -a, 0.0f,     0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
		-a, -a, 0.0f,     0.0f, 0.0f ,1.0f,    0.0f, 0.0f,
		-a,  a, 0.0f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f
	
	};*/
	vertexData = {
		/* Position */ /* Normals */ /* Texture Coords */
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f

	};


	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

	/*#pragma region Icosahedron Index Data
	indexData = {
		2, 0, 3,
		2, 1, 0
	};*/

#pragma endregion

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, indexData.size() * sizeof(unsigned int), indexData.data(), GL_STATIC_DRAW);
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
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
#pragma endregion

#pragma region index attribute buffer 
	/*glEnableVertexAttribArray(shader->GetAttrColors());
	glVertexAttribPointer(
		shader->GetAttrColors(),
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(float),
		(void*)(3 * sizeof(float))
	);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);*/
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


	glDrawArrays(GL_TRIANGLES, 0, vertexData.size()/8);
	//glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_BYTE, (void*)0);
	glDisableVertexAttribArray(shader->GetAttrVertices());
	//glDisableVertexAttribArray(shader->GetAttrColors());
	glDisableVertexAttribArray(shader->GetAttrNormals());
	glDisableVertexAttribArray(shader->GetAttrTexCoords());
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

	shader->SetVec3("light.ambientColor", { 0.1f, 0.1f, 0.1f });
	shader->SetVec3("light.diffuseColor", { 1.0f, 1.0f, 1.0f });
	shader->SetVec3("light.specularColor", { 3.0f, 3.0f, 3.0f });
	shader->SetVec3("light.position", lightPosition);
	shader->SetVec3("light.color", lightColor);
	shader->SetFloat("light.constant", 1.0f);
	shader->SetFloat("light.linear", 0.09f);
	shader->SetFloat("light.quad", 0.032f);

	shader->SetFloat("material.specularStrength", 8.0f);
	shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, texture.GetTexture());
	shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, texture2.GetTexture());
}