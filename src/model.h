#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "mesh.h"
#include <GL/glew.h>

class Model {
private:
	Mesh mesh;
	
public:
	void Draw(Shader& shader);
	Model(Mesh mesh);
	~Model();
};

#endif // !DEBUG

