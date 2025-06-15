#include "model.h"
void Model::Draw(Shader& shader) 
{
		mesh.Draw(shader);
}

Model::Model(const Mesh& mesh) : mesh(mesh)
{

}

Model::Model(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) : mesh(vertices, indices)
{

}

Model::~Model() = default;

