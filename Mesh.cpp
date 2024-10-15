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
	texture.LoadTexture("C:/Users/leana/source/repos/OpenGL/Assets/Tacos.jpg");

	float a =5.0f;
	

	vertexData = {
		// Positions      // Colors (R, G, B)  // Texture coordinates 
		 a,  a, 0.0f,     1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 
		 a, -a, 0.0f,     0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
		-a, -a, 0.0f,     0.0f, 0.0f ,1.0f,    0.0f, 0.0f,
		-a,  a, 0.0f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f
	
	};


	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

#pragma region Icosahedron Index Data
	indexData = {
		2, 0, 3,
		2, 1, 0
	};
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
	vertexBuffer = 0;
	indexBuffer = 0;
}

void Mesh::Render(glm::mat4 wvp) {
	glUseProgram(shader->GetProgramID());

	wvp *= world;
	glUniformMatrix4fv(shader->GetAttrWVP(), 1, FALSE, &wvp[0][0]);
	

	// Vertex and color attribute setup
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

	glEnableVertexAttribArray(shader->GetAttrColors());
	glVertexAttribPointer(
		shader->GetAttrColors(),
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(float),
		(void*)(3 * sizeof(float))
	);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glEnableVertexAttribArray(shader->GetAttrTexCoords());
	glVertexAttribPointer(
		shader->GetAttrTexCoords(),
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(float),
		(void*)(6 * sizeof(float))
	);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.GetTexture());
	glUniform1i(shader->GetSampler1(), 0);
	
	//glDrawArrays(GL_TRIANGLES, 0, vertexData.size()/8);
	glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_BYTE, (void*)0);
	glDisableVertexAttribArray(shader->GetAttrVertices());
	glDisableVertexAttribArray(shader->GetAttrColors());
	glDisableVertexAttribArray(shader->GetAttrTexCoords());
}

void Mesh::SetRotation(float rotationX, float rotationY) {
	world = glm::rotate(glm::mat4(1.0f), glm::radians(rotationY), glm::vec3(0, 1, 0)); // Y-axis rotation
	world = glm::rotate(world, glm::radians(rotationX), glm::vec3(1, 0, 0));
}
