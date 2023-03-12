#ifndef SKYBOX_RENDERING_SYSTEM
#define SKYBOX_RENDERING_SYSTEM

#include "Coordinator.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Renderer3D.h"
#include "../RealX/RealXEngine.h"

#include "../Graphics/GraphicsEngine.h"

struct SkyboxRenderingSystem :public System
{
public:

	void Update(Window* pWindow,GraphicsEngine* pGraphicsEngine, EntityComponentSystem* pCoordinator, Shader* pSkyboxShader, Camera* pCamera)
	{
		// Disabling depth mask.
		pWindow->DisableDepthMask();

		// Starting using program.
		pSkyboxShader->UseProgram();

		// Sending camera data to the shader program.
		pSkyboxShader->setCamera("camera", pCamera);

		// Iterating through entities and drawing models.
		for (auto const& entity : m_Entities)
		{
			// Getting reference to the transfrom component.
			auto& transform = pCoordinator->GetComponent<TransformComponent>(entity);

			// Getting reference to the skybox component.
			auto& skybox = pCoordinator->GetComponent<SkyboxComponent>(entity);

			// Loading and using texture.
			TexturesResourcesLoader::LoadCubemap
			   (skybox.pathToRightTexture, skybox.pathToLeftTexture,
				skybox.pathToTopTexture, skybox.pathToBottomTexture,
				skybox.pathToBackTexture, skybox.pathToFrontTexture)->UseTexture();

			// Getting reference to the transform component.
			pGraphicsEngine->RenderCubeWithOutTexture(*pSkyboxShader, transform.position, transform.rotation, transform.scale);
		}

		// Enabling depth mask.
		pWindow->EnableDepthMask();

		// Stop using the program.
		pSkyboxShader->StopUsingProgram();
	}
};

#endif