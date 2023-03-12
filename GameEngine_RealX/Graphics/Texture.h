#ifndef TEXTURE_H
#define TEXTURE_H

#include "glew.h"

#include <string>
#include <iostream>

class Texture {
private:
	GLuint textureID{};				// Texture ID.
	int width{};					// Width of texture image.
	int height{};					// Height of texture image.
	int bitDepth{};					// Bit depth of texture image.
	std::string pathToBitmapFile;	// Path to image (.png, .jpg).

public:
	// Getting texture id.
	int getTextureID();

	// Getting width of texture image.
	int getWidth();

	// Getting height of texture image.
	int getHeight();

	// Getting bit depth of texture image.
	int getBitDepth();

	// Getting path to image (.png, jpg).
	std::string getPathToBitmapFile();

	// Default constructor that creates empty pathToBitmapfile and other fields.
	Texture();					

	// Creating texture and saving the path to image (.png, .jpg).
	Texture(std::string const& pathToBitmap); 

	// Loading texture by using other path to image (.png, .jpg).
	bool LoadTexture(std::string const& pathToBitmap);

	// Loading texture by using current path to image (.png, .jpg).
	bool LoadTexture();

	// Using texture and setting offset (by default is 0).
	void UseTexture(int offsetID = 0);

protected:
	// Loading side.
	void LoadSide(GLenum target,std::string pathToSide);
};
#endif