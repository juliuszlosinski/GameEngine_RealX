#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


Texture::Texture() {
	this->textureID = 0;
	this->width = 0;
	this->height = 0;
	this->pathToBitmapFile = "";
}

Texture::Texture(std::string const& pathToBitmap) {
	this->textureID = 0;
	this->width = 0;
	this->height = 0;
	this->pathToBitmapFile = pathToBitmap.c_str();
}

int Texture::getTextureID() {
	return textureID;
}

int Texture::getWidth() {
	return width;
}

int Texture::getHeight() {
	return height;
}

int Texture::getBitDepth() {
	return bitDepth;
}

std::string Texture::getPathToBitmapFile() {
	return pathToBitmapFile;
}


bool Texture::LoadTexture() {
	unsigned char* data;
	data = stbi_load(this->pathToBitmapFile.c_str(), &width, &height, &bitDepth, 0);
	if (!data)
	{
		printf("Failed to find: %s\n", this->pathToBitmapFile);
		return false;
	}
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
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
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
	stbi_set_flip_vertically_on_load(true);
	return true;
}

bool Texture::LoadTexture(std::string const& pathToBitmap) {
	unsigned char* data;
	data = stbi_load(pathToBitmap.c_str(), &width, &height, &bitDepth, 0);
	if (!data)
	{
		printf("Failed to find: %s\n", pathToBitmap);
		return false;
	}
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
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
	this->pathToBitmapFile = pathToBitmap.c_str();
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

void Texture::UseTexture(int offsetID) {
	glActiveTexture(GL_TEXTURE0 + offsetID);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
}

// Loading side of cubemap.
void Texture::LoadSide(GLenum target, std::string pathToSide)
{
	int width, height, bitDepth;
	unsigned char* data;
	data = stbi_load(pathToSide.c_str(), &width, &height, &bitDepth, 0);
	if (!data)
	{
		std::cout << "Failed to find: " << pathToSide << std::endl;
	}
	else
	{
		glTexImage2D(target, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	stbi_image_free(data);
}