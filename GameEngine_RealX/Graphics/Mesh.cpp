#include "Mesh.h"

// Default constructor.
Mesh::Mesh() 
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	numberOfVertices = 0;
	numberOfIndices = 0;
}

// Customized constructor.
Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices)
{
	this->vertices = vertices;
	this->indices = indices;
	this->numberOfIndices = indices.size();
	this->numberOfVertices = vertices.size();
}

// Getting vector with vertices.
const std::vector<Vertex>& Mesh::getVertices()
{
	return vertices;
}

// Getting vector that contains indices.
const std::vector<GLuint>& Mesh::getIndices()
{
	return indices;
}

// Getting VAO ID.
GLuint Mesh::getVAO() {
	return VAO;
}

// Getting VBO ID.
GLuint Mesh::getVBO() {
	return VBO;
}

// Getting number of indices.
GLuint Mesh::getIndexCount() {
	return  numberOfIndices;
}


// Getting number of vertices.
GLuint Mesh::getNumberOfVertices()
{
	return numberOfVertices;
}

#define DEBUG

// Creating mesh by generating ID, binding, copying data, setting attributes (VBO) and unbinding id.
void Mesh::CreateMesh() {
	
#ifdef DEBUG
	std::cerr << "Number of vertices: " << numberOfVertices << std::endl;
	std::cerr << "Number of indices: " << numberOfIndices << std::endl;
#endif
	if (numberOfVertices > 0 && numberOfIndices > 0)
	{
		try 
		{
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &IBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
				glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
		catch (std::exception e)
		{
			return;
		}
	}
}

// Rendering mesh.
void Mesh::RenderMesh() {
	glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

// Free GPU memory by deallocating VAO, VBO and IBO buffers.
void Mesh::ClearMesh() {
	if (VAO != 0) {
		glDeleteBuffers(1, &VAO);
	}
	if (IBO != 0) {
		glDeleteBuffers(1, &IBO);
	}
	if (VBO != 0) {
		glDeleteBuffers(1, &VBO);
	}
	IBO = 0;
	VBO = 0;
	VAO = 0;
	numberOfIndices = 0;
	numberOfVertices = 0;
}

// Destructor that will call ClearMesh method.
Mesh::~Mesh() {
	ClearMesh();
}