#ifndef ICOMPONENT_ARRAY_H
#define ICOMPONENT_ARRAY_H

#include "CoreDataECS.h"

class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
};

#endif