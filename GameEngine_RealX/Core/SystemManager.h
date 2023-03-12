#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include "CoreDataECS.h"
#include "System.h"

class SystemManager
{
private:
	// Map from system type string pointer to a signature.
	std::unordered_map<const char*, Signature> m_Signatures{};

	// Map from system type string pointer to a system pointer.
	std::unordered_map<const char*, std::shared_ptr<System>> m_Systems{};
public:
	template <typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		const char* typeName = typeid(T).name();

		assert(m_Systems.find(typeName) == m_Systems.end() && "Registering system more than once!");

		// Creating a pointer to the system and return it so it can be used externally.
		auto system = std::make_shared<T>();
		m_Systems.insert({ typeName, system });
		return system;
	}

	template<typename T>
	void SetSignature(Signature signature)
	{
		const char* typeName = typeid(T).name();

		assert(m_Systems.find(typeName) != m_Systems.end() && "System used before registered.");

		// Setting. the signature for this system.
		m_Signatures.insert({ typeName, signature });
	}

	void EntityDestroyed(Entity entity)
	{
		// Erase a destroyed entity from all system lists.
		// m_Entities is a set to se no check needed.
		for (auto const& pair : m_Systems)
		{
			auto const& system = pair.second;

			system->m_Entities.erase(entity);
		}
	}

	void EntitySignatureChanged(Entity entity, Signature entitySignature)
	{
		// Notify each system that an entity's signature changed.
		for (auto const& pair : m_Systems)
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = m_Signatures[type];

			// Entity signature matches system signature - insert into set.
			if ((entitySignature & systemSignature) == systemSignature)
			{
				system->m_Entities.insert(entity);
			}
			// Entity signature does not match system signature - erase from set.
			else
			{
				system->m_Entities.erase(entity);
			}
		}
	}
};

#endif