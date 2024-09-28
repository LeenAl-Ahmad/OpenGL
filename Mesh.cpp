#include "Mesh.h"
#include "Shader.h"

Mesh::~Mesh()
{
	if (vertexBuffer != 0)
	{
		glDeleteBuffers(1, &vertexBuffer);
	}
}

void Mesh::Create(Shader* _shader)
{
	shader = _shader;

	vertexData = {
		0.2f, 0.2f, 0.0f ,    1.0f, 0.0f ,0.0f ,1.0f,
		0.3f, 0.9f, 0.0f,      0.0f, 1.0f, 0.0f, 1.0f, 
		0.4f, 0.5f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f,
		0.7f, 0.8f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f,
		0.8f, 0.4f, 0.0f,     0.0f, 1.0f, 0.0f, 1.0f, 
		1.0f, 0.6f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.2f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f,
		1.5f, 0.6f, 0.0f,     0.0f, 1.0f, 0.0f, 1.0f
	};
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &vertexBuffer);
}

void Mesh::Render(glm::mat4 wvp)
{
	glUseProgram(shader->GetProgramID());

	glEnableVertexAttribArray(shader->GetAttrVertices());
	
	wvp *= world;
	glUniformMatrix4fv(shader->GetAttrWVP(), 1, FALSE, &wvp[0][0]);
	glVertexAttribPointer(
		shader->GetAttrVertices(),
		3,
		GL_FLOAT,
		GL_FALSE,
		7* sizeof(float),
		(void*)0
	);

	glEnableVertexAttribArray(shader->GetAttrColors());
	glVertexAttribPointer(
		shader->GetAttrColors(),
		4,
		GL_FLOAT,
		GL_FALSE,
		7 * sizeof(float),
		(void*)(3 * sizeof(float))
	);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glDrawArrays(GL_TRIANGLES, 0, vertexData.size()/7);
	glDisableVertexAttribArray(shader->GetAttrVertices());
	glDisableVertexAttribArray(shader->GetAttrColors());

}
