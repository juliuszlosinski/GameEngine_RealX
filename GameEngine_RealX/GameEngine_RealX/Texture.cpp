#ifndef TEXTURE_H
#define TEXTURE_H
#include "Texture.h"
#endif

#ifndef STB_H
#define STB_H
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif


Texture::Texture() {
	this->textureID = 0;
	this->width = 0;
	this->height = 0;
	this->pathToBitmapFile = "";
}

Texture::Texture(std::string const& pathToBitmap) {
	LoadTexture(pathToBitmap);
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

void Texture::LoadTexture(std::string const& pathToBitmap) {
	unsigned char* data;
	data = stbi_load(pathToBitmap.c_str(), &width, &height, &bitDepth, 0);
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
	stbi_image_free(data);
	stbi_set_flip_vertically_on_load(true);
	this->pathToBitmapFile = pathToBitmap.c_str();
}

void Texture::UseTexture() {
	glBindTexture(GL_TEXTURE_2D, this->textureID);
}