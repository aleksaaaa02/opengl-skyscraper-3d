#pragma once
#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include "model.h"
#include "mesh.h"
#include "transform.h"
#include <glm/glm.hpp>
#include <list>
#include <memory>


class SceneNode : public Model {
	SceneNode* parent = nullptr;
public:
	std::list<std::unique_ptr<SceneNode>> children;
	Transform Trans;
	void AddChild(const Mesh &mesh);
	void AddChild(std::unique_ptr<SceneNode> node);
	void DrawSelfAndChild(Shader& shader);
	SceneNode();
	SceneNode(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	explicit SceneNode(const Mesh& mesh);
	explicit SceneNode(const std::shared_ptr<Mesh> &mesh);
	~SceneNode();
};

#endif // DEBUG

