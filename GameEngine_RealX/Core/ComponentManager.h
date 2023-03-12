#ifndef COMPONENT_MANAGER
#define COMPONENT_MANAGER

#include "CoreDataECS.h"
#include "IComponentArray.h"
#include "ComponentArray.h"

class ComponentManager
{
private:
	// Map from type string pointer to a component type.
	std::unordered_map<const char*, ComponentType> m_ComponentTypes{};

	// Map from type string pointer to a component array.
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_ComponentArrays{};

	// The component type to be assigned to the next registered component - starting at 0.
	ComponentType m_NextComponentType{};

	// Convience function to get the statically casted pointer to the ComponentArray of type T. 
	template <typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		const char* typeName = typeid(T).name();
		assert(m_ComponentTypes.find(typeName) != m_ComponentTypes.end() && "Component not registered before use.");
		return std::static_pointer_cast<ComponentArray<T>>(m_ComponentArrays[typeName]);
	}

public:
	template<typename T>
	void RegisterComponent()
	{
		const char* typeName = typeid(T).name();
		assert(m_ComponentTypes.find(typeName) == m_ComponentTypes.end() && "Registering component type more than once!");

		//Adding this component type to the component type map.
		m_ComponentTypes.insert({ typeName, m_NextComponentType });

		// Create a ComponentArray pointer and add it to the component arrays map.
		m_ComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

		// Increment the value so that next component registered will be different. 
		++m_NextComponentType;
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		const char* typeName = typeid(T).name();

		assert(m_ComponentTypes.find(typeName) != m_ComponentTypes.end() && "Component not registered before use.");

		// Return this component's type - used for creating signatures.
		return m_ComponentTypes[typeName];
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		// Add a component to the array for an entity.
		GetComponentArray<T>()->InsertData(entity, component);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		// Remove a component from the array for an entity.
		GetComponentArray<T>()->RemoveData(entity);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		// Get a reference to a component from the array for an entity.
		return GetComponentArray<T>()->GetData(entity);
	}

	void EntityDestroyed(Entity entity)
	{
		// Notify each component array that entity has been destroyed.
		// If it has a component for that entity, it will remove it.
		for (auto const& pair : m_ComponentArrays)
		{
			auto const& component = pair.second;
			component->EntityDestroyed(entity);
		}
	}
};

#endif