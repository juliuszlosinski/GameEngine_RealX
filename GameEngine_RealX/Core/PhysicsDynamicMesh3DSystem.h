#ifndef PHYSX_DYNAMIC_MESH3D_SYSTEM
#define PHYSX_DYNAMIC_MESH3D_SYSTEM

#include "Coordinator.h"
#include "System.h"
#include "CoreDataECS.h"
#include "Components.h"
#include "../Graphics/MeshesResourcesLoader.h"

class PhysicsDynamicMesh3DSystem : public System
{
public:
	void Update(EntityComponentSystem& g_Coordinator, PhysicsEngine* pPhysX)
	{
		for (auto const& entity : m_Entities)
		{
			auto& tag = g_Coordinator.GetComponent<TagComponent>(entity);
			auto& transform = g_Coordinator.GetComponent<TransformComponent>(entity);
			auto& physXMesh3D = g_Coordinator.GetComponent<PhysXDynamicMesh3DComponent>(entity);
			auto& modelComponent = g_Coordinator.GetComponent<ModelRendererComponent>(entity);

			if (physXMesh3D.physXRigidBody == nullptr)
			{
				physXMesh3D.physXRigidBody = pPhysX->CreateDynamicActorFromModel(
					*MeshesResourcesLoader::LoadModel(modelComponent.pathToModel),
					physx::PxVec3(transform.position.x, transform.position.y, transform.position.z)
				);

				physx::PxTransform trans;
				trans.p.x = transform.position.x;
				trans.p.y = transform.position.y;
				trans.p.z = transform.position.z;

				physx::PxQuat q1(transform.rotation.x, physx::PxVec3(1.0f, 0.0f, 0.0f));
				physx::PxQuat q2(transform.rotation.y, physx::PxVec3(0.0f, 1.0f, 0.0f));
				physx::PxQuat q3(transform.rotation.z, physx::PxVec3(0.0f, 0.0f, 1.0f));

				trans.q = q1 * q2 * q3;

				physXMesh3D.physXRigidBody->setGlobalPose(trans);
				physXMesh3D.physXRigidBody->setMass(physXMesh3D.mass);
				physXMesh3D.physXRigidBody->setName(tag.name);
			}

			if (physXMesh3D.physXRigidBody != nullptr)
			{
				physx::PxTransform pxTransform = physXMesh3D.physXRigidBody->getGlobalPose();

				glm::vec3& position = transform.position;
				glm::vec3& rotation = transform.rotation;

				physx::PxVec3 angles;    //yaw pitch roll
				float x = pxTransform.q.x;
				float y = pxTransform.q.y;
				float z = pxTransform.q.z;
				float w = pxTransform.q.w;

				// roll (x-axis rotation)
				double sinr_cosp = 2 * (w * x + y * z);
				double cosr_cosp = 1 - 2 * (x * x + y * y);
				angles.x = std::atan2(sinr_cosp, cosr_cosp);

				// pitch (y-axis rotation)
				double sinp = 2 * (w * y - z * x);
				if (std::abs(sinp) >= 1)
					angles.y = std::copysign(3.14f / 2, sinp); // use 90 degrees if out of range
				else
					angles.y = std::asin(sinp);

				// yaw (z-axis rotation)
				double siny_cosp = 2 * (w * z + x * y);
				double cosy_cosp = 1 - 2 * (y * y + z * z);
				angles.z = std::atan2(siny_cosp, cosy_cosp);

				position.x = pxTransform.p.x;
				position.y = pxTransform.p.y;
				position.z = pxTransform.p.z;

				rotation.x = angles.x;
				rotation.y = angles.y;
				rotation.z = angles.z;
			}

		}
	}
};
#endif