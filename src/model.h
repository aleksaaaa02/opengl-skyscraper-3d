#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "mesh.h"
#include <GL/glew.h>

class Model {
protected:
	Mesh mesh;
	
public:
	void Draw(Shader& shader);
	Model(const Mesh& mesh);
	Model(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	Model() = default;
	~Model();
};

#endif // !DEBUG

