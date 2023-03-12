#ifndef MESH_H
#define MESH_H

#include "Vertex.h"

#define GLEW_STATIC
#include <glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

/*

	############ GENERAL IDEA OF CREATING LOADING MESH ############

	We have 3 buffers (VAO, VBO, IBO).
	The first one (VAO) is like a profile that stores pointers to other buffers.
	The second one (VBO) is a buffer that contains one big array with data about:
	- vertex position (x, y, z) vec3.
	- texture coordinates (x, y) vec2.
	- normals (x, y, z) vec3.
	For example:
	float vbo_data[] = {
	//		POSITION			  TEXTURE            NORMALS
	//	 X	    Y  	  Z			  X    Y		  X    Y     Z
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		1.0f, 1.0f, 1.0f
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		1.0f, 1.0f, 1.0f
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		-1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		-1.0f, 1.0f, 1.0f
	};
	And the next step is to setup pointers to help GPU in intepreting these data.
	We will have three pointers, one for position, one for texture and one for normals.
	These pointers are attributes of vertex, so our vertex will have three atributes!
	We will also have to enable these pointers.

	Setting up pointer:

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

	// [0] -> Is id of pointer, we have 0.
	// [1] -> How many components (3 is for vector 3 that has x, y, z), we have vector 3 so we will have 3.
	// [2] -> What type of data we are passing, we have floats, so we have GL_FLOAT (directive for float).
	// [3] -> Is a stride, we have 8 * sizeof(GLfloat) so it's 8 * 4 Bytes = 24 Bytes
	// [4] -> Is a offset (pointer) to access specified attribute, so it's 0 or for texture is (void*)(vertices[0])*3 = 12 Bytes.

	In the next stage we have to only enable this pointer to be valid!

	glEnableVertexAttribArray(0);

	Other pointers:
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(sizeof(vertices[0]) * 5));
	glEnableVertexAttribArray(2);

	The last one buffer is element array buffer object or indexed buffer that will be used as a container for
	indexes of vertices that we want to use. So if we want to use all of these vertices to create rectangle we will have
	to do such a thing:

	unsigned int ibo_data []={
		0, 1, 3
		1, 3, 2
	}

	After this we have to create IBO id, bind it, copy all of these data and binded it!

	When we have VBO, IBO done, we can unbind VAO!

	VAO is finally created so we use these profile in drawing, we have to bind the program, VAO and invoke glDrawElements
	to use shader program that will use currunet bounded VAO to take data (vertex and his attributes).

	############### CREATING, BINDING AND COPYING DATA TO THESE BUFFERS ####################

	GENERATE VAO ------------------------------------------------> "VERTEX ARRAY OBJECT"
	BIND VAO ----------------------------------------------------> "VERTEX ARRAY OBJECT"
		GENERATE IBO  -------------------------------------------> "ELEMENT ARRAY BUFFER"
		BIND IBO ------------------------------------------------> "ELEMENT ARRAY BUFFER"
		BUFFER DATA/ COPY DATA TO BINDED ELEMENT ARRAY BUFFER ---> "ELEMENT ARRAY BUFFER"
		UNBINDING CURRENT BINDED IBO ----------------------------> "ELEMENT ARRAY BUFFER"

		GENERATE VBO --------------------------------------------> "VERTEX BUFFER OBJECT / ARRAY BUFFER"
		BIND VBO ------------------------------------------------> "VERTEX BUFFER OBJECT / ARRAY BUFFER"
		BUFFER DATA/ COPY DATA TO BINDED ARRAY BUFFER -----------> "VERTEX BUFFER OBJECT / ARRAY BUFFER"
		SET ATTRIBUTE POINTER FOR VERTEX POSITION ---------------> "VERTEX BUFFER OBJECT / ARRAY BUFFER"
		ENABLE ATTRIBUTE POINTER FOR VERTEX POSITION ------------> "VERTEX BUFFER OBJECT / ARRAY BUFFER"
		SET ATTRIBUTE POINTER FOR TEXTURE POSITION --------------> "VERTEX BUFFER OBJECT / ARRAY BUFFER"
		ENABLE ATTRIBUE POINTER FOR  TEXTURE POSITION -----------> "VERTEX BUFFER OBJECT / ARRAY BUFFER"
		SET ATTRIBUTE POINTER FOR NORMAL POSITION ---------------> "VERTEX BUFFER OBJECT / ARRAY BUFFER"
		ENABLE ATTRIBUTE POINTER FOR NORMAL POSITION ------------> "VERTEX BUFFER OBJECT / ARRAY BUFFER"
		UNBINDING CURRENT BINDED VBO ----------------------------> "VERTEX BUFFER OBJECT / ARRAY BUFFER"
	UNBINDING CURRENT BINDED VAO --------------------------------> "VERTEX ARRAY OBJECT"
	*/

class Mesh
{
protected:
	std::vector<Vertex> vertices;	// Vertices data;
	std::vector<GLuint> indices;	// Indices.
	GLuint VAO;						// ID of vertex array object.
	GLuint VBO;						// ID of vertex buffer object.
	GLuint IBO;						// ID of element array/ indexes buffer object. 
	GLuint numberOfVertices;		// Number of vertices.
	GLuint numberOfIndices;			// Number of indices.

public:

	// Default constructor.
	Mesh();

	// Constructor that takes data.
	Mesh(const std::vector<Vertex>& vertices,const std::vector<GLuint>& indices);

	// Get vertices data.
	const std::vector<Vertex>& getVertices();

	// Get indices data.
	const std::vector<GLuint>& getIndices(); 

	// Getting VAO ID.
	GLuint getVAO();

	// Getting VBO ID.
	GLuint getVBO();

	// Getting number of indices.
	GLuint getIndexCount();

	// Getting number of vertices.
	GLuint getNumberOfVertices();

	// Creating mesh by using:
	// - buffer of vertices data (position cords, texture cords, normals cords),
	// - buffer of indices that will tell which vertex use in current moment.
	// - number of vertices,
	// - number of indices,
	void CreateMesh();
	
	// Rendering mesh:
	// Binding VAO, IBO and calling glDrawElements(GL_TRIANGLES, numberOfIndices, 0, GL_UNSIGNED_INT, 0).
	// And unbinding IBO and VAO.
	void RenderMesh();

	// Clearing mesh, it means that will free GPU memory by deallocating VAO, VBO and IBO.
	void ClearMesh();

	// Getting vector with vertices.
	std::vector<Vertex>& getRefVertices()
	{
		return vertices;
	}

	// Destructor that will invoke ClearMesh method.
	~Mesh();
};
#endif