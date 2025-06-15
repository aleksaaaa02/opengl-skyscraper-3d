#include "transform.h"

Transform::Transform()
{
	
}

void Transform::computeModelMatrix() 
{
	modelMatrix = getLocalModelMatrix();
}

void Transform::computeModelMatrix(const glm::mat4& parentGlobalModelMatrix)
{
	modelMatrix = parentGlobalModelMatrix * getLocalModelMatrix();
}

glm::mat4 Transform::getLocalModelMatrix() 
{
	glm::mat4 transformX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 transformY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	
	// Rotation
	glm::mat4 rotationMatrix = transformY * transformX * transformZ;

	// Translate * Rotation * Scale
	return glm::translate(glm::mat4(1.0f), position) * rotationMatrix * glm::scale(glm::mat4(1.0f), scale);
}
