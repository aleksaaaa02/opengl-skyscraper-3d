#include "mesh.h"

Mesh::Mesh(const std::vector<Vertex> &vertices) : vertices(vertices)
{
	meshSetup();
}

Mesh::Mesh() = default;

Mesh::Mesh(const Mesh &other) : vertices(other.vertices)
{
	this -> VAO = other.VAO;
	this -> VBO = other.VBO;
}


void Mesh::Draw(Shader &shader) const {
	glBindVertexArray(VAO);
	shader.setVec4("objectColor", glm::vec4(this -> Colors, 1.0f));
	glDrawArrays(GL_TRIANGLES, 0, static_cast<unsigned int>(vertices.size()));
	glBindVertexArray(0);
}

void Mesh::meshSetup()
{
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

Mesh::~Mesh() 
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}
