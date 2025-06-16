#pragma once
#ifndef MESH_H 
#define MESH_H 

#include <vector>
#include <glm/glm.hpp>
#include "shader.h"

struct Vertex  {
	glm::vec3 Position;
	glm::vec3 Normal;
};

class Mesh {
	std::vector<Vertex> vertices;
	void meshSetup();
	unsigned int VBO;

public:
	glm::vec3 Colors = { 1.0f, 1.0f, 1.0f };
	unsigned int VAO;
	explicit Mesh(const std::vector<Vertex> &vertices);
	Mesh(const Mesh& other);
	Mesh();
	~Mesh();
	void Draw(Shader &shader) const;
};

#endif 

