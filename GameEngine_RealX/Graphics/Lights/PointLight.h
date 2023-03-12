#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Light.h"

/*
	struct Light
	{
		vec3 colour;
		float ambientIntensity;
		float diffuseIntensity;
	};

	struct PointLight
	{
		Light base;
		vec3 position;
		float constantFactor;
		float linearFactor;
		float exponentFactor;
	};
*/

class PointLight : public Light
{
protected:
	glm::vec3 position;		// Position of the light.
	
	// Formula of damping:
	// 1/(ax^2 + bx + c)
	// Damping factors:
	GLfloat constant;	// c
	GLfloat linear;		// b
	GLfloat exponent;	// a
public:

	// Default constructor.
	PointLight()
	{
		position = glm::vec3(0.0f, 0.0f, 0.0f);
		constant = 1.0f;
		linear = 0.0f;
		exponent = 0.0f;
	}

	// Customized constructor.
	PointLight(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat constant, GLfloat linear, GLfloat exponent) : Light(red, green, blue, aIntensity, dIntensity)
	{
		this->position = glm::vec3(xPos, yPos, zPos);
		this->constant = constant;
		this->linear = linear;
		this->exponent = exponent;
	}

	// Getting position of the point light.
	glm::vec3 getPosition()
	{
		return position;
	}

	// Getting reference to the position of the point light.
	glm::vec3& getRefPosition()
	{
		return position;
	}

	// Getting constant factor.
	GLfloat getConstantFactor()
	{
		return constant;
	}

	// Getting reference to the constant factor.
	GLfloat& getRefConstantFactor()
	{
		return constant;
	}

	// Getting linear factor.
	GLfloat getLinearFactor()
	{
		return linear;
	}

	// Getting reference to the linear factor.
	GLfloat& getRefLinearFactor()
	{
		return linear;
	}

	// Getting exponent factor.
	GLfloat getExponentFactor()
	{
		return exponent;
	}

	// Getting reference to the exponent factor.
	GLfloat& getRefExponentFactor()
	{
		return exponent;
	}
};

#endif
