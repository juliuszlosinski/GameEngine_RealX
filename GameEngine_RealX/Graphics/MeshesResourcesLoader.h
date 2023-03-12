#ifndef MESHES_H
#define MESHES_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string>

#include "Model.h"

#include "MeshTypes.h"

class MeshesResourcesLoader
{
	static std::map<MESH_TYPES, Mesh*>	      loadedMeshes;	 // Type of mesh that are located and stored on GPU (VAO, VBO, IBO).
	static std::map<std::string, Model*>      loadedModels;  // Models (multiple meshes) that are located and stored on GPU (VAO's, VBO's, IBO's).  
	static std::map<MESH_TYPES, bool>    loadedMeshesFLAGS;  // Flags about which mesh type is loaded to GPU.
	static std::map<std::string, bool>   loadedModelsFLAGS;  // Flags about whitch model is loaded to GPU.
public:
	// Loading cube mesh and getting reference to it.
	static Mesh* LoadCubeMesh();

	// Loading plain mesh and getting reference to it.
	static Mesh* LoadRectangleMesh();

	// Loading triangle mesh and getting reference to it.
	static Mesh* LoadTriangleMesh();

	// Loading model and getting reference to it.
	static Model* LoadModel(const std::string& path);
};

#endif