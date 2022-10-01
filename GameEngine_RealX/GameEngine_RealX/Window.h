#ifndef GLEW_H
#define GLEW_H
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

#ifndef CAMERA_H
#define CAMERA_H
#include "Camera.h"
#endif

class Window
{
private:
	int width;              // Width of GLFW window and viewport.
	int height;             // Height of GLFW window and viewport.
	int initialized;        // Flag about initializion: 1 - initialized, 0 - not initialized.
	std::string title;      // Title of window.
	GLFWwindow* pWindow;    // Pointer to the GLFW window.
	bool keys[1024];        // Keyboard keys.

	float redColorFactor;   // Red factor of background.
	float greenColorFactor; // Green factor of background.
	float blueColorFactor;  // Blue factor of background.

	float lastX;			// Last position of mouse on x axis.
	float lastY;            // Last position of mouse on y axis.
	float deltaX;           // Delta on the x axis.
	float deltaY;           // Delta on the y axis.
	float deltaScroll;      // Delta on scroll.
	bool firstMouseMoved;   // Flag for first mouse moved.

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
	float getLastX();
	float getLastY();
	float getDeltaX();
	float getDeltaY();
	float getDeltaScroll();
	bool isFirstMouseMoved();
	int isKeyPressed(int keyCode);
	const std::string& getTitle();
	void setDeltaX(float deltaX);
	void setDeltaY(float deltaY);
	void setDeltaScroll(float deltaScroll);
	void setLastX(float lastX);
	void setLastY(float lastY);
	void setFirstMouseMoved(bool firstMouseMoved);

	// Methods:
	void SwapBuffers(); // Swap buffers (front with back - double buffering).
	void PollEvents();  // Check if any events happened.
	void Initialize();  // Initialize GLFW Window and other things.
	void Deinitialize(); // Free resources.
	void Close(); // Close window.
	void ClearColorBuffer(); // Clear color from previous scene.
	// Clear color from previous scene.
	void ClearDepthBuffer(); // Clear depth buffer.
	void EnableDepthTest(); // Enabling depth test.

	static void HandleFrameBufferResize(GLFWwindow* pWindow, int widthOfWindow, int heightOfWindow); // Handle resize call back.
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode); // Handle keys call backs.
	static void HandleMouseMovement(GLFWwindow* window, double xposIn, double yposIn);
	static void HandleScroll(GLFWwindow* window, double xoffset, double yoffset);
};

