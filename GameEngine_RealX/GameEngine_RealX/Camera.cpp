#ifndef CAMERA_H
#define CAMERA_H
#include "Camera.h"
#endif

// Update camera vectors.
void Camera::UpdateCameraVectors() {
	// Calculating the new front vector.
	glm::vec3 tmpFront = glm::vec3(
		cos(glm::radians(yaw) * cos(glm::radians(pitch))),
		sin(glm::radians(pitch)),
		sin(glm::radians(yaw) * cos(glm::radians(pitch)))
	);
	front = glm::normalize(tmpFront);
	// Re-calculating the right and up vector.
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

// Custom constructor that takes vector as input.
Camera::Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
		       glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f),
	           float yaw = YAW, float pitch = PITCH) 
{
	this->position = position;
	this->worldUp = worldUp;
	this->yaw = YAW;
	this->pitch = PITCH;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	movementSpeed = SPEED;
	sensitivity = SENSITIVITY;
	zoom = ZOOM;
}

// Default constructor.
Camera::Camera()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->yaw = YAW;
	this->pitch = PITCH;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	movementSpeed = SPEED;
	sensitivity = SENSITIVITY;
	zoom = ZOOM;
}

// Custom constructor that float data as input.
Camera::Camera(float posX, float posY, float posZ,
			   float worldUpX, float worldUpY, float worldUpZ,
	           float yaw, float pitch)
{
	position = glm::vec3(posX, posY, posZ);
	worldUp = glm::vec3(worldUpX, worldUpY, worldUpZ);
	this->yaw = yaw;
	this->pitch = pitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	movementSpeed = SPEED;
	sensitivity = SENSITIVITY;
	zoom = ZOOM;
}

// Get camera view matrix;
glm::mat4 Camera:: getViewMatrix() {
	return glm::lookAt(position, position + front, up);
}

// Handling keyboard to move camera in directions.
void Camera::KeyBoardHandler(CameraMovement direction, float deltaTime) {
	float cameraVelocity = movementSpeed * deltaTime;
	switch (direction)
	{
		case CAMERA_FORWARD: position += front * cameraVelocity; break;
		case CAMERA_BACKWARD: position -= front * cameraVelocity; break;
		case CAMERA_RIGHT: position += right * cameraVelocity; break;
		case CAMERA_LEFT: position -= right * cameraVelocity; break;
	}
}

// Handling mouse movement around x and y axis.
void Camera::MouseHandler(float xDelta, float yDelta, GLboolean constrainPitch = true) {
	yaw += xDelta * sensitivity;
	pitch += yDelta * sensitivity;

	if (constrainPitch) {
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	UpdateCameraVectors();
}

// Handling mouse scroll to make bigger zoom.
void Camera::MouseScrollHandler(float yDelta) {
	zoom -= static_cast<float>(yDelta);
	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 45.0f)
		zoom = 45.0f;
}