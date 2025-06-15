#include "model.h"
void Model::Draw(Shader& shader) 
{
		mesh -> Draw(shader);
}

Model::Model(std::shared_ptr<Mesh> mesh) : mesh(mesh)
{

}


Model::Model(const Mesh& mesh) : mesh(std::make_shared<Mesh>(mesh))
{

}

Model::Model(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) : mesh(std::make_shared<Mesh>(vertices, indices))
{

}

Model::~Model() = default;

