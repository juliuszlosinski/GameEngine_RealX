#ifndef UTILS_H
#define UTILS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#define GLEW_STATIC
#include "glew.h"

class Utils
{
public:
	// Setting average normals.
	static void setAverageNormals(GLfloat* vertices, unsigned int* indices, unsigned int verticeCount, unsigned int indiceCount, unsigned int vLength, unsigned normalOffset);

	// Decomposing matrix model to vectors (translation,  rotation, scale)
	static bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);
};
#endif