#ifndef RENTITY_H
#define RENTITY_H
#include "Coordinator.h"

class REntity
{
	EntityComponentSystem* m_Coordinator;									 // Pointer to coordinator.
	Entity m_EntityID;											 // Entity id.
	std::unordered_map<const char*, bool> m_AvailableComponents; // All components that entity has.
public:

	// Default constructor.
	REntity()
	{
		m_EntityID = 0;
		m_Coordinator = nullptr;
	}

	// Specific constructor that takes pointer to coordinator.
	REntity(EntityComponentSystem* m_Coordinator)
	{
		this->m_Coordinator = m_Coordinator;
		this->m_EntityID = m_Coordinator->CreateEntity();
		SetRequiredComponents();
	}

	// Setting tag.
	void SetTag(std::string name)
	{
		strncpy_s(GetComponent<TagComponent>().name, name.c_str(), 30);
	}

	// Getting the id of entity.
	Entity getID()
	{
		return m_EntityID;
	}

	// Adding component to entity.
	template <typename T> void AddComponent(T component)
	{
		m_Coordinator->AddComponent(m_EntityID, component);
		m_AvailableComponents[typeid(T).name()] = true;
	}

	// Removing component from entity.
	template <typename T> void RemoveComponent()
	{
		m_Coordinator->RemoveComponent<T>(m_EntityID);
		m_AvailableComponents[typeid(T).name()] = false;
	}

	// Getting component from entity.
	template <typename T> T& GetComponent()
	{
		return m_Coordinator->GetComponent<T>(m_EntityID);
	}

	// Checking entity has a component.
	template <typename T> bool HasComponent()
	{
		return m_AvailableComponents[typeid(T).name()];
	}

private:
	// Setting up essentials components.
	void SetRequiredComponents()
	{
		// Setting up transform component.
		AddComponent<TransformComponent>(
			TransformComponent
			{
				glm::vec3(0.0f, 0.0f, 0.0f),	// Translation (x, y, z)
				glm::vec3(0.0f, 0.0f, 0.0f),	//    Rotation (x, y, z)
				glm::vec3(1.0f, 1.0f, 1.0f)		//	     Scale (x, y, z)
			}
		);

		// Adding tag component.
		AddComponent<TagComponent>({});
		strncpy_s(GetComponent<TagComponent>().name, std::string("Entity" + std::to_string(getID())).c_str(), 30);
	}
};
#endif