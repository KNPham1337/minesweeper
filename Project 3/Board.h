#pragma once
#include "Tile.h"
#include <fstream>
#include "TextureManager.h"
#include <vector>
#include <map>
class Board
{
private:
	// Gameplay Area
	unsigned int _width = 0;
	unsigned int _height = 0;
	unsigned int _tileCount = 0; // width * height without multiplication of 32 and adding 100
	int _mineCount = 0;
	int _flagCount = 0;
	sf::RectangleShape boardArea;
	vector<vector<Tile*>> _listOfTiles;

	// Menu
	bool debug = false;
	sf::RectangleShape menuArea;
	sf::RectangleShape faceButton;;
	sf::RectangleShape debugButton;
	sf::RectangleShape test1Button;
	sf::RectangleShape test2Button;
	sf::RectangleShape test3Button;
	vector<sf::RectangleShape*> menuButtons = {&debugButton, &test1Button, &test2Button, &test3Button, &faceButton};

	// Window
	unsigned int _windowWidth = 0; // multiply width by 32
	unsigned int _windowHeight = 0; // multiply by 32 and add 100

	// Internal
	bool isWon = false;
	bool isGameOver = false;
	unsigned int safeTileCount = 0;

public:
	Board(string name);
	Board& operator=(const Board& otherBoard);
	~Board();
	unsigned int GetWidth();
	unsigned int GetHeight();
	int GetMineCount();
	int GetFlagCount();
	unsigned int GetTileCount();
	unsigned int GetWindowWidth();
	unsigned int GetWindowHeight();
	vector<vector<Tile*>>& GetTiles();
	bool GetDebug();

	void IncrementFlagCount();
	void DecrementFlagCount();
	void SetDebug();
	sf::RectangleShape GetBoardArea();
	void Resize2dVector();
	void Populate2dVector();
	void PlaceMinesRandomly();

	// Menu
	sf::RectangleShape* GetMenuArea();
	vector<sf::RectangleShape*>& GetMenuButtons();

	void SetMenuArea();
	void SetMenuButtons();

	void SetWinStatus(bool state);
	void SetGameStatus(bool state);
	bool GetWinStatus();
	bool GetGameStatus();

	void IncrementSafeTileCount();
	void DecrementSafeTileCount();

	unsigned int GetSafeTileCount();
};