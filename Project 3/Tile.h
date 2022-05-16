#pragma once
#include <vector>
#include<SFML/Graphics.hpp>
#include "Random.h"
#include "TextureManager.h"
using namespace std;
class Tile
{
private:
	bool hasMine;
	bool hasFlag = false;
	bool isRevealed = false;
	sf::Vector2f position;
	string revealedSprite; // can either be a mine or a number
	const string backgroundSprite = "tile_revealed"; // is the default empty tile
	sf::RectangleShape tileRectangle; // holds the area of the sprite for use in determining mouse clicks
	vector<Tile*> adjacentTiles; // a list of nearby mines, used to calculate the number of nearby mines

public:
	Tile(unsigned int x, unsigned int y);
	~Tile();
	bool GetMine();
	bool GetFlag();
	bool GetRevealed();
	sf::Vector2f GetPosition();
	vector<Tile*>& GetAdjacentTiles();
	string GetBackgroundSprite();
	string GetRevealedSprite();
	sf::RectangleShape& GetTileRectangle();
	Tile& operator=(const Tile& otherTile);


	void SetAdjacentTiles(vector<vector<Tile*>>& tiles, unsigned int x, unsigned int y);
	void SetMine();
	void SetRevealedSprite();
	void SetFlag(bool flag);
	void SetRevealedState(bool state);
};