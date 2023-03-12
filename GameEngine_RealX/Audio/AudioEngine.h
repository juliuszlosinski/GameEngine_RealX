#ifndef SOUND3D_H
#define SOUND3D_H

#include "irrKlang.h"
#include <string>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>

class AudioEngine
{
	irrklang::ISoundEngine*								  soundEngine;	// Sound engine.
	glm::vec3										   cameraPosition;	// Position of camera.
	glm::vec3										  cameraDirection;	// Direction of camera.

public:
	// Default constructor.
	AudioEngine()
	{
		soundEngine     = irrklang::createIrrKlangDevice();
		cameraPosition  = glm::vec3(0.0f, 0.0f, 0.0f);
		cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	// Updating components like camera position.
	void Update(glm::vec3 cameraPositon, glm::vec3 cameraDirection)
	{
		this->cameraPosition  =  cameraPosition;
		this->cameraDirection = glm::normalize(cameraDirection);

		irrklang::vec3df convertedCameraPosition = irrklang::vec3df(this->cameraPosition.x, this->cameraPosition.y, this->cameraPosition.z);
		irrklang::vec3df convertedCameraDirection = irrklang::vec3df(this->cameraDirection.x, this->cameraDirection.y, this->cameraDirection.z);

		soundEngine->setListenerPosition(convertedCameraPosition, convertedCameraDirection);
	}

	// Getting pointer to the created sound 3dD.
	irrklang::ISound* createSound3D(const std::string& pathToMusic, glm::vec3 position)
	{
		irrklang::ISound* sound3D = soundEngine->play3D(pathToMusic.c_str(), irrklang::vec3df(position.x, position.y, position.z), false, true);
		return sound3D;
	}
};

#endif