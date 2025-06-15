#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <iostream>

const float defaultMS = 2.5f;
const float defaultYaw = -90.0f;
const float defaultPitch = 0.0f;
const float defaultSensitivity = 0.01;

enum Camera_Movment
{
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT,
	UP,
	DOWN
};

class Camera {
public:
	glm::vec3 Position;	
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	
	float Yaw;
	float Pitch;
	float MS;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float ms = defaultMS, float yaw = defaultYaw);
	~Camera() = default;
	void MoveCamera(Camera_Movment direction, float deltaTime);
	void RotateCamera(float offsetx, float offsety);
	glm::mat4 GetViewMatrix();
private:
	void updateCamera();	
};

#endif // !DEBUG
