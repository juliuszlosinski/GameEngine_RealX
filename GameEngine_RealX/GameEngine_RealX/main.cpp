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

/*
#ifndef SOIL_H
#define SOIL_H
#include <soil.h>
#endif
*/

#ifndef STB_H
#define STB_H
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

class Texture {
private:
	GLuint textureID{};
	int width{};
	int height{};
	int bitDepth{};
	std::string pathToBitmapFile;

public:
	Texture() {
		this->textureID = 0;
		this->width = 0;
		this->height = 0;
		this->pathToBitmapFile = "";
	}

	Texture(std::string const& pathToBitmap) {
		LoadTexture(pathToBitmap);
	}

	void LoadTexture(std::string const& pathToBitmap) {
		unsigned char* data;
		data = stbi_load(pathToBitmap.c_str(), &width, &height, &bitDepth, 0);
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "Failed to load texture!\n";
		}
		stbi_image_free(data);
		stbi_set_flip_vertically_on_load(true);
		this->textureID = texture;
		this->pathToBitmapFile = pathToBitmap.c_str();
	}

	void UseTexture() {
		glBindTexture(GL_TEXTURE_2D, this->textureID);
	}
};

int main(void) {

	Window* pWindow;
	pWindow = new Window();

	pWindow->Initialize();

	Shader* pShader;
	pShader = new Shader();
	pShader->CreateFromFiles("Resources\\Shaders\\shader.vert", "Resources\\Shaders\\shader.frag");

	GLfloat vertices[] = {
		-0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.0f,	0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		0.3f, 0.3f, 0.3f,   1.0f, 1.0f
	};

	GLuint indices[] = {
		0, 1, 2,
		0, 3, 2
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

	Texture t1("Resources\\Bitmaps\\container.jpg");
	//GLuint secondTexture = createTexture("Resources\\Bitmaps\\tower.jpg");

	float delta{};
	// ########## RENDER LOOOP ########
	while (!pWindow->isWindowClosed()) {

		// Checking if any event happend.
		pWindow->PollEvents();

		// Clearing previous scene.
		pWindow->ClearColorBuffer();

		delta += 0.001f;
		pShader->UseProgram();
		pShader->setFloat("delta", delta);
		
		glActiveTexture(GL_TEXTURE0);
		t1.UseTexture();
		pShader->setInt("firstTexture", 0);

		/*
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, secondTexture);
			pShader->setInt("secondTexture", 1);
		*/

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Swapping color buffer.
		pWindow->SwapBuffers();

		if (pWindow->isKeyPressed(GLFW_KEY_ESCAPE))
			pWindow->Close();
	}

	// Free resources taken by GLFW.
	pWindow->Deinitialize();

	return 0;
}