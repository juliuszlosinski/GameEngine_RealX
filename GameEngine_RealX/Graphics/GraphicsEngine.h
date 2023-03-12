#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include "Renderer2D.h"
#include "Renderer3D.h"

class GraphicsEngine
{
private:
	Renderer2D* m_pRenderer2D;
	Renderer3D* m_pRenderer3D;

public:
	GraphicsEngine()
	{
		m_pRenderer2D = new Renderer2D();
		m_pRenderer3D = new Renderer3D();
	}

	void RenderRectangleMeshWithTexture(Shader& shader, const std::string& pathToTexture,
		const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
	{

		m_pRenderer2D->RenderRectangleMeshWithTexture(shader, pathToTexture, translation, rotation, scale);
	}

	void RenderTriangleMeshWithTexture(Shader& shader, const std::string& pathToTexture,
		const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
	{
		m_pRenderer2D->RenderRectangleMeshWithTexture(shader, pathToTexture, translation, rotation, scale);
	}

	void RenderModel(Shader& shader, const std::string& pathToModel,
		const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
	{
		m_pRenderer3D->DrawModel(shader, pathToModel, translation, rotation, scale);
	}

	void RenderCubeWithTexture(Shader& shader, const std::string& pathToTexture,
		const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
	{
		m_pRenderer3D->DrawCubeWithTexture(shader, pathToTexture, translation, rotation, scale);
	}

	void RenderCubeWithOutTexture(Shader& shader,
		const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
	{
		m_pRenderer3D->DrawCubeWithOutTexture(shader, translation, rotation, scale);
	}
};
#endif