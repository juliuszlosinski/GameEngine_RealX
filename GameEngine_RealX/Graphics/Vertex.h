#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ostream>

struct Vertex
{
	glm::vec3 position;     // Position of vertex (x, y, z).
	glm::vec2 texture;      // Texture cordinates (u, v).
	glm::vec3 normal;       // Position of normals (nx, ny, nz).
};      
#endif