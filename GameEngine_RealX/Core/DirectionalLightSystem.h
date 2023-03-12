#ifndef DIRECTIONAL_LIGHT_SYSTEM
#define DIRECTIONAL_LIGHT_SYSTEM

#include "Coordinator.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Lights/DirectionalLight.h"
#include "../RealX/RealXEngine.h"

#define DEBUG

struct DirectionalLightSystem :public System
{
	void Update(EntityComponentSystem* pCoordinator, Shader* pShader)
	{
		// Getting number of directional lights.
		int numberOfDirectionalLights = m_Entities.size();

#ifdef  DEBUG
		std::cout << "Number of directional lights: " << numberOfDirectionalLights << std::endl;
#endif

		// Passing number of uniform directional lights.
		pShader->setInt("passedNumberOfDirectionalLights", numberOfDirectionalLights);

		// Iterating through entities and setting current directional light.
		int i = 0;
		for (auto const& entity : m_Entities)
		{
			// Getting reference to the directional light component.
			auto& directionalLight = pCoordinator->GetComponent<DirectionalLightComponent>(entity);

			// Creating uniform name based on current light index.
			std::string currentUniformName = "directionalLights[" + std::to_string(i) + "]";

			// Setting up current directional light by passing to current uniform name a directional light.
			pShader->setDirectionalLight(currentUniformName, &directionalLight.light);

			// Incremeting index.
			i++;
		}
	} 
};

#endif