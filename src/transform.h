#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform {
public:
	glm::vec3 position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	
	glm::mat4 getLocalMatrix();
	glm::mat4 getLocalMatrix(glm::mat4 parentModelMatrix);
	Transform();
	~Transform();
};

#endif // !DEBUG

