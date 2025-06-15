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
	Transform transform;
	std::list<std::unique_ptr<SceneNode>> children;
	SceneNode* parent = nullptr;

public:
	void AddChild(std::vector<Mesh> meshes);
	SceneNode(std::vector<Mesh> meshes);
	~SceneNode();
};

#endif // DEBUG

