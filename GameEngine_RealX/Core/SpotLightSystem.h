#ifndef SPOT_LIGHT_SYSTEM
#define SPOT_LIGHT_SYSTEM

#include "Coordinator.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Lights/SpotLight.h"
#include "../RealX/RealXEngine.h"

#define DEBUG

struct SpotLightSystem :public System
{
	void Update(EntityComponentSystem* pCoordinator, Shader* pShader)
	{
		// Getting number of spot lights.
		int numberOfSpotLights = m_Entities.size();

#ifdef  DEBUG
		std::cout << "Number of spot lights: " << numberOfSpotLights << std::endl;
#endif

		// Passing number of uniform spot lights.
		pShader->setInt("passedNumberOfSpotLights", numberOfSpotLights);

		// Iterating through entities and setting current spot light.
		int i = 0;
		for (auto const& entity : m_Entities)
		{
			// Getting reference to the spot light component.
			auto& spotLight = pCoordinator->GetComponent<SpotLightComponent>(entity);

			// Getting reference to the transform compoennt.
			auto& transform = pCoordinator->GetComponent<TransformComponent>(entity);

			// Saving spot light position to be the transform position.
			spotLight.light.getRefPosition() = transform.position;

			// Creating uniform name based on current light index.
			std::string currentUniformName = "spotLights[" + std::to_string(i) + "]";

			// Setting up current point light in the shader.
			pShader->setSpotLight(currentUniformName, &spotLight.light);

			// Incremeting index.
			i++;
		}
	}
};
#endif