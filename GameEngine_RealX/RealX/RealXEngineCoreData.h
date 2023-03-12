#ifndef REALX_ENGINE_CORE_DATA_H
#define REALX_ENGINE_CORE_DATA_H

#define GLEW_STATIC
#include "glew.h"
#include "glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Core/Coordinator.h"
#include "../Graphics/Camera.h"
#include "../Window/Window.h"
#include "../Core/Components.h"

#include "../Core/PhysicsSystem.h"
#include "../Core/ModelRenderingSystem.h"
#include "../Core/MeshRenderingSystem.h"
#include "../Core/SkyboxRenderingSystem.h"
#include "../Core/CameraSystem.h"
#include "../Core/DirectionalLightSystem.h"
#include "../Core/PointLightSystem.h"
#include "../Core/SpotLightSystem.h"
#include "../Core/Audio3DSystem.h"

#include "../Core/PhysicsDynamicBox3DSystem.h"
#include "../Core/PhysicsStaticBox3DSystem.h"

#include "../Core/PhysicsDynamicSphere3DSystem.h"
#include "../Core/PhysicsStaticSphere3DSystem.h"

#include "../Core/PhysicsDynamicCapsule3DSystem.h"
#include "../Core/PhysicsStaticCapsule3DSystem.h"

#include "../Core/PhysicsDynamicMesh3DSystem.h"
#include "../Core/PhysicsStaticMesh3DSystem.h"

#include "../Physics/PhysicsEngine.h"

#include "../Graphics/Renderer3D.h"
#include "../Core/REntity.h"
#include "../Graphics/MeshTypes.h"
#endif 