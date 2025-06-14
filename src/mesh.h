#pragma once
#ifndef MESH_H 
#define MESH_H 

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

struct Vertex  {
	glm::vec3 Position;
};

class Mesh {
private: 
	std::vector<Vertex> vertecies;

public:
	Mesh();
	~Mesh() = default;
};

#endif 

