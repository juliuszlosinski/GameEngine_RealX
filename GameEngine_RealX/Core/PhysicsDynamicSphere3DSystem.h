#ifndef PHYSX_DYNAMIC_SPHERE3D_SYSTEM
#define PHYSX_DYNAMIC_SPHERE3D_SYSTEM

#include "Coordinator.h"
#include "System.h"
#include "CoreDataECS.h"
#include "Components.h"

class PhysicsDynamicSphere3DSystem : public System
{
public:
	void Update(EntityComponentSystem& g_Coordinator, PhysicsEngine* pPhysX)
	{
		for (auto const& entity : m_Entities)
		{
			auto& tag = g_Coordinator.GetComponent<TagComponent>(entity);
			auto& transform = g_Coordinator.GetComponent<TransformComponent>(entity);
			auto& physXSphere3D = g_Coordinator.GetComponent<PhysXDynamicSphere3DComponent>(entity);

			if (physXSphere3D.physXRigidBody == nullptr)
			{
				physXSphere3D.physXRigidBody = pPhysX->CreateDynamicSphere(
					physXSphere3D.radius,
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

				physXSphere3D.physXRigidBody->setGlobalPose(trans);
				physXSphere3D.physXRigidBody->setMass(physXSphere3D.mass);
				physXSphere3D.physXRigidBody->setName(tag.name);
			}

			if (physXSphere3D.physXRigidBody != nullptr)
			{
				physx::PxTransform pxTransform = physXSphere3D.physXRigidBody->getGlobalPose();

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