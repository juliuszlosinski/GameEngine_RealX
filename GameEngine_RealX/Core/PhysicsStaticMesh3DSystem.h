#ifndef PHYSX_STATIC_MESH3D_SYSTEM
#define PHYSX_STATIC_MESH3D_SYSTEM

#include "Coordinator.h"
#include "System.h"
#include "CoreDataECS.h"
#include "Components.h"
#include "../Graphics/MeshesResourcesLoader.h"

class PhysicsStaticMesh3DSystem : public System
{
public:
	void Update(EntityComponentSystem& g_Coordinator, PhysicsEngine* pPhysX)
	{
		for (auto const& entity : m_Entities)
		{
			auto& tag = g_Coordinator.GetComponent<TagComponent>(entity);
			auto& transform = g_Coordinator.GetComponent<TransformComponent>(entity);
			auto& physXMesh3D = g_Coordinator.GetComponent<PhysXStaticMesh3DComponent>(entity);
			auto& modelComponent = g_Coordinator.GetComponent<ModelRendererComponent>(entity);

			if (physXMesh3D.physXRigidBody == nullptr)
			{
				physXMesh3D.physXRigidBody = pPhysX->CreateStaticActorFromModel(
					*MeshesResourcesLoader::LoadModel(modelComponent.pathToModel),
					physx::PxVec3(transform.position.x, transform.position.y, transform.position.z)
				);
				physXMesh3D.physXRigidBody->setName(tag.name);
			}

			if (physXMesh3D.physXRigidBody != nullptr)
			{
				physx::PxTransform trans;
				trans.p.x = transform.position.x;
				trans.p.y = transform.position.y;
				trans.p.z = transform.position.z;

				physx::PxQuat q1(transform.rotation.x, physx::PxVec3(1.0f, 0.0f, 0.0f));
				physx::PxQuat q2(transform.rotation.y, physx::PxVec3(0.0f, 1.0f, 0.0f));
				physx::PxQuat q3(transform.rotation.z, physx::PxVec3(0.0f, 0.0f, 1.0f));

				trans.q = q1 * q2 * q3;
				physXMesh3D.physXRigidBody->setGlobalPose(trans);
			}
		}
	}
};
#endif