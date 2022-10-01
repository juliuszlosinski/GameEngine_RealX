#ifndef WINDOW_H
#define WINDOW_H
#include "Window.h"
#endif 

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#include "FileHandler.h"
#endif

#ifndef GLEW_H
#define GLEW_STATIC
#include "glew.h"
#endif 

#ifndef GLFW_H
#define GLFW_H
#include "glfw3.h"
#endif

#ifndef STRING_H
#define STRING_H
#include <string>
#endif

#ifndef FSTREAM_H
#define FSTREAM_H
#include <fstream>
#endif

#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif

#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

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