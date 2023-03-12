#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "PointLight.h"

class SpotLight : public PointLight
{
	glm::vec3 direction;			// Direction of light.
	GLfloat edge;					// Edge.
	GLfloat processedEdge;		// Processed edge.
	bool isOn;					// If light is on.
public:
	// Default constructor.
	SpotLight() 
	{
		direction = glm::vec3(0.0f, -1.0f, 0.0f);
		edge = 0.0f;
		processedEdge = cos(glm::radians(edge));
		isOn = true;
	}

	// Customized constructor.
	SpotLight(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat xDir, GLfloat yDir, GLfloat zDir,
		GLfloat constant, GLfloat linear, GLfloat exponent,
		GLfloat edge) : PointLight(red, green, blue, aIntensity, dIntensity, xPos, yPos, zPos, constant, linear, exponent)
	{
		direction = glm::normalize(glm::vec3(xDir, yDir, zDir));
		this->edge = edge;
		processedEdge = cos(glm::radians(edge));
	}

	// Getting direction.
	glm::vec3 getDirection()
	{
		return direction;
	}

	// Getting reference to the direction.
	glm::vec3& getRefDirection()
	{
		return direction;
	}

	// Getting edge.
	GLfloat getEdge()
	{
		return edge;
	}

	// Getting reference to the edge.
	GLfloat& getRefEdge()
	{
		return edge;
	}

	// Getting processed edge.
	GLfloat getProcessedEdge()
	{
		return processedEdge;
	}

	// Getting reference to the processed edge.
	GLfloat& getRefProcessedEdge()
	{
		return processedEdge;
	}

	// Getting is on flag.
	bool getIsOn()
	{
		return isOn;
	}

	// Getting reference to the is on flag.
	bool& getRefIsOn()
	{
		return isOn;
	}

	// Setting up flash by passing position and direction vectors.
	void SetFlash(glm::vec3 position, glm::vec3 direction)
	{
		this->position = position;
		this->direction = direction;
	}
};
#endif

