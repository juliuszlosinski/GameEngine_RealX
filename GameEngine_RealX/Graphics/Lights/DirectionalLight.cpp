#include "DirectionalLight.h"

// Getting direction of light.
glm::vec3 DirectionalLight::getDirection()
{
	return direction;
}

// Setting up direction by using vector.
void DirectionalLight::setDirection(glm::vec3 direction)
{
	this->direction = direction;
}

// Setting up direction by using floats.
void DirectionalLight::setDirection(GLfloat xDirection, GLfloat yDirection, GLfloat zDirection)
{
	this->direction = glm::vec3(xDirection, yDirection, zDirection);
}

// Default constructor.
DirectionalLight::DirectionalLight() : Light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

// Customized constructor that takes float values.
DirectionalLight::DirectionalLight
   (GLfloat red, GLfloat green, GLfloat blue,
	GLfloat ambientIntensity, GLfloat diffuseIntensity,
	GLfloat xDirection, GLfloat yDirection, GLfloat zDirection)
	:Light(red, green, blue, ambientIntensity, diffuseIntensity)
{
	direction = glm::vec3(xDirection, yDirection, zDirection);
}

// Customized constructor that takes vectors values.
DirectionalLight::DirectionalLight
    (glm::vec3 colour,
	GLfloat ambientIntensity, GLfloat diffuseIntensity,
	glm::vec3 direction)
	:Light(colour, ambientIntensity, diffuseIntensity)
{
	this->direction = direction;
}