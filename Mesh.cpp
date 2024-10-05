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

void Mesh::CreatePlayer(Shader* _shader)
{
	shader = _shader;
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	vertexData = {
		// Positions           // Colors (R, G, B, A)
		0.0f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f, 1.0f,  // Top vertex (red)
	   -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f, 1.0f,  // Bottom left vertex (red)
		0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f, 1.0f   // Bottom right vertex (red)
	};

	indexData = { 0, 1, 2 };  // Single triangle

	// Generate and bind buffers as before
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(unsigned int), indexData.data(), GL_STATIC_DRAW);
	
}

void Mesh::CreateNPCS(Shader* _shader, float r, float g , float b, float a) 
{
	shader = _shader;
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	vertexData = {
		// Positions           // Colors (R, G, B, A)
		0.0f,  0.5f, 0.0f,    r, g, b, a,  // Top vertex (red)
	   -0.5f, -0.5f, 0.0f,    r, g, b, a,  // Bottom left vertex (red)
		0.5f, -0.5f, 0.0f,    r, g, b, a   // Bottom right vertex (red)
	};

	indexData = { 0, 1, 2 };  // Single triangle

	// Generate and bind buffers as before
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(unsigned int), indexData.data(), GL_STATIC_DRAW);

}

glm::vec3 Mesh::GetPosition() const {
	return position;
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
	
	// Update buffer data with the scaled vertices
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	
	// Apply translation (positioning the NPC)
	world = glm::translate(glm::mat4(1.0f), position);

	// Apply rotation to face the player (rotation around the Z-axis in 2D)
	world = glm::rotate(world, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

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

void Mesh::SetRotation(float angle) {
	rotation = angle;
}

void Mesh::Move(float deltaX, float deltaY) {
	position.x += deltaX;
	position.y += deltaY;
}

void Mesh::Move(glm::vec3 delta) {
	position += delta;
}