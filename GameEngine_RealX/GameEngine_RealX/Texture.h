
#ifndef GLEW_H
#define GLEW_H
#include "glew.h"
#endif 

#ifndef STRING_H
#define STRING_H
#include <string>
#endif

#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif

class Texture {
private:
	GLuint textureID{};
	int width{};
	int height{};
	int bitDepth{};
	std::string pathToBitmapFile;

public:
	Texture();

	Texture(std::string const& pathToBitmap);

	int getTextureID();

	int getWidth();

	int getHeight();

	int getBitDepth();

	std::string getPathToBitmapFile();

	void LoadTexture(std::string const& pathToBitmap);

	void UseTexture();
};

