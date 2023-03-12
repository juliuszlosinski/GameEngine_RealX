#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Light.h"
#include <string>

/*
	Direction lighting is a light (Phong Lighting Model: Ambient + Diffuse + Specular)
	that doesn't have position but only direction. It's like a sun!

	Shader program representation of Directional Light:

	struct Light
	{
		vec3 colour;
		float ambientIntensity;
		float diffuseIntensity;
	};

	struct DirectionalLight
	{
		Light light;
		vec3 direction;
	}
*/

class DirectionalLight : public Light
{
	glm::vec3 direction;	// Direction of light.
public:

	// Getting direction of light.
	glm::vec3 getDirection();

	// Setting up direction by using vector.
	void setDirection(glm::vec3 direction);

	// Setting up direction by using floats.
	void setDirection(GLfloat xDirection, GLfloat yDirection, GLfloat zDirection);

	// Getting reference to the direction vector.
	glm::vec3& getRefDirection()
	{
		return direction;
	}

	// Default constructor.
	DirectionalLight();

	// Customized constructor that takes float values.
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
					 GLfloat ambientIntensity, GLfloat diffuseIntensity,
					 GLfloat xDirection, GLfloat yDirection, GLfloat zDirection);

	// Customized constructor that takes vectors values.
	DirectionalLight(glm::vec3 colour,
					 GLfloat ambientIntensity, GLfloat diffuseIntensity,
					 glm::vec3 direction);
};
#endif