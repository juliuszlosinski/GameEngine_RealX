#ifndef MATERIAL_H
#define MATERIAL_H

#define GLEW_STATIC
#include "glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material
{
	GLfloat m_SpecularIntensity; // Factor of specular intensity.
	GLfloat m_Shininess;		   // Big = Metal or Small = Wood.

public:

	// Default constructor.
	Material()
	{
		m_SpecularIntensity = 0.5f;
		m_Shininess = 32.0f;
	}

	// Customized constructor.
	Material(GLfloat specularIntensity, GLfloat shininess)
	{
		m_SpecularIntensity = specularIntensity;
		m_Shininess = shininess;
	}

	// Getting value of specular intensity.
	GLfloat getSpecularIntensity()
	{
		return m_SpecularIntensity;
	}

	// Getting reference to the specular intensity.
	GLfloat& getRefSpecularIntensity()
	{
		return m_SpecularIntensity;
	}

	// Getting value of shininess.
	GLfloat getShininess()
	{
		return m_Shininess;
	}

	// Getting reference to the shininess.
	GLfloat& getRefShininess()
	{
		return m_Shininess;
	}
};

#endif