#ifndef SHADER_H
#define SHADER_H


#include "../Utils/FileHandler.h"
#define GLEW_STATIC
#include "glew.h"
#include "glfw3.h"

#include <string>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"
#include "Lights/SpotLight.h"
#include "Material.h"

class Shader
{
private:
	int shaderProgram; // Id program.
public:

	// Default constructor;
	Shader();

	// Getting the id of shader program.
	int getShaderProgramId();

	// Start using shader program.
	void UseProgram();

	// Stop using program.
	void StopUsingProgram();

	// Create shader program from shader objects.
	void CreateFromShaderObjects(int vertexShaderObject, int fragmentShaderObject);

	// Create shader program from files.
	void CreateFromFiles(std::string const& pathToVertexShader, std::string const& pathToFragmentShader);

	// Create shader program from strings.
	void CreateFromStrings(std::string const& vertexShaderCode, std::string const& fragmentShaderCode);

	// Get uniform location.
	int getUniformLocation(std::string const& nameOfUniform);

	// Set float uniform.
	void setFloat(std::string const& uniformName, float value);

	// Set int uniform.
	void setInt(std::string const& uniformName, int value);

	// Set bool uniform.
	void setBool(std::string const& uniformName, bool value);

	// Set mat4 uniform value.
	void setMat4(std::string const& uniformName, glm::mat4 const& value);

	// Set vector 3 uniform value.
	void setVec3(std::string const& uniformName, glm::vec3 const& value);

	/*
		struct Material
		{
			float shininess;
			float specularIntensity;
		};
	*/

	// Setting up material in shader.
	void setMaterial(std::string const& uniformName, Material* material)
	{
		setFloat(uniformName + ".shininess", material->getShininess());
		setFloat(uniformName + ".specularIntensity", material->getSpecularIntensity());
	}

	// Setting camera in shader.
	void setCamera(std::string const& uniformName, Camera* camera)
	{
		setVec3(uniformName + ".position", camera->getPosition());
		setMat4("view",	camera->getViewMatrix());
		setMat4("projection", camera->getProjectionMatrix());
	}
	
	/*
	
	struct Light
	{
		vec3 colour;				// Colour of the light.
		float ambientIntensity;		// Ambient intensity of the light.
		float diffuseIntensity;		// Diffuse intensity of the light.
	}

	struct DirectionalLight
	{
		Light light;				// Base light.	
		vec3 direction;				// Direction of emiting light.
	}

	*/

	// Setting up directional light int shader.
	void setDirectionalLight(std::string const& uniformName, DirectionalLight* light)
	{
		setVec3(uniformName + ".light.colour", light->getColour());
		setFloat(uniformName + ".light.ambientIntensity", light->getAmbientIntensity());
		setFloat(uniformName + ".light.diffuseIntensity", light->getDiffuseIntensity());
		setVec3(uniformName + ".direction", light->getDirection());
	}

	/*
		struct Light
		{
			vec3 colour;
			float ambientIntensity;
			float diffuseIntensity;
		};

		struct PointLight
		{
			Light light;

			vec3 position;
			float constantFactor;
			float linearFactor;
			float exponentFactor;
		};
	*/

	// Setting up point light in shader.
	void setPointLight(std::string const& uniformName, PointLight* light)
	{
		setVec3(uniformName + ".light.colour", light->getColour());
		setFloat(uniformName + ".light.ambientIntensity", light->getAmbientIntensity());
		setFloat(uniformName + ".light.diffuseIntensity", light->getDiffuseIntensity());
		
		setVec3(uniformName + ".position", light->getPosition());
		setFloat(uniformName + ".constantFactor", light->getConstantFactor());
		setFloat(uniformName + ".linearFactor", light->getLinearFactor());
		setFloat(uniformName + ".exponentFactor", light->getExponentFactor());
	}

	/*
		struct Light
		{
			vec3 colour;
			float ambientIntensity;
			float diffuseIntensity;
		}; 

		struct PointLight
		{
			Light light;
	
			vec3 position;
			float constant;
			float linear;
			float exponent;
		};

		struct SpotLight
		{
			PointLight light;
			vec3 direction;
			float edge;
		};
	
	*/

	// Setting up spot light in the shader.
	void setSpotLight(std::string const& uniformName, SpotLight* light)
	{
		setVec3(uniformName + ".direction", light->getDirection());
		setFloat(uniformName + ".edge", light->getEdge());
		setPointLight(uniformName + ".light", light);
	}

	// Creating vertex shader object based on file.
	static int CreateVertexShaderObjectFromFile(std::string const& pathToFile);

	// Creating fragment shader object based on file.
	static int CreateFragmentShaderObjectFromFile(std::string const& pathToFile);

	// Creating vertex shader object based on string.
	static int CreateVertexShaderObjectFromString(std::string const& data);

	// Creating fragment shader object based on string.
	static int CreateFragmentShaderObjectFromString(std::string const& data);

	// Creating shader object based on file.
	static int CreateShaderObjectFromFile(std::string const& pathToFile, GLenum typeOfShader);

	// Creating shader object based on string.
	static int CreateShaderObjectFromString(std::string const& data, GLenum typeOfShader);
};
#endif