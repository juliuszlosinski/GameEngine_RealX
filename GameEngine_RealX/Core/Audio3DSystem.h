#ifndef AUDIO3D_SYSTEM_H
#define AUDIO3D_SYSTEM_H

#include "Coordinator.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Renderer3D.h"
#include "../RealX/RealXEngine.h"
#include "../Audio/AudioEngine.h"

struct Audio3DSystem :public System
{
	// Default constructor.
	Audio3DSystem()
	{
		
	}

	void Update(EntityComponentSystem* pCoordinator,AudioEngine* pAudioEngine, Camera* pCamera)
	{
		// Iterating through entities setting up music.
		for (auto const& entity : m_Entities)
		{
			// Getting reference to the transform component.
			auto& transform = pCoordinator->GetComponent<TransformComponent>(entity);

			// Getting reference to the audo component.
			auto& audio = pCoordinator->GetComponent<Audio3DComponent>(entity);

			// Checking if there is audio sound.
			if (!audio.updated)
			{
				audio.updated = true;
				if (audio.sound != nullptr)
				{
					audio.sound->stop();
					audio.sound->drop();
				}
				audio.sound = pAudioEngine->createSound3D(audio.pathToFile, transform.position);
				std::cout << "AUDIO_SYSTEM::Updated sound component!\n";
			}

			// Updating position of the audio.
			if (audio.sound != nullptr) 
			{
				audio.sound->setPosition(irrklang::vec3df(transform.position.x, transform.position.y, transform.position.z));
				std::cout << "AUDIO_SYSTEM::Camera's position updated in audio system!\n";
			}

			// Updating sound engine.
			pAudioEngine->Update(pCamera->getPosition(), pCamera->getDirection());
		}
	}
};
#endif
