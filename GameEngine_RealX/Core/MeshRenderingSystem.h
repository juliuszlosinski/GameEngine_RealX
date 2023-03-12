#ifndef MESH_RENDERING_SYSTEM
#define MESH_RENDERING_SYSTEM

#include "Coordinator.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Renderer3D.h"
#include "../Graphics/Renderer2D.h"
#include "../RealX/RealXEngine.h"
#include "../Graphics/GraphicsEngine.h"

struct MeshRenderingSystem :public System
{
	void Update(EntityComponentSystem* pCoordinator,GraphicsEngine* pGraphicEngine, Shader* pShader)
	{
		// Iterating through entities and drawing models.
		for (auto const& entity : m_Entities)
		{
			// Getting reference to the transform component.
			auto& transform = pCoordinator->GetComponent<TransformComponent>(entity);

			// Getting reference to the mesh renderer component.
			auto& meshRenderer = pCoordinator->GetComponent<MeshRendererComponent>(entity);
			
			// Getting reference to the material component.
			auto& material = pCoordinator->GetComponent<MaterialComponent>(entity);

			// Setting up a material in shader.
			pShader->setMaterial("material", &material.material);

			// Drawing the model on the frame buffer.
			std::string meshType(meshRenderer.meshType);
			if (meshType == "Cube")
			{
				pGraphicEngine->RenderCubeWithTexture(*pShader, meshRenderer.pathToTexture, transform.position, transform.rotation, transform.scale);
			}
			else if (meshType == "Triangle")
			{
				pGraphicEngine->RenderTriangleMeshWithTexture(*pShader, meshRenderer.pathToTexture, transform.position, transform.rotation, transform.scale);
			}
			else if (meshType == "Rectangle")
			{
				pGraphicEngine->RenderRectangleMeshWithTexture(*pShader, meshRenderer.pathToTexture, transform.position, transform.rotation, transform.scale);
			}
			else
			{
				pGraphicEngine->RenderCubeWithTexture(*pShader, meshRenderer.pathToTexture, transform.position, transform.rotation, transform.scale);
			}
		}
	}
};
#endif