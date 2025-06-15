#include "camera.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>


Camera::Camera(glm::vec3 position , glm::vec3 up, float ms, float yaw) 
 : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MS(ms), Yaw(yaw), Pitch(0.0f)
{
	this -> Position = position;	
	this -> WorldUp = up;
	updateCamera();
}

void Camera::MoveCamera(Camera_Movment direction, float deltaTime)
{
	float velocity = MS * deltaTime;
	switch (direction) {
		case FORWARD:
			Position += Front * velocity;
			break;
		case BACKWARD:
			Position -= Front * velocity;
			break;
		case LEFT:
			Position -= Right * velocity;
			break;
		case RIGHT:
			Position += Right * velocity;
			break;
		case DOWN:
			Position -= Up * velocity;
			break;
		case UP:
			Position += Up * velocity;
			break;
	}
}

void Camera::updateCamera() 
{
	glm::vec3 front = Front;

	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

	Front = glm::normalize(front);
	
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}

void Camera::RotateCamera(float offsetx, float offsety)
{
	offsetx *= defaultSensitivity;	
	offsety *= defaultSensitivity;

	Yaw += offsetx;
	Pitch += offsety;
	updateCamera();
}