#ifndef RENDERING_SYSTEM_H
#define RENDERING_SYSTEM_H

#include "Coordinator.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Renderer3D.h"
#include "../Graphics/MeshesResourcesLoader.h"
#include "../RealX/RealXEngine.h"
#include "../Graphics/GraphicsEngine.h"


struct ModelRenderingSystem :public System
{
	void Update(EntityComponentSystem* pCoordinator, GraphicsEngine* pGraphicsEngine, Shader* pShader)
	{
		// Iterating through entities and drawing models.
		for (auto const& entity : m_Entities)
		{
			// Getting reference to the transform component.
			auto& transform = pCoordinator->GetComponent<TransformComponent>(entity);

			// Getting reference to the model renderer component.
			auto& modelRenderer = pCoordinator->GetComponent<ModelRendererComponent>(entity);

			// Getting reference to the material component.
			auto& material = pCoordinator->GetComponent<MaterialComponent>(entity);

			// Setting up material in shader.
			pShader->setMaterial("material", &material.material);

			// Drawing the model on the frame buffer.
			pGraphicsEngine->RenderModel(*pShader, modelRenderer.pathToModel, transform.position, transform.rotation, transform.scale);
		}
	}
};
#endif
