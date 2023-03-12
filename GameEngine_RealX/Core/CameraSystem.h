#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#include "Coordinator.h"
#include "System.h"
#include "CoreDataECS.h"
#include "Components.h"

class CameraSystem : public System
{
public:
	Camera* getMainCameraFromEntitiesWithCameraComponent(EntityComponentSystem& g_Coordinator)
	{
		// Iterating through all cameras in the system.
		for (auto const& entity : m_Entities)
		{
			// Getting reference to the camera component.
			auto& refCamera = g_Coordinator.GetComponent<CameraComponent>(entity);

			// Getting reference to the transform component.
			auto& refTransform = g_Coordinator.GetComponent<TransformComponent>(entity);

			// Setting up camera position according to the transform.
			//refCamera.camera.setPosition(refTransform.position);

			// Checking if this is a main camera.
			if (refCamera.mainCamera)
			{
				// Returning reference to the camera.
				return &refCamera.camera;
			}
		}
	}
};
#endif