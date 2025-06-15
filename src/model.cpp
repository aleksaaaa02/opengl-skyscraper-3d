#include "model.h"
void Model::Draw(Shader& shader) 
{
		mesh.Draw(shader);
}

Model::Model(Mesh mesh) : mesh(mesh)
{

}

Model::~Model()
{
	
}

