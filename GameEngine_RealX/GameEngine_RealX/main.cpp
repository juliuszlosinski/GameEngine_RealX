#ifndef GLEW_H
#define GLEW_H
#define GLEW_STATIC
#include "glew.h"
#endif 

#ifndef GLFW3_H
#define GLFW3_H
#include "glfw3.h"
#endif 

#ifndef STRING_H
#define STRING_H
#include <string>
#endif

#ifndef FSTREAM_H
#define FSTREAM_H
#include <fstream>
#endif

#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif

#ifndef WINDOW_H
#define WINDOW_H
#include "Window.h"
#endif 

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#include "FileHandler.h"
#endif 

#ifndef SHADER_H
#define SHADER_H
#include "Shader.h"
#endif

#ifndef TEXTURE_H
#define TEXTURE_H
#include "Texture.h"
#endif

#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

int main(void) {

	Window* pWindow;
	pWindow = new Window();

	pWindow->Initialize();

	Shader* pShader;
	pShader = new Shader();
	pShader->CreateFromFiles("Resources\\Shaders\\shader.vert", "Resources\\Shaders\\shader.frag");

	Camera* pCamera;
	pCamera = new Camera();

	GLfloat vertices[] = {
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 	0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,		0.3f, 0.3f, 0.3f,  1.0f, 1.0f,

		- 0.5f, 0.5f, -0.5f,	1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		0.5f, 0.5f, -0.5f,		0.3f, 0.3f, 0.3f,  1.0f, 1.0f,

		- 0.5f, 0.5f, -0.5f,	1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		-0.5f, 0.5f,   0.5f,	0.3f, 0.3f, 0.3f,   1.0f, 1.0f,

		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 	0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		0.5f, 0.5f,  0.5f,		0.3f, 0.3f, 0.3f,  1.0f, 1.0f,

		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.3f, 0.3f, 0.3f,  1.0f, 1.0f,

		-0.5f,  0.5f, 0.5f,		1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, 0.5f,		0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	0.3f, 0.3f, 0.3f,  1.0f, 1.0f,
	};


	GLuint indices[] = {
		0, 1, 2,
		0, 3, 2,

		4, 5, 6,
		4, 7, 6,

		8, 9, 10,
		8, 11, 10,

		12, 13, 14,
		12, 15, 14,

		16, 17, 18,
		16, 19, 18,

		20, 21, 24,
		20, 23, 24,
	};

	GLuint VAO{};
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
		GLuint VBO{};
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3*sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		GLuint EBO{};
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);

	Texture t1("Resources\\Bitmaps\\queen.jpg");
	Texture t2("Resources\\Bitmaps\\gravity_falls.jpg");
	//GLuint secondTexture = createTexture("Resources\\Bitmaps\\tower.jpg");

	int a; // Default initilization may cause undefined behaviour.
	int b = 5; // Copy initialization.
	int d(5); // Direct initialization.
	int e{ 6 }; // Uniform initialization.

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	float delta{};
	bool flag = false, f = true;
	// ########## RENDER LOOOP ########
	while (!pWindow->isWindowClosed()) {

		// Checking if any event happend.
		pWindow->PollEvents();

		// Clearing previous scene.
		pWindow->ClearColorBuffer();
		pWindow->EnableDepthTest();
		pWindow->ClearDepthBuffer();

		delta += 0.001f;
		pShader->UseProgram();
		pShader->setFloat("delta", delta);

		glBindVertexArray(VAO);

			glActiveTexture(GL_TEXTURE0);
			t1.UseTexture();
			pShader->setInt("firstTexture", 0);

			glActiveTexture(GL_TEXTURE1);
			t2.UseTexture();
			pShader->setInt("secondTexture", 1);

			glm::mat4 view = glm::mat4(1.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); ;

			glm::mat4 projection;
			projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
			
			pCamera->MouseHandler(pWindow->getDeltaX(), pWindow->getDeltaY(), true);

			pShader->setMat4("view", pCamera->getViewMatrix());
			pShader->setMat4("projection", projection);

			for (int i = 0; i < 10; i++) {

				glm::mat4 model = glm::mat4(1.0f);
				float angle = 20.0f * i;
				model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				model = glm::translate(model, cubePositions[i]);

				pShader->setFloat("delta", delta);
				pShader->setMat4("model", model);
				
				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			}
		glBindVertexArray(0);

		// Swapping color buffer.
		pWindow->SwapBuffers();
		
		std::cout << "Delta X: " << pWindow->getDeltaX() << std::endl;
		std::cout << "Delta y: " << pWindow->getDeltaY() << std::endl;

		if (pWindow->isKeyPressed(GLFW_KEY_ESCAPE))
			pWindow->Close();
		if (pWindow->isKeyPressed(GLFW_KEY_W))
			pCamera->KeyBoardHandler(CameraMovement::CAMERA_FORWARD, 0.05f);
		if (pWindow->isKeyPressed(GLFW_KEY_A))
			pCamera->KeyBoardHandler(CameraMovement::CAMERA_LEFT, 0.05f);
		if (pWindow->isKeyPressed(GLFW_KEY_S))
			pCamera->KeyBoardHandler(CameraMovement::CAMERA_BACKWARD, 0.05f);
		if (pWindow->isKeyPressed(GLFW_KEY_D))
			pCamera->KeyBoardHandler(CameraMovement::CAMERA_RIGHT, 0.05f);
	}

	// Free resources taken by GLFW.
	pWindow->Deinitialize();

	return 0;
}