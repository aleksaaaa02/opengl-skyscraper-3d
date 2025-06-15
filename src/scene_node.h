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
private:
	std::list<std::unique_ptr<SceneNode>> children;
	SceneNode* parent = nullptr;
public:
	Transform Trans;
	void AddChild(Mesh mesh);
	void DrawSelfAndChild(Shader& shader);
	SceneNode(Mesh mesh);
	~SceneNode();
};

#endif // DEBUG

