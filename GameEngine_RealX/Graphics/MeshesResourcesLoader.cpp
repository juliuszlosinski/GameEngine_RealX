#include "MeshesResourcesLoader.h"

std::map<MESH_TYPES, Mesh*>	      MeshesResourcesLoader::loadedMeshes;	// Type of mesh that are located and stored on GPU (VAO, VBO, IBO).
std::map<std::string, Model*>     MeshesResourcesLoader::loadedModels;  // Models (multiple meshes) that are located and stored on GPU (VAO's, VBO's, IBO's).  
std::map<MESH_TYPES, bool>   MeshesResourcesLoader::loadedMeshesFLAGS;  // Flags about which mesh type is loaded to GPU.
std::map<std::string, bool>  MeshesResourcesLoader::loadedModelsFLAGS;  // Flags about whitch model is loaded to GPU.

// Loading cube mesh and getting reference to it.
Mesh* MeshesResourcesLoader::LoadCubeMesh()
{
	// Checking if CUBE MESH is loaded.
	if (!loadedMeshesFLAGS[MESH_TYPES::CUBE])
	{
		// Generating vertices and thier attributes (position, texture, normal).
		Vertex f_v1;
		f_v1.position = glm::vec3(-1.0f, 1.0f, 1.0f);
		f_v1.texture = glm::vec2(0.0f, 1.0f);
		f_v1.normal = glm::vec3(0.0f, 0.0f, 1.0f);

		Vertex f_v2;
		f_v2.position = glm::vec3(-1.0f, -1.0f, 1.0f);
		f_v2.texture = glm::vec2(0.0f, 0.0f);
		f_v2.normal = glm::vec3(0.0f, 0.0f, 1.0f);

		Vertex f_v3;
		f_v3.position = glm::vec3(1.0f, -1.0f, 1.0f);
		f_v3.texture = glm::vec2(1.0f, 0.0f);
		f_v3.normal = glm::vec3(0.0f, 0.0f, 1.0f);

		Vertex f_v4;
		f_v4.position = glm::vec3(1.0f, 1.0f, 1.0f);
		f_v4.texture = glm::vec2(1.0f, 1.0f);
		f_v4.normal = glm::vec3(0.0f, 0.0f, 1.0f);

		// -----

		Vertex b_v1;
		b_v1.position = glm::vec3(-1.0f, 1.0f, -1.0f);
		b_v1.texture = glm::vec2(0.0f, 1.0f);
		b_v1.normal = glm::vec3(0.0f, 0.0f, -1.0f);

		Vertex b_v2;
		b_v2.position = glm::vec3(-1.0f, -1.0f, -1.0f);
		b_v2.texture = glm::vec2(0.0f, 0.0f);
		b_v2.normal = glm::vec3(0.0f, 0.0f, -1.0f);

		Vertex b_v3;
		b_v3.position = glm::vec3(1.0f, -1.0f, -1.0f);
		b_v3.texture = glm::vec2(1.0f, 0.0f);
		b_v3.normal = glm::vec3(0.0f, 0.0f, -1.0f);

		Vertex b_v4;
		b_v4.position = glm::vec3(1.0f, 1.0f, -1.0f);
		b_v4.texture = glm::vec2(1.0f, 1.0f);
		b_v4.normal = glm::vec3(0.0f, 0.0f, -1.0f);

		// -----

		Vertex d_v1;
		d_v1.position = glm::vec3(-1.0f, -1.0f, -1.0f);
		d_v1.texture = glm::vec2(0.0f, 1.0f);
		d_v1.normal = glm::vec3(0.0f, -1.0f, 0.0f);

		Vertex d_v2;
		d_v2.position = glm::vec3(-1.0f, -1.0f, 1.0f);
		d_v2.texture = glm::vec2(0.0f, 0.0f);
		d_v2.normal = glm::vec3(0.0f, -1.0f, 0.0f);

		Vertex d_v3;
		d_v3.position = glm::vec3(1.0f, -1.0f, 1.0f);
		d_v3.texture = glm::vec2(1.0f, 0.0f);
		d_v3.normal = glm::vec3(0.0f, -1.0f, 0.0f);

		Vertex d_v4;
		d_v4.position = glm::vec3(1.0f, -1.0f, -1.0f);
		d_v4.texture = glm::vec2(1.0f, 1.0f);
		d_v4.normal = glm::vec3(0.0f, -1.0f, 0.0f);

		//  -----

		Vertex u_v1;
		u_v1.position = glm::vec3(-1.0f, 1.0f, -1.0f);
		u_v1.texture = glm::vec2(0.0f, 1.0f);
		u_v1.normal = glm::vec3(0.0f, 1.0f, 0.0f);

		Vertex u_v2;
		u_v2.position = glm::vec3(-1.0f, 1.0f, 1.0f);
		u_v2.texture = glm::vec2(0.0f, 0.0f);
		u_v2.normal = glm::vec3(0.0f, 1.0f, 0.0f);

		Vertex u_v3;
		u_v3.position = glm::vec3(1.0f, 1.0f, 1.0f);
		u_v3.texture = glm::vec2(1.0f, 0.0f);
		u_v3.normal = glm::vec3(0.0f, 1.0f, 0.0f);

		Vertex u_v4;
		u_v4.position = glm::vec3(1.0f, 1.0f, -1.0f);
		u_v4.texture = glm::vec2(1.0f, 1.0f);
		u_v4.normal = glm::vec3(0.0f, 1.0f, 0.0f);

		// ------

		Vertex l_v1;
		l_v1.position = glm::vec3(-1.0f, 1.0f, -1.0f);
		l_v1.texture = glm::vec2(0.0f, 1.0f);
		l_v1.normal = glm::vec3(-1.0f, 0.0f, 0.0f);

		Vertex l_v2;
		l_v2.position = glm::vec3(-1.0f, -1.0f, -1.0f);
		l_v2.texture = glm::vec2(0.0f, 0.0f);
		l_v2.normal = glm::vec3(-1.0f, 0.0f, 0.0f);

		Vertex l_v3;
		l_v3.position = glm::vec3(-1.0f, -1.0f, 1.0f);
		l_v3.texture = glm::vec2(1.0f, 0.0f);
		l_v3.normal = glm::vec3(-1.0f, 0.0f, 0.0f);

		Vertex l_v4;
		l_v4.position = glm::vec3(-1.0f, 1.0f, 1.0f);
		l_v4.texture = glm::vec2(1.0f, 1.0f);
		l_v4.normal = glm::vec3(-1.0f, 0.0f, 0.0f);

		// ------

		Vertex r_v1;
		r_v1.position = glm::vec3(1.0f, 1.0f, 1.0f);
		r_v1.texture = glm::vec2(0.0f, 1.0f);
		r_v1.normal = glm::vec3(1.0f, 0.0f, 0.0f);

		Vertex r_v2;
		r_v2.position = glm::vec3(1.0f, -1.0f, 1.0f);
		r_v2.texture = glm::vec2(0.0f, 0.0f);
		r_v2.normal = glm::vec3(1.0f, 0.0f, 0.0f);

		Vertex r_v3;
		r_v3.position = glm::vec3(1.0f, -1.0f, -1.0f);
		r_v3.texture = glm::vec2(1.0f, 0.0f);
		r_v3.normal = glm::vec3(1.0f, 0.0f, 0.0f);

		Vertex r_v4;
		r_v4.position = glm::vec3(1.0f, 1.0f, -1.0f);
		r_v4.texture = glm::vec2(1.0f, 1.0f);
		r_v4.normal = glm::vec3(1.0f, 0.0f, 0.0f);

		// -------

		// Setting up vector with vertices.
		std::vector<Vertex> vertices
		{
			f_v1, f_v2, f_v3, f_v4,		// 0 1 2 3
			b_v1, b_v2, b_v3, b_v4,		// 4 5 6 7
			d_v1, d_v2, d_v3, d_v4,		// 8 9 10 11
			u_v1, u_v2, u_v3, u_v4,		// 12 13 14 15
			l_v1, l_v2, l_v3, l_v4,		// 16 17 18 19
			r_v1, r_v2, r_v3, r_v4		// 20 21 22 23
		};

		// Setting up vector with indices.
		std::vector<GLuint> indices
		{
			0, 1, 2,
			2, 3, 0,

			4, 5, 6,
			6, 7, 4,

			8, 9, 10,
			10, 11, 8,

			12, 13, 14,
			14, 15, 12,

			16, 17, 18,
			18, 19, 16,

			20, 21, 22,
			22, 23, 20
		};

		// Creating a cube mesh on the heap.
		Mesh* cubeMesh;
		cubeMesh = new Mesh(vertices, indices);
		cubeMesh->CreateMesh();
		
		// Saving loaded mesh. 
		loadedMeshes[MESH_TYPES::CUBE] = cubeMesh;

		// Setting flag about loaded mesh.
		loadedMeshesFLAGS[MESH_TYPES::CUBE] = true;
	}

	// Returning reference to the cube mesh.
	return loadedMeshes[MESH_TYPES::CUBE];
}

// Loading plain mesh and getting reference to it.
Mesh* MeshesResourcesLoader::LoadRectangleMesh()
{
	// Checking if mesh is currently loaded to the GPU.
	if (!loadedMeshesFLAGS[MESH_TYPES::RECTANGLE])
	{
		// Genereting vertices and thier attributes (position, texture, normal).
		Vertex v1;
		v1.position = glm::vec3(-1.0f, 1.0f, 0.0f);
		v1.texture = glm::vec2(0.0f, 1.0f);
		v1.normal = glm::vec3(0.0f, 0.0f, 1.0f);

		Vertex v2;
		v2.position = glm::vec3(-1.0f, -1.0f, 0.0f);
		v2.texture = glm::vec2(0.0f, 0.0f);
		v2.normal = glm::vec3(0.0f, 0.0f, 1.0f);

		Vertex v3;
		v3.position = glm::vec3(1.0f, -1.0f, 0.0f);
		v3.texture = glm::vec2(1.0f, 0.0f);
		v3.normal = glm::vec3(0.0f, 0.0f, 1.0f);

		Vertex v4;
		v4.position = glm::vec3(1.0f, 1.0f, 0.0f);
		v4.texture = glm::vec2(1.0f, 1.0f);
		v4.normal = glm::vec3(0.0f, 0.0f, 1.0f);

		// Setting up vector with vertices.
		std::vector<Vertex> vertices = {
			v1, v2, v3, v4
		};

		// Setting up vector with indices.
		std::vector<GLuint> indices =
		{
			0, 1, 2,
			2, 3, 0
		};

		// Creating a plain mesh.
		Mesh* plainMesh;
		plainMesh = new Mesh(vertices, indices);
		plainMesh->CreateMesh();

		// Saving new plain mesh.
		loadedMeshes[MESH_TYPES::RECTANGLE] = plainMesh;

		// Setting up a new flag about new saved plain mesh.
		loadedMeshesFLAGS[MESH_TYPES::RECTANGLE] = true;
	}

	// Getting reference to the mesh.
	return loadedMeshes[MESH_TYPES::RECTANGLE];
}

// Loading triangle mesh and getting reference to it.
Mesh* MeshesResourcesLoader::LoadTriangleMesh()
{
	// Checking if there is already saved triangle mesh.
	if (!loadedMeshesFLAGS[MESH_TYPES::TRIANGLE])
	{
		// Generating vertices (positions, textures, normals).
		Vertex v1;
		v1.position = glm::vec3(-1.0f, -1.0f, 0.0f);
		v1.texture = glm::vec2(0.0f, 0.0f);
		v1.normal = glm::vec3(0.0f, 0.0f, 1.0f);

		Vertex v2;
		v2.position = glm::vec3(1.0f, -1.0f, 0.0f);
		v2.texture = glm::vec2(1.0f, 0.0f);
		v2.normal = glm::vec3(0.0f, 0.0f, 1.0f);

		Vertex v3;
		v3.position = glm::vec3(0.0f, 1.0f, 0.0f);
		v3.texture = glm::vec2(0.5f, 0.5f);
		v3.normal = glm::vec3(0.0f, 0.0f, 1.0f);

		// Setting up a vector with vertices.
		std::vector<Vertex> vertices = {
			v1, v2, v3
		};

		// Setting up a vector with indices.
		std::vector<GLuint> indices = {
			0, 1, 2
		};

		// Creating a new triangle mesh.
		Mesh* triangleMesh;
		triangleMesh = new Mesh(vertices, indices);
		triangleMesh->CreateMesh();

		// Saving a new triangle mesh.
		loadedMeshes[MESH_TYPES::TRIANGLE] = triangleMesh;

		// Setting a flag about a new save triangle mesh.
		loadedMeshesFLAGS[MESH_TYPES::TRIANGLE] = true;
	}

	// Getting reference to the triangle mesh.
	return loadedMeshes[MESH_TYPES::TRIANGLE];
}

// Loading model and getting reference to it.
Model* MeshesResourcesLoader::LoadModel(const std::string& path)
{
	// Checking if model is loaded.
	if (!loadedModelsFLAGS[path])
	{
		// Creating and loading model.
		Model* model = new Model(path);
		model->LoadModel();

		// Saving a new loaded model.
		loadedModels[path] = model;

		// Setting up a flag about a new saved model.
		loadedModelsFLAGS[path] = true;
	}

	// Getting a reference to loaded model.
	return loadedModels[path];
}