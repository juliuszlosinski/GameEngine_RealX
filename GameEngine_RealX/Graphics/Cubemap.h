#ifndef CUBEMAP_H
#define CUBEMAP_H

#define GLEW_STATIC
#include "glew.h"
#include <vector>
#include <string>

#include "Texture.h"
#include <vector>

class Cubemap : Texture
{
	std::string m_PathToRightTexture;	// Right side of cube.
	std::string m_PathToLeftTexture;	// Left side of cube.
	std::string m_PathToTopTexture;		// Top side of cube.
	std::string m_PathToBottomTexture;  // Bottom side of cube.
	std::string m_PathToBackTexture;	// Back side of cube.
	std::string m_PathToFrontTexture;	// Front side of cube.
	GLuint m_CubeMapTextureID;			// ID of cubemap texture.
	bool m_Loaded;
public:

	// Default constructor.
	Cubemap()
	{
		m_PathToRightTexture = "Textures\\Skybox\\water_right.jpg";
		m_PathToLeftTexture = "Textures\\Skybox\\water_left.jpg";
		m_PathToTopTexture = "Textures\\Skybox\\water_top.jpg";
		m_PathToBottomTexture = "Textures\\Skybox\\water_bottom.jpg";
		m_PathToBackTexture = "Textures\\Skybox\\water_back.jpg";
		m_PathToFrontTexture =  "Textures\\Skybox\\water_front.jpg";
		m_Loaded = false;
	}

	// Custom constructoor.
	Cubemap(const std::string& pathToRightRexture, const std::string& pathToLeftTexture,
			const std::string& pathToTopTexture, const std::string& pathToBottomTexture,
			const std::string& pathToBackTexture, const std::string& pathToFrontTexture)
	{
		m_PathToRightTexture = pathToRightRexture;
		m_PathToLeftTexture = pathToLeftTexture;
		m_PathToTopTexture = pathToTopTexture;
		m_PathToBottomTexture = pathToBottomTexture;
		m_PathToBackTexture = pathToBackTexture;
		m_PathToFrontTexture = pathToFrontTexture;
		m_Loaded = false;
	}

	// Getting the cubemap texture ID.
	GLuint getCubeMapTextureID()
	{
		return m_CubeMapTextureID;
	}
	
	// Getting reference to the path right texture.
	std::string& getRefPathToRightTexture()
	{
		return m_PathToRightTexture;
	}

	// Getting reference to the path left texture.
	std::string& getRefPathToLeftTexture()
	{
		return m_PathToLeftTexture;
	}

	// Getting reference to the path top texture.
	std::string& getRefPathToTopTexture()
	{
		return m_PathToTopTexture;
	}

	// Getting reference to the path bottom texture.
	std::string& getRefPathToBottomTexture()
	{
		return m_PathToBottomTexture;
	}

	// Getting reference to the path back texture.
	std::string& getRefPathToBackTexture()
	{
		return m_PathToBackTexture;
	}

	// Getting reference to the path front texture.
	std::string& getRefPathToFrontTexture()
	{
		return m_PathToFrontTexture;
	}

	// Getting flag about loaded.
	bool isLoaded()
	{
		return m_Loaded;
	}

	// Loading texture.
	void LoadTexture()
	{
		// Checking if cubemap is currently loaded.
		if (!m_Loaded)
		{
			// Generating a texture and binding to the proer texture target.
			glGenTextures(1, &m_CubeMapTextureID);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeMapTextureID);

			// Loading sides of cubemap.
			LoadSide(GL_TEXTURE_CUBE_MAP_POSITIVE_X, m_PathToRightTexture);
			LoadSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, m_PathToLeftTexture);
			LoadSide(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, m_PathToTopTexture);
			LoadSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, m_PathToBottomTexture);
			LoadSide(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, m_PathToFrontTexture);
			LoadSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, m_PathToBackTexture);

			// Specify wrapping and filtering methods.
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

			// Unbiding texture.
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

			// Setting flag for loaded.
			m_Loaded = true;
		}
	}

	// Using texture.
	void UseTexture()
	{
		std::cout << "Using texture: " << m_CubeMapTextureID << "\n";
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeMapTextureID);
	}
};
#endif