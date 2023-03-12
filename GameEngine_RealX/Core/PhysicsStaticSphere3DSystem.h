#ifndef PHYSX_STATIC_SPHERE3D_SYSTEM
#define PHYSX_STATIC_SPHERE3D_SYSTEM

#include "Coordinator.h"
#include "System.h"
#include "CoreDataECS.h"
#include "Components.h"

class PhysicsStaticSphere3DSystem : public System
{
public:
	void Update(EntityComponentSystem& g_Coordinator, PhysicsEngine* pPhysX)
	{
		for (auto const& entity : m_Entities)
		{
			auto& tag = g_Coordinator.GetComponent<TagComponent>(entity);
			auto& transform = g_Coordinator.GetComponent<TransformComponent>(entity);
			auto& physXSphere3D = g_Coordinator.GetComponent<PhysXStaticSphere3DComponent>(entity);

			if (physXSphere3D.physXRigidBody == nullptr)
			{
				physXSphere3D.physXRigidBody = pPhysX->CreateStaticSphere(
					physXSphere3D.radius,
					physx::PxVec3(transform.position.x, transform.position.y, transform.position.z)
				);
				physXSphere3D.physXRigidBody->setName(tag.name);
			}

			if (physXSphere3D.physXRigidBody != nullptr)
			{
				physx::PxTransform trans;
				trans.p.x = transform.position.x;
				trans.p.y = transform.position.y;
				trans.p.z = transform.position.z;

				physx::PxQuat q1(transform.rotation.x, physx::PxVec3(1.0f, 0.0f, 0.0f));
				physx::PxQuat q2(transform.rotation.y, physx::PxVec3(0.0f, 1.0f, 0.0f));
				physx::PxQuat q3(transform.rotation.z, physx::PxVec3(0.0f, 0.0f, 1.0f));

				trans.q = q1 * q2 * q3;
				physXSphere3D.physXRigidBody->setGlobalPose(trans);
			}

		}
	}
};
#endif