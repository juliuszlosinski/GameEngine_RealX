#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "CoreDataECS.h"

class EntityManager
{
private:
	// Queue of unused entity IDS;
	std::queue<Entity> m_AvailableEntities{};

	// Array of signatures where the index corresponds to the enitity ID;
	std::array<Signature, MAX_ENTITIES> m_Signatures{};
	//			Bitset	  Size of array

	// Totatl living entities - used to keep limits on how many exist.
	std::uint32_t m_LivingEntityCount{};
public:

	EntityManager()
	{
		// Initializng the queue with all possible entity IDs.
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			m_AvailableEntities.push(entity);
		}
	}

	Entity CreateEntity()
	{
		// Checking if current number of entities is smaller than maximum.
		assert(m_LivingEntityCount < MAX_ENTITIES && "To many entities in existence!");

		// Taking and ID from the front of the queue.
		Entity id = m_AvailableEntities.front();

		// Removing (poping) element from the front of the queue.
		m_AvailableEntities.pop();

		// Increasing number of available entites.
		++m_LivingEntityCount;

		// Getting an available entity id.
		return id;
	}

	void DestroyEntity(Entity entity)
	{
		// Checking if entity id is smaller that maximum.
		assert(entity < MAX_ENTITIES && "Entity out of range!");

		// Invalidate the destroyed entity's signature.
		m_Signatures[entity].reset();

		// Putting the destroyed ID at the back of queue.
		m_AvailableEntities.push(entity);

		// Decreasing number of living entities.
		--m_LivingEntityCount;
	}

	void SetSignature(Entity entity, Signature signature)
	{
		// Checking if entity id is smaller than maximum.
		assert(entity < MAX_ENTITIES && "Entity out of range");

		// Putting this entity's signature into the array.
		m_Signatures[entity] = signature;
	}

	Signature GetSignature(Entity entity)
	{
		// Checking if entity id is smaller than maximum.
		assert(entity < MAX_ENTITIES && "Entity out of range!");

		// Getting this entity's signature from the array.
		return m_Signatures[entity];
	}
};
#endif 