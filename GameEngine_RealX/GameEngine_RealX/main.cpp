#define GLEW_STATIC

#include "Window.h"
#include "FileHandler.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <iostream>

#ifndef GLEW_H
#define GLEW_H
#include "glew.h"
#endif 

#ifndef GLFW3_H
#define GLFW3_H
#include "glfw3.h"
#endif 


int main(void) {

	Window* pWindow;
	pWindow = new Window();

	pWindow->Initialize();

	Shader* pShader;
	pShader = new Shader();
	pShader->CreateFromFiles("Shaders\\shader.vert", "Shaders\\shader.frag");

	GLfloat vertices[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);

	// ########## RENDER LOOOP ########
	while (!pWindow->isWindowClosed()) {

		// Checking if any event happend.
		pWindow->PollEvents();

		// Clearing previous scene.
		pWindow->ClearColorBuffer();

		// Swapping color buffer.
		pWindow->SwapBuffers();

		if (pWindow->isKeyPressed(GLFW_KEY_ESCAPE))
			pWindow->Close();
	}

	// Free resources taken by GLFW.
	pWindow->Deinitialize();

	return 0;
}