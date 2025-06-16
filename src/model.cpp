#include "model.h"

#include <utility>
void Model::Draw(Shader& shader) const {
		mesh -> Draw(shader);
}

Model::Model(std::shared_ptr<Mesh> mesh) : mesh(std::move(mesh))
{

}


Model::Model(const Mesh& mesh) : mesh(std::make_shared<Mesh>(mesh))
{

}

Model::Model(const std::vector<Vertex>& vertices) : mesh(std::make_shared<Mesh>(vertices))
{

}

Model::~Model() = default;

