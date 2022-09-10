#ifndef WINDOW_H
#define WINDOW_H
#include "Window.h"
#endif 

// Create window with specified params.
Window::Window(int width, int height, const std::string& title, float redColorFactor, float greenColorFactor, float blueColorFactor)
{
	this->width = width;
	this->height = height;
	this->title = title;
	this->redColorFactor = redColorFactor;
	this->greenColorFactor = greenColorFactor;
	this->blueColorFactor = blueColorFactor;

	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}

}

// Default constructor.
Window::Window()
{
	this->width = 800;
	this->height = 600;
	this->title = std::string("OpenGL Application");
	this->redColorFactor = .2f;
	this->greenColorFactor = .3f;
	this->blueColorFactor = .3f;
}

// Destructor.
Window::~Window()
{
	// Free all resources.
	this->Deinitialize();
}

// Check if window is initialized.
int Window::isInitialized()
{
	return this->initialized;
}

// Get width of window/ viewport.
int Window::getWitdh()
{
	return this->width;
}

// Get height of window/ viewport.
int Window::getHeight()
{
	return this->height;
}

// Check if window is closed.
int Window::isWindowClosed()
{
	return glfwWindowShouldClose(this->pWindow);
}

// Get title of window.
const std::string& Window::getTitle()
{
	return this->title;
}

// Swap buffers (front with back) - double buffering.
void Window::SwapBuffers()
{
	// Checking if object is initialized -> GLEW, GLFW and GLFWWindow is correctly initialized.
	if (this->initialized)
	{
		// Swap front with back.
		glfwSwapBuffers(this->pWindow);
	}
}

// Check events if any happened.
void Window::PollEvents()
{
	// Checking if object is initialized -> GLEW, GLFW and GLFWWindow is correctly initialized.
	if (this->initialized)
	{
		// Check events if any happened.
		glfwPollEvents();
	}
}

// Close window.
void Window::Close() {
	glfwSetWindowShouldClose(this->pWindow, GL_TRUE);
}

// Free resources that are were by used by GLFW.
void Window::Deinitialize()
{
	if (this->initialized) {
		glfwSetWindowShouldClose(this->pWindow, GL_TRUE);
		glfwTerminate();
		this->initialized = 0;
	}
}

// Callback for framebuffer resize operation.
void Window::HandleFrameBufferResize(GLFWwindow* pWindow, int widthOfWindow, int heightOfWindow)
{
	// Setting up the new configuration of viewport.
	glViewport(0, 0, widthOfWindow, heightOfWindow);
}

// Get information about if key is pressed.
int Window::isKeyPressed(int keyCode) {
	return this->keys[keyCode];
}

// Clear color from previous scene.
void Window::ClearColorBuffer() {
	glClearColor(this->redColorFactor, this->greenColorFactor, this->blueColorFactor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

// Callback for keys events.
void Window::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode) { // Handle keys call backs.
	// Casting the window.
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	// Checking if any key was pressed.
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			theWindow->keys[key] = false;
		}
	}
}

// Initialize GLFW (Window and its associated context) and GLEW.
void Window::Initialize()
{
	// Initlizing GLFW library.
	if (glfwInit() == GLFW_FALSE) {
		std::cout << "Failed to intialize GLFW library" << std::endl;
		this->initialized = 0;
		return;
	}

	// Setting the up the configuration for window.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creating window and its associated context.
	this->pWindow = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);

	// Checking if window is correctly created.
	if (this->pWindow == nullptr)
	{
		// Printing the message about failing.
		std::cout << "Failed to created GFLW window and its associated context!" << std::endl;

		// Frees allocated resources by GLFW, terminates the GLFW library.
		glfwTerminate();

		// Exiting the program with error.
		this->initialized = 0;
		return;
	}

	// Setting up the current context for the current thread.
	glfwMakeContextCurrent(this->pWindow);

	// Ensuring that GLEW will use modern techniques for managaing OpenGL functionality.
	glewExperimental = GL_TRUE;

	// Initilizng GLEW library.
	if (glewInit() != GLEW_OK) {
		// Printing message about failing.
		std::cout << "Failed to initilize GLEW library!" << std::endl;

		// Exiting the program with error.
		this->initialized = 0;
		return;
	}

	// Setting up the dimensions of viewport.
	glViewport(0, 0, this->width, this->height);

	// Setting up the framebuffer callback for viewport.
	glfwSetFramebufferSizeCallback(this->pWindow, Window::HandleFrameBufferResize);

	// Setting up keys call back.
	glfwSetKeyCallback(this->pWindow, Window::HandleKeys);

	// Setting pointer.
	glfwSetWindowUserPointer(this->pWindow, this);

	this->initialized = 1;
}