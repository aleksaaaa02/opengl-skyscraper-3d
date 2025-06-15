#include "scene_node.h"

void SceneNode::AddChild(std::vector<Mesh> meshes)
{
	children.emplace_back(std::make_unique<SceneNode>(meshes));
}

SceneNode::SceneNode(std::vector<Mesh> meshes) : Model(meshes)
{
}

SceneNode::~SceneNode()
{

}
