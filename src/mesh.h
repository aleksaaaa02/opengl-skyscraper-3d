#pragma once
#ifndef MESH_H 
#define MESH_H 

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "shader.h"

struct Vertex  {
	glm::vec3 Position;
	glm::vec3 Colors;
};

class Mesh {
private: 
	std::vector<Vertex> vertecies;
	std::vector<unsigned int> indecies;
	void meshSetup();
	unsigned int VBO, EBO;
public:
	unsigned int VAO;
	Mesh(std::vector<Vertex> vertecies, std::vector<unsigned int> indecies);
	~Mesh() = default;
	void Draw(Shader &shader);
};

#endif 

