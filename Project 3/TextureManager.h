#pragma once
#include <SFML/Graphics.hpp>
#include<map>
#include<string>
using namespace std;

class TextureManager
{
	// static ensures that one and only one copy is ever in memory
	static map<string, sf::Texture> textures;
	static void LoadTexture(string textureName);
public:
	static const sf::Texture& GetTexture(string textureName); // Load and return an sf::Texture object
	static map<string, sf::Texture>& GetTextures(); // Returns the textures map
	static void Clear(); // call at end of main
};