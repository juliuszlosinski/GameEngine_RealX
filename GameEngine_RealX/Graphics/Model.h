#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "Texture.h"


class Model
{
	std::vector<Mesh*> meshList;			// Vector of meshes.
	std::vector<Texture*> textureList;		// Vector of textures.
	std::vector<unsigned int> meshToText;	// Vector of meshes to textures.
	std::string fileName;					// Name of filename.
	bool isLoaded;							// Flag about loaded model.

	glm::vec3 max = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 min = glm::vec3(1000.0f, 1000.0f, 1000.0f);

	void LoadNode(aiNode* node, const aiScene* scene);
	void LoadMesh(aiMesh* mesh, const aiScene* scene);
	void LoadMaterials(const aiScene* scene);
public:
	Model();
	Model(const std::string& fileName);

	void Normalize();

	std::vector<Mesh*>& getRefMeshList()
	{
		return meshList;
	}

	// Getting all vertices position from model.
	std::vector<glm::vec3> getTotalVertexPositions()
	{
		std::vector<glm::vec3> allVerticesWithPositions;
		for (int i = 0; i < meshList.size(); i++)
		{
			std::vector<Vertex> vertices = meshList[i]->getVertices();
			for (int j = 0; j < vertices.size(); j++)
			{
				allVerticesWithPositions.push_back(vertices[j].position);
				//std::cout << vertices[j].position.x << " " << vertices[j].position.x << " " << vertices[j].position.x << "\n";
			}
			//std::cout << "\n";
		}
		
		return allVerticesWithPositions;
	}

	// Getting all indices position from model.
	std::vector<unsigned int> getTotalIndices()
	{
		std::vector<unsigned int> allIndices;
		for (int i = 0; i < meshList.size(); i++)
		{
			std::vector<unsigned int> indices = meshList[i]->getIndices();
			for (int j = 0; j < indices.size(); j++)
			{
				allIndices.push_back(indices[j]);
			}
		}
		return allIndices;
	}

	// Getting total number of vertices.
	int getTotalNumberOfVertices()
	{
		int sum = 0;
		for (int i = 0; i < meshList.size(); i++)
		{
			sum += meshList[i]->getNumberOfVertices();
		}
		return sum;
	}

	// Getting total number of indices.
	int getTotalNumberOfIndices()
	{
		int sum = 0;
		for (int i = 0; i < meshList.size(); i++)
		{
			sum += meshList[i]->getIndexCount();
		}
		return sum;
	}

	void LoadModel();
	void RenderModel();
	void ClearModel();
	~Model();
};
#endif