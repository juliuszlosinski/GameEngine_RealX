#ifndef RENDERER_3D
#define RENDERER_3D

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string>

#include "MeshesResourcesLoader.h"
#include "TexturesResourcesLoader.h"
#include "Shader.h"

class Renderer3D
{
private:
	// Getting Matrix transformation by using vectors (translation, rotation and scale).
	glm::mat4 GetMatrixTransformation(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
	{
		glm::mat4 model(1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, translation);
		model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, scale);
		return model;
	}

public:
	// Drawing model.
	void DrawModel(Shader& shader, const std::string& path,const glm::vec3& translation,const glm::vec3& rotation,const glm::vec3& scale);

	// Drawing a 3D cube with texture.
	void DrawCubeWithTexture(Shader& shader, const std::string& path, const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);

	// Drawing a 3D cube without texture.
	void DrawCubeWithOutTexture(Shader& shader, const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);
};
#endif

