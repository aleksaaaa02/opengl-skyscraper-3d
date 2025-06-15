#include "scene_node.h"

void SceneNode::AddChild(const Mesh& mesh)
{
	children.emplace_back(std::make_unique<SceneNode>(mesh));
	children.back() -> parent = this;
}

SceneNode::SceneNode(const Mesh& mesh) : Model(mesh)
{

}

SceneNode::SceneNode(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) : Model(vertices, indices)
{

}
void SceneNode::DrawSelfAndChild(Shader& shader)
{ 
	shader.setMat4("model", Trans.getLocalModelMatrix());
	Draw(shader);
	
	for(auto&& child : children)
	{
		child -> DrawSelfAndChild(shader);
	}	
}

SceneNode::~SceneNode() = default;
