#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLEW_STATIC
#include "glew.h"
#include <vector>
#include <string>


// ENUMARATIONS FOR CAMERA MOVEMENT.
enum CameraMovement {
	CAMERA_FORWARD,
	CAMERA_BACKWARD,
	CAMERA_LEFT,
	CAMERA_RIGHT
};

// DEFAULT CAMERA VALUES
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.75f;
const float SENSITIVITY = 0.5f;
const float ZOOM = 45.0f;

/*
	Camera representation in shader:
	
	struct Camera
	{
		vec3 position;
	};

*/

class Camera
{
	glm::vec3 position;		 // Vector that points to camera's position.
	glm::vec3 front;		 // Vector that points forward from camera.
	glm::vec3 up;			 // Vector that points to up from camera.
	glm::vec3 right;		 // Vector that points to right from camera.
	glm::vec3 worldUp;		 // Vector that points to up according to world.
	glm::vec3 direction;	 // Vector that tells about camera's direction.
	float yaw;				 // Angle around y axis.
	float pitch;			 // Angle arount x axis.
	float zoom;				 // Zoom of camera.
	float movementSpeed;	 // Speed of camera movement.
	float sensitivity;		 // Senstivity of mouse.
		
	float fieldOfView;		 // FOV - field of view.	
	float distanceOfViewing; // Distance of rendering.
	float aspectRatio;		 // Aspect ratio.

	// Calculating the new camera vectors.
	void UpdateCameraVectors();

public:
	// Default constructor.
	Camera();

	// Custom constructor that takes vector as input.
	Camera(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch,
												  float fieldOfView, float distanceOfViewing, float aspectRatio);

	// Custom constructor that float data as input.
	Camera(float posX, float posY, float posZ, float worldUpX, float worldUpY, float worldUpZ, float yaw, float pitch,
															   float fieldOfView, float distanceOfViewing, float aspectRatio);

	// Setting up camera position.
	void setPosition(const glm::vec3& position)
	{
		this->position = position;
	}

	// Returning reference to the yaw angle.
	float& getRefYawAngle()
	{
		return yaw;
	}

	// Returning reference to the pith angle.
	float& getRefPitchAngle()
	{
		return pitch;
	}

	// Getting projection matrix.
	glm::mat4 getProjectionMatrix();

	// Get camera view matrix;
	glm::mat4 getViewMatrix();

	// Get camera position.
	glm::vec3 getPosition()
	{
		return position;
	}

	glm::vec3* getRefPosition()
	{
		return &position;
	}

	glm::vec3 getDirection()
	{
		return direction;
	}

	void setAspectRatio(float aspectRatio)
	{
		this->aspectRatio = aspectRatio;
	}

	// Handling keyboard to move camera in directions.
	void KeyBoardHandler(CameraMovement direction, float deltaTime);

	// Handling mouse movement around x and y axis.
	void MouseHandler(float xDelta, float yDelta, GLboolean constrainPitch);

	// Handling mouse scroll to make bigger zoom.
	void MouseScrollHandler(float yDelta);
};
#endif