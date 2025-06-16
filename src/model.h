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
	void Draw(Shader& shader) const;
	explicit Model(const Mesh& mesh);
	explicit Model(std::shared_ptr<Mesh> mesh);
	explicit Model(const std::vector<Vertex>& vertices);
	Model() = default;
	~Model();
};

#endif // !DEBUG

