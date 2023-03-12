#ifndef TEXTURES_RESOURCES_LOADER_H
#define TEXTURES_RESOURCES_LOADER_H

#include "Texture.h"
#include "Cubemap.h"
#include <map>
#include <set>

class TexturesResourcesLoader
{
private:
	static std::map<std::string, Texture*>  loadedTextures;					 // Currently loaded textures.
	static std::map<std::string, bool> loadedTexturesFLAGS;					 // Flags if textures is loaded.
	static std::map<std::multiset<std::string>, Cubemap*> loadedCubemaps;	 // Currently loaded cubemaps.
	static std::map<std::multiset<std::string>, bool> loadedCubemapsFLAGS;	 // Flags if cubemp is currently loaded.

public:
	// Loading texture and getting reference to it.
	static Texture* LoadTexture(const std::string& path);

	// Loading cubemap and getting reference to it.
	static Cubemap* LoadCubemap
	(
		const std::string& pathToRightRexture, const std::string& pathToLeftTexture,
		const std::string& pathToTopTexture, const std::string& pathToBottomTexture,
		const std::string& pathToBackTexture, const std::string& pathToFrontTexture
	);
};
#endif
