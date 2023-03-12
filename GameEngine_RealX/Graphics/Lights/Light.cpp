#include "Light.h"

//Default constructor:
Light::Light()
{
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	diffuseIntensity = 0.0f;
}

// Customized constructor that takes floats as input.
Light::Light(GLfloat red, GLfloat green, GLfloat blue,
		     GLfloat ambientIntesinty, GLfloat diffuseIntensity)
{
	colour = glm::vec3(red, green, blue);
	this->ambientIntensity = ambientIntesinty;
	this->diffuseIntensity = diffuseIntensity;
}

// Getting current colour of light.
glm::vec3 Light::getColour()
{
	return colour;
}

// Getting value of ambient intensity.
GLfloat Light::getAmbientIntensity()
{
	return ambientIntensity;
}

// Getting value of diffuse intensity.
GLfloat Light::getDiffuseIntensity()
{
	return diffuseIntensity;
}

// Setting colour by using vector.
void Light::setColour(glm::vec3 colour)
{
	this->colour = colour;
}

// Setting colour by using float as input.
void Light::setColour(GLfloat red, GLfloat green, GLfloat blue)
{
	this->colour = glm::vec3(red, green, blue);
}

// Setting up the ambient intensity.
void Light::setAmbientIntensity(GLfloat ambientIntensity)
{
	this->ambientIntensity = ambientIntensity;
}

// Setting up the diffuse intensity.
void Light::setDiffuseIntenisty(GLfloat diffuseIntensity)
{
	this->diffuseIntensity = diffuseIntensity;
}

// Customized constructor that takes vectors as input.
Light::Light(glm::vec3 colour, GLfloat ambientIntensity, GLfloat diffuseIntensity)
{
	this->colour = colour;
	this->ambientIntensity = ambientIntensity;
	this->diffuseIntensity = diffuseIntensity;
}
