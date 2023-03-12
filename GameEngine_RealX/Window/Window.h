#ifndef WINDOW_H
#define WINDOW_H

#define GLEW_STATIC
#include "glew.h"
#include "glfw3.h"
#include "../Graphics/Camera.h"

#include <iostream>
#include <string>

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
	std::string glslVersion;// Version of GLSL.

	GLuint  m_FrameBufferID;
	GLuint m_TextureColorID;
	GLuint m_TextureDepthID;
	GLuint m_RendererBufferID;

public:
	// Constructors:
	Window(int width, int height, const std::string& title, float redColorFactor, float greenColorFactor, float blueColorFactor);
	Window();

	// Destructors:
	~Window();

	GLuint getFrameBufferID()
	{
		return m_FrameBufferID;
	}

	GLuint getTextureColorFromFrameBuffer()
	{
		return m_TextureColorID;
	}

	GLuint getTextureDepthFromFrameBuffer()
	{
		return m_TextureDepthID;
	}

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
	
	void setFrameBuffer()
	{
		glGenFramebuffers(1, &m_FrameBufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
			glGenTextures(1, &m_TextureColorID);
			glBindTexture(GL_TEXTURE_2D, m_TextureColorID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_2D, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureColorID, 0);
			glGenRenderbuffers(1, &m_RendererBufferID);
			glBindRenderbuffer(GL_RENDERBUFFER, m_RendererBufferID);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RendererBufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}


	void BindToFrameBufferForTexture()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
		glEnable(GL_POLYGON_SMOOTH);
		EnableDepthTest();
		glfwSwapInterval(1);
		glEnable(GL_MULTISAMPLE);
		ClearColorBuffer();
		ClearDepthBuffer();
		glViewport(0, 0, 1920, 1080);
	}

	void UseDefaultFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		EnableDepthTest();
	}

	GLFWwindow* getGLFWwindow()
	{
		return pWindow;
	}
	const char* getGLSLVersion()
	{
		return glslVersion.c_str();
	}

	void DisableDepthMask()
	{
		glDepthMask(GL_FALSE);
	}

	void EnableDepthMask()
	{
		glDepthMask(GL_TRUE);
	}

	// Methods:
	void SwapBuffers(); // Swap buffers (front with back - double buffering).
	void PollEvents();  // Check if any events happened.
	void Init();  // Initialize GLFW Window and other things.
	void Deinitialize(); // Free resources.
	void Close(); // Close window.
	void ClearColorBuffer(); // Clear color from previous scene.
	// Clear color from previous scene.
	void ClearDepthBuffer(); // Clear depth buffer.
	void EnableDepthTest(); // Enabling depth test.

	void SetPolygonMode()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	static void HandleFrameBufferResize(GLFWwindow* pWindow, int widthOfWindow, int heightOfWindow); // Handle resize call back.
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode); // Handle keys call backs.
	static void HandleMouseMovement(GLFWwindow* window, double xposIn, double yposIn);
	static void HandleScroll(GLFWwindow* window, double xoffset, double yoffset);
};
#endif