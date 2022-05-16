#include "TextureManager.h"

// redeclare variable so file knows it exists
map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName) {
	string path = "images/";
	path += fileName + ".png";

	textures[fileName].loadFromFile(path);
}

const sf::Texture& TextureManager::GetTexture(string textureName) {
	
	if (textures.find(textureName) == textures.end())
		LoadTexture(textureName);
	
	return textures[textureName];
}

map<string, sf::Texture>& TextureManager::GetTextures()
{
	return textures;
}

void TextureManager::Clear() {
	textures.clear();
}