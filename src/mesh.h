#pragma once
#ifndef MESH_H 
#define MESH_H 

#include <vector>
#include <glm/glm.hpp>
#include "shader.h"

struct Vertex  {
	glm::vec3 Position;
	glm::vec4 Colors;
};

class Mesh {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	void meshSetup();
	unsigned int VBO, EBO;

public:
	unsigned int VAO;
	Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);
	Mesh(const Mesh& other);
	Mesh();
	~Mesh();
	void Draw(Shader &shader) const;
};

#endif 

