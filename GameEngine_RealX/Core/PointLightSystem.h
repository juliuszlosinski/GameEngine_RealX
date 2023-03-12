#ifndef POINT_LIGHT_SYSTEM
#define POINT_LIGHT_SYSTEM

#include "Coordinator.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Lights/PointLight.h"
#include "../RealX/RealXEngine.h"

#define DEBUG

struct PointLightSystem :public System
{
	void Update(EntityComponentSystem* pCoordinator, Shader* pShader)
	{
		// Getting number of point lights.
		int numberOfPointLights = m_Entities.size();

#ifdef  DEBUG
		std::cout << "Number of point lights: " << numberOfPointLights << std::endl;
#endif

		// Passing number of uniform point lights.
		pShader->setInt("passedNumberOfPointLights", numberOfPointLights);

		// Iterating through entities and setting current point light.
		int i = 0;
		for (auto const& entity : m_Entities)
		{
			// Getting reference to the point light component.
			auto& pointLight = pCoordinator->GetComponent<PointLightComponent>(entity);

			// Getting reference to the transform component.
			auto& transform = pCoordinator->GetComponent<TransformComponent>(entity);
			
			// Setting point light position to be according to transform component.
			pointLight.light.getRefPosition() = transform.position;

			// Creating uniform name based on current light index.
			std::string currentUniformName = "pointLights[" + std::to_string(i) + "]";

			// Setting up current point light in the shader.
			pShader->setPointLight(currentUniformName, &pointLight.light);

			// Incremeting index.
			i++;
		}
	}
};

#endif