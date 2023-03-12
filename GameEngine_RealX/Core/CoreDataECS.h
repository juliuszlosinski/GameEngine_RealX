#ifndef CORE_DATA_ECS_H
#define CORE_DATA_ECS_H

#include <string>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <bitset>
#include <assert.h>
#include <queue>
#include <array>
#include <set>
#include <unordered_map>

using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 5000;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

#endif