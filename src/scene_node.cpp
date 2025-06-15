#include "scene_node.h"

void SceneNode::AddChild(Mesh mesh)
{
	children.emplace_back(std::make_unique<SceneNode>(mesh));
	children.back() -> parent = this;
}

SceneNode::SceneNode(Mesh mesh) : Model(mesh)
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

SceneNode::~SceneNode()
{

}
