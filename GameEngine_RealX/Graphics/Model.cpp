#include "Model.h"
#include <fstream>

//Default constructor.
Model::Model()
{
	this->fileName = "Models\\DefaultCube.obj";
	isLoaded = false;
}

// Constructor with path.
Model::Model(const std::string& fileName)
{
	this->fileName = fileName;
	isLoaded = false;
}

// Default destructor.
Model::~Model()
{

}

// Rendering model.
void Model::RenderModel()
{
	// Checking if model is loaded.
	if (isLoaded)
	{
		// Going through every mesh.
		for (size_t i = 0; i < meshList.size(); i++)
		{
			// Getting material index.
			unsigned int materialIndex = meshToText[i];

			// Checking if material index exists. -----> BINDING TEXTURE.
			if (materialIndex < textureList.size() && textureList[materialIndex])
			{
				textureList[materialIndex]->UseTexture();
			}

			// Rendering mesh. ----------> BINDING VAO.
			meshList[i]->RenderMesh();
		}
	}
	else
	{
		std::cerr << "Model with path: " << this->fileName << " is not loaded!";
	}
}

// Loading model by using provided path to file.
void Model::LoadModel()
{
	// Creating importer for loading model.
	Assimp::Importer importer;

	// Loading "scene" that is our model.
	const aiScene* scene = importer.ReadFile(
		this->fileName,
		aiProcess_Triangulate
		| aiProcess_FlipUVs 
		| aiProcess_GenSmoothNormals 
		| aiProcess_JoinIdenticalVertices
	);

	// Checking if scene is correctly loaded.
	if (!scene)
	{
		std::cout << "Model " << this->fileName << "failed to load " << importer.GetErrorString();
		return;
	}

	// Starting loading nodes (meshes, indices).
	LoadNode(scene->mRootNode, scene);

	// Loading materials (textures).
	LoadMaterials(scene);

	Normalize();

	// Setting the flag.
	isLoaded = true;
}

// Loading one from scene and going to another child node.
void Model::LoadNode(aiNode* node, const aiScene* scene)
{
	// Loading every mesh that is corresponding to this Node.
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	// Loading child nodes.
	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		LoadNode(node->mChildren[i], scene);
	}
}

#define DEBUG
#define DEBUG_TO_FILE

void Model::Normalize()
{
	std::cout << "Model::Starting normalizing...\n";
	for (int i = 0; i < meshList.size(); i++)
	{
		Mesh* mesh = meshList[i];
		std::vector<Vertex> newVertices;
		std::vector<Vertex> vertices = mesh->getRefVertices();
		std::cout << vertices[0].position.x << "\n";
		for (int j = 0; j < vertices.size(); j++)
		{
			//std::cout << "\nBefore: VEC(" << vertices[j].position.x << ", " << vertices[j].position.y << ", " << vertices[j].position.z << ")\n";
			glm::vec3 center = (max + min) / 2.0f;
			glm::vec3 halfSize = (max - min) / 2.0f;
			vertices[j].position = (vertices[j].position - center) / halfSize;
			newVertices.push_back(vertices[j]);
			/*
			vertices[j].position.x = (2.0 * (vertices[j].position.x - min.x) / (max.x - min.x) - 1.0);
			vertices[j].position.y = (2.0 * (vertices[j].position.y - min.y) / (max.y - min.y) - 1.0);
			vertices[j].position.z = (2.0 * (vertices[j].position.z - min.z) / (max.z - min.z) - 1.0);
			*/
			//std::cout << "After: VEC(" << vertices[j].position.x << ", " << vertices[j].position.y << ", " << vertices[j].position.z << ")\n";
		}
		meshList[i] = new Mesh(newVertices, mesh->getIndices());
		meshList[i]->CreateMesh();
		free(mesh);
		std::cout << vertices[0].position.x << "\n";
	}
	std::cout << "Model::Normalzing is finished!\n";
}

// Loading mesh.
void Model::LoadMesh(aiMesh* mesh, const aiScene* scene)
{
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout.precision(2);

	// Creating container for vertices (positions, texture, normals).
	std::vector<Vertex> vertices;

	// Creating container for indices.
	std::vector<GLuint> indices;

#ifdef DEBUG_TO_FILE
	std::ofstream logFile;
	logFile.open("mesh.log");
	logFile << "Vertex data: " << std::endl;;
	logFile << "POSITION - TEXTURE - NORMALS" << std::endl;
#endif
#ifdef DEBUG_TO_CMD
	std::cout << "Vertex data: " << std::endl;
	std::cout << "POSITION - TEXTURE - NORMALS" << std::endl;
#endif

	// Going through every vertex in the mesh.
	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		// Setting vertex position.
		vertex.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
		//vertex.position = glm::normalize(vertex.position);

		if (vertex.position.x > max.x)
		{
			max.x = vertex.position.x;
		}
		if (vertex.position.y > max.y)
		{
			max.y = vertex.position.x;
		}
		if (vertex.position.z > max.z)
		{
			max.z = vertex.position.z;
		}

		if (vertex.position.x < min.x)
		{
			min.x = vertex.position.x;
		}
		if (vertex.position.y < min.y)
		{
			min.y = vertex.position.y;
		}
		if (vertex.position.z < min.z)
		{
			min.z = vertex.position.z;
		}

#ifdef DEBUG_TO_CMD
		std::cout << mesh->mVertices[i].x << ", " << mesh->mVertices[i].y << ", " << mesh->mVertices[i].z << " | ";
#endif
#ifdef DEBUG_TO_FILE
		logFile << mesh->mVertices[i].x << ", " << mesh->mVertices[i].y << ", " << mesh->mVertices[i].z << " | ";
#endif 

		// Checking if theres is vertex texture cords.
		if (mesh->mTextureCoords[0])
		{
			// Setting corresponding vertex texture cords.
#ifdef DEBUG_TO_CMD
			std::cout << mesh->mTextureCoords[0][i].x << ", " << mesh->mTextureCoords[0][i].y << " | ";
#endif
#ifdef DEBUG_TO_FILE
			logFile << mesh->mTextureCoords[0][i].x << ", " << mesh->mTextureCoords[0][i].y << " | ";
#endif
			vertex.texture = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
		}
		else 
		{
#ifdef DEBUG_TO_CMD
			std::cout << 0 << ", " << 0 << " | ";
#endif
#ifdef DEBUG_TO_FILE
			logFile << 0 << ", " << 0 << " | ";
#endif
			// Setting default vertex texture cords.
			vertex.texture = { 0.0f, 0.0f };
		}

		// Adding normals.
#ifdef DEBUG_TO_CMD
		std::cout << -mesh->mNormals[i].x << ", " << -mesh->mNormals[i].y << ", " << -mesh->mNormals[i].z << " ";
		std::cout << "\n";
#endif
#ifdef DEBUG_TO_FILE
		logFile << -mesh->mNormals[i].x << ", " << -mesh->mNormals[i].y << ", " << -mesh->mNormals[i].z << " ";
		logFile << "\n";
#endif
		//std::cout << "\n";
		vertex.normal = { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z };
		vertices.insert(vertices.end(), vertex);
	}

	

#ifdef DEBUG_TO_CMD
	std::cout << "Indices:" << std::endl;
#endif
#ifdef DEBUG_TO_FILE
	logFile << "Indices:" << std::endl;
#endif

	// Going through faces to get the indices.
	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		// Saving current face.
		aiFace face = mesh->mFaces[i];

		// Adding indices of face to container for indices.
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
#ifdef DEBUG_TO_CMD
			std::cout << face.mIndices[j] << ", ";
#endif
#ifdef DEBUG_TO_FILE
			logFile << face.mIndices[j] << ", ";
#endif
			indices.push_back(face.mIndices[j]);
		}
	}

#ifdef DEBUG_TO_CMD
	std::cout << std::endl;
#endif
#ifdef DEBUG_TO_FILE
	logFile << std::endl;
#endif

	// Creating mesh.
	Mesh* newMesh = new Mesh(vertices, indices);
	//newMesh->CreateMesh();

	// Adding new mesh.
	meshList.push_back(newMesh);

	// Adding material index.
	meshToText.push_back(mesh->mMaterialIndex);

#ifdef DEBUG_TO_CMD
	std::cout << "Number of vertices: " << vertices.size() << std::endl;
	std::cout << "Number of indices: " << indices.size() << std::endl;
#endif

#ifdef DEBUG_TO_FILE
	logFile << "Number of vertices: " << vertices.size() << std::endl;
	logFile << "Number of indices: " << indices.size() << std::endl;
	logFile.close();
#endif
}

// Loading materials (textures) from scene.
void Model::LoadMaterials(const aiScene* scene)
{
	// Resizing the texture list container.
	textureList.resize(scene->mNumMaterials);

	// Going through all materials/ textures.
	for (size_t i = 0; i < scene->mNumMaterials; i++)
	{
		// Taking reference to material.
		aiMaterial* material = scene->mMaterials[i];

		// Saving the default reference.
		textureList[i] = nullptr;

		// Checking if there is a texture.
		if (material->GetTextureCount(aiTextureType_DIFFUSE))
		{
			// Getting the path to the texture.
			aiString pathToTexture;

			// Checking if we can get path to the texture.
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &pathToTexture) == AI_SUCCESS)
			{
				// Selecting the path.
				int idx = std::string(pathToTexture.data).rfind("\\\\");
				std::string fileName = std::string(pathToTexture.data).substr(idx + 1);
				std::string texPath = std::string("Textures/") + fileName;

				// Creating texture.
				textureList[i] = new Texture(texPath.c_str());

				// Checking if textures is correctly loaded.
				
				
				if (!textureList[i]->LoadTexture())
				{
					// Printing the message about failed loading.
					std::cout << "Failed to load texture: " << texPath << std::endl;

					// Deleting texture.
					delete textureList[i];
					
					// Dereferencing current texture.
					textureList[i] = nullptr;
				}
				
				
			}
		}

		
		// There is no texture.
		if (!textureList[i])
		{
			// Creating a texture with plain.png image.
			textureList[i] = new Texture("Textures/plain.png");

			// Loading texture.
			textureList[i]->LoadTexture();
		}
		
		
	}
}

void Model::ClearModel()
{
	// Going through every meshes and deleting them.
	for (size_t i = 0; i < meshList.size(); i++)
	{
		// There is a mesh.
		if (meshList[i])
		{
			// Deleting mesh.
			delete meshList[i];

			// Dereferencing current mesh.
			meshList[i] = nullptr;
		}
	}

	// Going through every texture and deleting them.
	for (size_t i = 0; i < textureList.size(); i++)
	{
		// There is a texture.
		if (textureList[i])
		{
			// Deleting mesh.
			delete textureList[i];

			// Dereferencing current texture.
			textureList[i] = nullptr;
		}
	}
}