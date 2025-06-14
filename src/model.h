#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "mesh.h"
#include <GL/glew.h>

struct Transform {

};

class Model {
private:
	std::vector<Mesh> meshes;
	
public:
	void Draw(Shader& shader);
	Model(std::vector<Mesh> meshes);
	~Model();
};

#endif // !DEBUG

