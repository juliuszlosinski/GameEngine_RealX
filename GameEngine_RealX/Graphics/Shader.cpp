#include "Shader.h"

// Default constructor.
Shader::Shader()
{
	this->shaderProgram = 0;
}

// Getting the id of shader program.
int Shader::getShaderProgramId() {
	return this->shaderProgram;
}

// Creating vertex shader object based on file.
int Shader::CreateVertexShaderObjectFromFile(std::string const& pathToFile)
{
	return Shader::CreateShaderObjectFromFile(pathToFile, GL_VERTEX_SHADER);
}

// Creating fragment shader object based on file.
int Shader::CreateFragmentShaderObjectFromFile(std::string const& pathToFile)
{
	return Shader::CreateShaderObjectFromFile(pathToFile, GL_FRAGMENT_SHADER);
}

// Creating vertex shader object based on string.
int Shader::CreateVertexShaderObjectFromString(std::string const& data)
{
	return Shader::CreateShaderObjectFromString(data, GL_VERTEX_SHADER);
}

// Creating fragment shader object based on string.
int Shader::CreateFragmentShaderObjectFromString(std::string const& data)
{
	return Shader::CreateShaderObjectFromString(data, GL_FRAGMENT_SHADER);
}

// Creating shader object base on file.
int Shader::CreateShaderObjectFromFile(std::string const& pathToFile, GLenum typeOfShader) {
	unsigned int shaderObject;

	std::string name_of_shader;
	if (typeOfShader == GL_VERTEX_SHADER) {
		name_of_shader = "VERTEX_SHADER";
	}
	else if (typeOfShader == GL_FRAGMENT_SHADER) {
		name_of_shader = "FRAGMENT_SHADER";
	}


	// Creating shader object.
	shaderObject = glCreateShader(typeOfShader);

	// Attach shader source code to the shader object.
	std::string data = ReadTextFromFile(pathToFile);
	const char* fData = data.c_str();
	glShaderSource(shaderObject, 1, &fData, NULL);

	std::cout << "SRC::SHADER::" << name_of_shader << "::COMPILATION_SOURCE\n" << data << "\n";

	// Compiling shader object.
	glCompileShader(shaderObject);

	// Checking if compiling of shader object is successful.
	int success; // Integer to indicate success.
	char infoLog[512]; // Storage container for the error messages.
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderObject, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << name_of_shader << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}
	else {
		std::cout << "SUCCESS::SHADER::" << name_of_shader << "::COMPILATION_SUCCESS\n" << std::endl;
		return shaderObject;
	}
}

// Creating shader object based on string.
int Shader::CreateShaderObjectFromString(std::string const& data, GLenum typeOfShader)
{
	unsigned int shaderObject;

	// Creating shader object.
	shaderObject = glCreateShader(typeOfShader);

	// Attach shader source code to the shader object.
	const char* fData = data.c_str();
	glShaderSource(shaderObject, 1, &fData, NULL);

	std::cout << "SRC::SHADER::" << typeOfShader << "::COMPILATION_SOURCE\n" << data << "\n";

	// Compiling shader object.
	glCompileShader(shaderObject);

	// Checking if compiling of shader object is successful.
	int success; // Integer to indicate success.
	char infoLog[512]; // Storage container for the error messages.
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderObject, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << typeOfShader << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}
	else {
		std::cout << "SUCCESS::SHADER::" << typeOfShader << "::COMPILATION_SUCCESS\n" << std::endl;
		return shaderObject;
	}
}


// Set float uniform.
void Shader::setFloat(std::string const& uniformName, float value) {
	glUniform1f(getUniformLocation(uniformName), value);
}
// Set int uniform.
void Shader::setInt(std::string const& uniformName, int value) {
	glUniform1i(getUniformLocation(uniformName), value);
}

// Set bool uniform.
void Shader::setBool(std::string const& uniformName, bool value) {
	glUniform1i(getUniformLocation(uniformName), static_cast<int>(value));
}

// Get uniform location.
int Shader::getUniformLocation(std::string const& nameOfUniform) {
	return glGetUniformLocation(this->shaderProgram, nameOfUniform.c_str());
}

// Start using program.
void Shader::UseProgram() {
	glUseProgram(this->shaderProgram);
}

// Stop using program.
void Shader::StopUsingProgram() {
	glUseProgram(0);
}

// Set mat4 uniform value.
void Shader::setMat4(std::string const& uniformName, glm::mat4 const& value) {
	glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(value));

}

// Set vector 3 uniform value.
void Shader::setVec3(std::string const& uniformName, glm::vec3 const& value) {
	glUniform3fv(getUniformLocation(uniformName), 1, glm::value_ptr(value));
}

// Creating shader program based on files.
void Shader::CreateFromFiles(std::string const& pathToVertexShader, std::string const& pathToFragmentShader)
{
	unsigned int vertexShaderObject = Shader::CreateVertexShaderObjectFromFile(pathToVertexShader);
	unsigned int fragmentShaderObject = Shader::CreateFragmentShaderObjectFromFile(pathToFragmentShader);
	CreateFromShaderObjects(vertexShaderObject, fragmentShaderObject);
}

// Creating shader program based on strings.
void Shader::CreateFromStrings(std::string const& vertexShaderCode, std::string const& fragmentShaderCode)
{
	unsigned int vertexShaderObject = Shader::CreateVertexShaderObjectFromString(vertexShaderCode);
	unsigned int fragmentShaderObject = Shader::CreateFragmentShaderObjectFromString(fragmentShaderCode);
	CreateFromShaderObjects(vertexShaderObject, fragmentShaderObject);
}

// Create shader program by using shader objects.
void Shader::CreateFromShaderObjects(int vertexShaderObject, int fragmentShaderObject) {

	// Creating empty program getting the ID reference to the newly created program object.
	this->shaderProgram = glCreateProgram();

	// Attaching shaders.
	glAttachShader(this->shaderProgram, vertexShaderObject);
	glAttachShader(this->shaderProgram, fragmentShaderObject);
	glLinkProgram(this->shaderProgram);

	// Checking for failing.
	int success;
	char infoLog[512];
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::LINKING_SHADERS::" << this->shaderProgram << "::LINKING_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "SUCCESS::LINKING_SHADERS::" << this->shaderProgram << "::LINKING_SUCCESS" << std::endl;
	}

	// Deleting shader objects.
	glDeleteShader(vertexShaderObject);
	glDeleteShader(fragmentShaderObject);
}