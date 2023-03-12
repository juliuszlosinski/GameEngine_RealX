#ifndef RENDERER_2D_H
#define RENDERER_2D_H

#include "MeshesResourcesLoader.h"
#include "TexturesResourcesLoader.h"
#include "Shader.h"

class Renderer2D
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
	// Rendering rectangle on the frame buffer by using passed binding "model matrix" in given shader program.
	void RenderRectangleMeshWithTexture(Shader& shader, const std::string& pathToTexture, const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
	{
		// Setting up a model matrix (transformation of rectangle).
		shader.setMat4("model", GetMatrixTransformation(translation, rotation, scale));

		// Loading and setting up a texture.
		TexturesResourcesLoader::LoadTexture(pathToTexture)->UseTexture();

		// Loading and rendering cube by using current binded shader program and passed uniforms.
		MeshesResourcesLoader::LoadRectangleMesh()->RenderMesh();
	}

	// Rendering triangle on the frame buffer by using passed binding "model matrix" in given shader program.
	void RenderTriangleMeshWithTexture(Shader& shader, const std::string& pathToTexture, const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
	{
		// Setting up a model matrix (transformation of triangle).
		shader.setMat4("model", GetMatrixTransformation(translation, rotation, scale));

		// Loading and setting up a texture.
		TexturesResourcesLoader::LoadTexture(pathToTexture)->UseTexture();

		// Loading and rendering cube by using current binded shader program and passed uniforms.
		MeshesResourcesLoader::LoadTriangleMesh()->RenderMesh();
	}
};
#endif