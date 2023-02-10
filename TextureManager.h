#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <memory>

using namespace sf;
using namespace std;

/// <summary>
/// Contains all the textures that was loaded at least one time.
/// Make an easy and optimize way to access a texture.
/// </summary>
class TextureManager
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	TextureManager() = default;
	~TextureManager() = default;

	// GETTER

	/// <summary>
	/// Based on the path in parameter, if this path was already registered in the map, then return the texture associated with.
	/// Else, load the texture and return it after adding it to the map with his path as key.
	/// </summary>
	/// <param name="path">File path of the texture</param>
	/// <returns>Return the texture binded to this file path</returns>
	shared_ptr<Texture> GetTexture(const string& path);

private:

	/// <summary>
	/// Map of texture, contains a file path as Key and a shared_ptr of Texture as a Value.
	/// </summary>
	map<const string, shared_ptr<Texture>> mLoadedTextures;
};

