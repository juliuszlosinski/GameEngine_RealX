#include "TexturesResourcesLoader.h"

std::map<std::string, Texture*>                TexturesResourcesLoader::loadedTextures;		  // Currently loaded meshes.
std::map<std::string, bool>                    TexturesResourcesLoader::loadedTexturesFLAGS;  // Flags if mesh is loaded.
std::map<std::multiset<std::string>, Cubemap*> TexturesResourcesLoader::loadedCubemaps;		  // Currently loaded cubemaps.
std::map<std::multiset<std::string>, bool>     TexturesResourcesLoader::loadedCubemapsFLAGS;  // Flags if cubemp is currently loaded

// Loading texture and getting reference to it.
Texture* TexturesResourcesLoader::LoadTexture(const std::string& path)
{
	// Checking if texture is already loaded.
	if (!loadedTexturesFLAGS[path])
	{
		// Loading a texture.
		Texture* texture;
		texture = new Texture(path);
		texture->LoadTexture();

		// Saving a new loaded texture.
		loadedTextures[path] = texture;

		// Setting up a flag fro a new loaded texture.
		loadedTexturesFLAGS[path] = true;

		std::cout << "looaded" << std::endl;
	}

	std::cout << "returning looaded texture" << std::endl;

	// Getting pointer to the texture.
	return loadedTextures[path];
}

// Loading cubemap and getting reference to it.
Cubemap* TexturesResourcesLoader::LoadCubemap
(
	const std::string& pathToRightRexture, const std::string& pathToLeftTexture,
	const std::string& pathToTopTexture, const std::string& pathToBottomTexture,
	const std::string& pathToBackTexture, const std::string& pathToFrontTexture
)
{
	std::multiset<std::string> paths =
	{
		pathToRightRexture, pathToLeftTexture,
		pathToTopTexture,pathToBottomTexture,
		pathToBackTexture,  pathToFrontTexture
	};
	if (!loadedCubemapsFLAGS[paths])
	{
		Cubemap* cubemap;
		cubemap = new Cubemap
		(
			pathToRightRexture, pathToLeftTexture,
			pathToTopTexture, pathToBottomTexture,
			pathToBackTexture, pathToFrontTexture
		);

		cubemap->LoadTexture();
		loadedCubemaps[paths] = cubemap;
		loadedCubemapsFLAGS[paths] = true;
	}
	return loadedCubemaps[paths];
}