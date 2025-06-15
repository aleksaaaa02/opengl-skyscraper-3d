#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <vector>
#include "mesh.h"
#include <GL/glew.h>

class Model {
protected:
	std::shared_ptr<Mesh> mesh;
	
public:
	void Draw(Shader& shader);
	Model(const Mesh& mesh);
	Model(std::shared_ptr<Mesh> mesh);
	Model(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	Model() = default;
	~Model();
};

#endif // !DEBUG

