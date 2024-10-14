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

	float a =0.5f;
	float b = 1.0f;

	vertexData = {
		// Positions             // Colors (R, G, B, A)
		-a, -a, 0.0f,     1.0f, 0.0f ,0.0f ,1.0f,  // Vertex 0 (bottom-left)
		 a,  a, 0.0f,     0.0f, 0.549f, 0.0f, 1.0f, // Vertex 1 (top-right)
		-a,  a, 0.0f,     1.0f, 1.0f, 0.0f, 1.0f,  // Vertex 2 (top-left)
		 a, -a, 0.0f,     1.0f, 1.0f, 0.0f, 1.0f,
	
	};


	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

#pragma region Icosahedron Index Data
	indexData = {
		0,1, 2,
		0,3,1
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
	vertexBuffer = 0;
	indexBuffer = 0;
}

void Mesh::Render(glm::mat4 wvp) {
	glUseProgram(shader->GetProgramID());
	
	float time = glfwGetTime();
	float scale = 0.01f + (sin(time) + 1.0f) / 2.0f * (2.0f - 0.01f);

	// Create a temporary scaled vertex data
	std::vector<float> scaledVertexData;
	for (size_t i = 0; i < vertexData.size(); i += 7) { // Assume each vertex has 7 components
		scaledVertexData.push_back(vertexData[i] * scale);       // X
		scaledVertexData.push_back(vertexData[i + 1] * scale);           // Y (no scaling)
		scaledVertexData.push_back(vertexData[i + 2] * scale);   // Z
		scaledVertexData.push_back(vertexData[i + 3]);           // R
		scaledVertexData.push_back(vertexData[i + 4]);           // G
		scaledVertexData.push_back(vertexData[i + 5]);           // B
		scaledVertexData.push_back(vertexData[i + 6]);           // A
	}

	// Update buffer data with the scaled vertices
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, scaledVertexData.size() * sizeof(float), scaledVertexData.data(), GL_STATIC_DRAW);

	wvp *= world;
	glUniformMatrix4fv(shader->GetAttrWVP(), 1, FALSE, &wvp[0][0]);
	

	// Vertex and color attribute setup
	glEnableVertexAttribArray(shader->GetAttrVertices());
	glVertexAttribPointer(
		shader->GetAttrVertices(),
		3,
		GL_FLOAT,
		GL_FALSE,
		7 * sizeof(float),
		(void*)0
	);

	glEnableVertexAttribArray(shader->GetAttrColors());
	glVertexAttribPointer(
		shader->GetAttrColors(),
		4,
		GL_FLOAT,
		GL_FALSE,
		7 * sizeof(float),
		(void*)(3 * sizeof(float)));

	// Draw the Icosahedron
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	//glDrawArrays(GL_TRIANGLES, 0, vertexData.size()/7);
	glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_BYTE, (void*)0);
	glDisableVertexAttribArray(shader->GetAttrVertices());
	glDisableVertexAttribArray(shader->GetAttrColors());
}

void Mesh::SetRotation(float rotationX, float rotationY) {
	world = glm::rotate(glm::mat4(1.0f), glm::radians(rotationY), glm::vec3(0, 1, 0)); // Y-axis rotation
	world = glm::rotate(world, glm::radians(rotationX), glm::vec3(1, 0, 0));
}
