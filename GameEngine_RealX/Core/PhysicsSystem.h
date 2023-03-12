#ifndef PHYSICS_SYSTEM
#define PHYSICS_SYSTEM

#include "Coordinator.h"
#include "System.h"
#include "CoreDataECS.h"
#include "Components.h"

class PhysicsSystem : public System
{
public:
	void Init()
	{

	}

	void Update(EntityComponentSystem& g_Coordinator, float dt)
	{
		for (auto const& entity : m_Entities)
		{
			auto& rigidBody = g_Coordinator.GetComponent<RigidBodyComponent>(entity);
			auto& transform = g_Coordinator.GetComponent<TransformComponent>(entity);
			auto const& gravity = g_Coordinator.GetComponent<GravityComponent>(entity);

			transform.position += rigidBody.velocity * dt;

			rigidBody.velocity += gravity.force * dt;
		}
	}
};

#endif