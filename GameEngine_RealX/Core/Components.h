#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "irrKlang.h"
#include <string>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "../Graphics/Camera.h"
#include "../Graphics/MeshTypes.h"
#include "../Graphics/Cubemap.h"
#include "../Graphics/Lights/DirectionalLight.h"
#include "../Graphics/Lights/PointLight.h"
#include "../Graphics/Lights/SpotLight.h"
#include "../Graphics/Material.h"
#include "../Graphics/Model.h"
#include "../Utils/Utils.h"

#include "../Graphics/MeshesResourcesLoader.h"

#include "../Physics/PhysicsEngine.h"

struct GravityComponent
{
	glm::vec3 force;
};

struct RigidBodyComponent
{
	glm::vec3 velocity;
	glm::vec3 acceleration;
};

struct TransformComponent
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

public:
	
	glm::mat4 getTransformMatrix()
	{
		glm::mat4 rotationMatrix = glm::toMat4(glm::quat(rotation));

		return glm::translate(glm::mat4(1.0f), position)
					* rotationMatrix
					* glm::scale(glm::mat4(1.0f), scale);
	}

	void decomposeTransformToVectors(const glm::mat4& transform)
	{
		Utils::DecomposeTransform(transform, position, rotation, scale);
	}
};

struct CameraComponent
{
	Camera camera;
	bool mainCamera;
};

struct ModelRendererComponent
{
	char pathToModel[30];			// Path to model.
};

struct MeshRendererComponent
{
	char meshType[30] = "Cube";								// Type of mesh.
	char pathToTexture[30] = "Textures\\container.jpg";		// Path to texture.
};

struct TagComponent
{
	char name[30] = "Entity";
};

struct SkyboxComponent
{
	char pathToRightTexture[50] = "Textures\\Skybox\\water_right.jpg";	// Right side of cube.
	char pathToLeftTexture[50] = "Textures\\Skybox\\water_left.jpg"; 	// Left side of cube.
	char pathToTopTexture[50] = "Textures\\Skybox\\water_top.jpg"; 		// Top side of cube.
	char pathToBottomTexture[50] = "Textures\\Skybox\\water_bottom.jpg";// Bottom side of cube.
	char pathToBackTexture[50] = "Textures\\Skybox\\water_back.jpg"; 	// Back side of cube.
	char pathToFrontTexture[50] = "Textures\\Skybox\\water_front.jpg"; 	// Front side of cube.
	bool mainSkybox;													// Flag about being main skybox in the scene.
};

struct Audio3DComponent
{
	char pathToFile[30] = "Music\\piano_music.wav";	// Path to file with music.
	irrklang::ISound* sound = nullptr;				// Sound.
	bool updated = false;							// Flag about being updated.
	bool stopped = false;							// Flag about being stopped.

	// Wrapper for stopping audio.
	void Stop()
	{
		if (sound!=nullptr)
		{
			sound->setIsPaused(true);
		}
	}

	// Wrapper for starting audio.
	void Play()
	{
		if (sound != nullptr)
		{
			sound->setIsPaused(false);
		}
	}
};

struct DirectionalLightComponent
{
	DirectionalLight light;
};

struct PointLightComponent
{
	PointLight light;
};

struct SpotLightComponent
{
	SpotLight light;
};

struct MaterialComponent
{
	Material material;
};

struct PhysXDynamicBox3DComponent
{
	float mass = 30.0f;
	physx::PxRigidDynamic* physXRigidBody;
};

struct PhysXStaticBox3DComponent
{
	physx::PxRigidStatic* physXRigidBody;
};

struct PhysXDynamicSphere3DComponent
{
	float mass = 30.0f;
	float radius = 1.0f;
	physx::PxRigidDynamic* physXRigidBody;
};

struct PhysXStaticSphere3DComponent
{
	float radius = 1.0f;
	physx::PxRigidStatic* physXRigidBody;
};

struct PhysXDynamicCapsule3DComponent
{
	float mass = 30.0f;
	float halfHeight = 0.65f;
	float radius = 0.35f;
	physx::PxRigidDynamic* physXRigidBody;
};

struct PhysXStaticCapsule3DComponent
{
	float halfHeight = 0.65f;
	float radius = 0.35f;
	physx::PxRigidStatic* physXRigidBody;
};

struct PhysXDynamicMesh3DComponent
{
	float mass = 30.0f;
	physx::PxRigidDynamic* physXRigidBody;
};

struct PhysXStaticMesh3DComponent
{
	physx::PxRigidStatic* physXRigidBody;
};
#endif