#include "Camera.h"

// Update camera vectors.
void Camera::UpdateCameraVectors() {
	glm::vec3 tmpFront;
	tmpFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	tmpFront.y = sin(glm::radians(pitch));
	tmpFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(tmpFront);
	right = glm::normalize(glm::cross(front, worldUp));
	this->direction = front;
	up = glm::normalize(glm::cross(right, front));
}

// Custom constructor that takes vector as input.
Camera::Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
		       glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f),
	           float yaw = YAW, float pitch = PITCH, 
			  float fieldOfView = 45, float distanceOfViewing = 100.0f, float aspectRatio = 1)
{
	this->position = position;
	this->worldUp = worldUp;
	this->yaw = YAW;
	this->pitch = PITCH;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	movementSpeed = SPEED;
	sensitivity = SENSITIVITY;
	zoom = ZOOM;
	this->fieldOfView = fieldOfView;
	this->distanceOfViewing = distanceOfViewing;
	this->aspectRatio = aspectRatio;
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
	fieldOfView = 45.0f;
}

// Custom constructor that float data as input.
Camera::Camera(float posX, float posY, float posZ,
			   float worldUpX, float worldUpY, float worldUpZ,
	           float yaw, float pitch, float fieldOfView = 45, float distanceOfViewing = 100.0f, float aspectRatio = 1)
{
	position = glm::vec3(posX, posY, posZ);
	worldUp = glm::vec3(worldUpX, worldUpY, worldUpZ);
	this->yaw = yaw;
	this->pitch = pitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	movementSpeed = SPEED;
	sensitivity = SENSITIVITY;
	zoom = ZOOM;
	this->fieldOfView = fieldOfView;
	this->distanceOfViewing = distanceOfViewing;
	this->aspectRatio = aspectRatio;
}

// Get camera view matrix;
glm::mat4 Camera:: getViewMatrix() 
{
	UpdateCameraVectors();
	return glm::lookAt(position, position + front, up);
}

// Handling keyboard to move camera in directions.
void Camera::KeyBoardHandler(CameraMovement direction, float deltaTime) 
{
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
void Camera::MouseHandler(float xDelta, float yDelta, GLboolean constrainPitch = true)
{
	xDelta *= sensitivity;
	yDelta *= sensitivity;
	
	yaw += xDelta;
	pitch += yDelta;

	if (constrainPitch) 
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	UpdateCameraVectors();
}

// Getting projection matrix.
glm::mat4 Camera::getProjectionMatrix()
{
	return glm::perspective(glm::radians(fieldOfView), aspectRatio, 0.1f, distanceOfViewing);
}

// Handling mouse scroll to make bigger zoom.
void Camera::MouseScrollHandler(float yDelta)
{
	zoom -= static_cast<float>(yDelta);
	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 45.0f)
		zoom = 45.0f;
}