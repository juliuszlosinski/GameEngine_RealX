#include "Renderer3D.h"

// Drawing a model.
void Renderer3D::DrawModel(Shader& shader, const std::string& path, const glm::vec3& translation,const glm::vec3& rotation,const glm::vec3& scale)
{
	// Setting up a model matrix (transformation of model).
	shader.setMat4("model", GetMatrixTransformation(translation, rotation, scale));

	// Loading and rendering model by using current binded shader program and passed uniforms.
	MeshesResourcesLoader::LoadModel(path)->RenderModel();
}

// Drawing a 3D cube.
void Renderer3D::DrawCubeWithTexture(Shader& shader, const std::string& path, const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
{
	// Setting up a model matrix (transformation of cube).
	shader.setMat4("model", GetMatrixTransformation(translation, rotation, scale));

	// Loading and setting up a texture.
	TexturesResourcesLoader::LoadTexture(path)->UseTexture();

	// Loading and rendering cube by using current binded shader program and passed uniforms.
	MeshesResourcesLoader::LoadCubeMesh()->RenderMesh();
}

// Drawing a 3D cube.
void Renderer3D::DrawCubeWithOutTexture(Shader& shader, const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
{
	// Setting up a model matrix (transformation of cube).
	shader.setMat4("model", GetMatrixTransformation(translation, rotation, scale));

	// Loading and rendering cube by using current binded shader program and passed uniforms.
	MeshesResourcesLoader::LoadCubeMesh()->RenderMesh();
}