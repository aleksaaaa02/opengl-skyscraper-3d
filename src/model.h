#pragma once
#include <vector>
#include "mesh.h"
#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>


class Model {
private:
	std::vector<Mesh> meshes;
	
public:
	Model();
	~Model();
};

#endif // !DEBUG

