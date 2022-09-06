#ifndef GLEW_H
#define GLEW_H
#define GLEW_STATIC
#include "glew.h"
#endif 

#ifndef GLFW_H
#define GLFW_H
#include "glfw3.h"
#endif 

#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif

#ifndef STRING_H
#define STRING_H
#include <string>
#endif

class Window
{
private:
	int width; // Width of GLFW window and viewport.
	int height; // Height of GLFW window and viewport.
	int initialized; // Flag about initializion: 1 - initialized, 0 - not initialized.
	std::string title; // Title of window.
	GLFWwindow* pWindow; // Pointer to the GLFW window.
	bool keys[1024]; // Keyboard keys.

	float redColorFactor; // Red factor of background.
	float greenColorFactor; // Green factor of background.
	float blueColorFactor; // Blue factor of background.

public:
	// Constructors:
	Window(int width, int height, const std::string& title, float redColorFactor, float greenColorFactor, float blueColorFactor);
	Window();

	// Destructors:
	~Window();

	// Proporties:
	int getWitdh();
	int getHeight();
	int isInitialized();
	int isWindowClosed();
	int isKeyPressed(int keyCode);
	const std::string& getTitle();

	// Methods:
	void SwapBuffers(); // Swap buffers (front with back - double buffering).
	void PollEvents();  // Check if any events happened.
	void Initialize();  // Initialize GLFW Window and other things.
	void Deinitialize(); // Free resources.
	void Close(); // Close window.
	void ClearColorBuffer(); // Clear color from previous scene.

	static void HandleFrameBufferResize(GLFWwindow* pWindow, int widthOfWindow, int heightOfWindow); // Handle resize call back.
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode); // Handle keys call backs.
};

