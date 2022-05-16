#include<iostream>

#include "Board.h"

// Read the config file
Board::Board(string name) {
	fstream ifile(name);
	string extension;

	size_t index = name.find_last_of('.');
	extension = name.substr(index + 1);

	// find the extension of the file
	if (ifile.is_open()) {
		if (extension == "cfg") {
			ifile >> _width;
			ifile >> _height;
			ifile >> _mineCount;

			Resize2dVector();
			Populate2dVector();
			PlaceMinesRandomly();
		}
		else if (extension == "brd") {
			string line;

			while (getline(ifile, line)) {
				_width = (unsigned int)line.size();
				_height++;
			}

			Resize2dVector();
			Populate2dVector();

			// Mine detection
			ifile.clear();
			ifile.seekg(0, ios::beg);
			int tempHeight = 0;
			while (getline(ifile, line)) {
				for (unsigned int x = 0; x < _width; x++)
					if (line[x] == '1') {
						_listOfTiles[x][tempHeight]->SetMine();
						_mineCount++;
					}
				tempHeight++;
			}
		}

		// Set adjacent values
		for (unsigned int y = 0; y < _height; y++) {
			for (unsigned int x = 0; x < _width; x++) {
				_listOfTiles[x][y]->SetAdjacentTiles(_listOfTiles, x, y);
			}
		}

		// transform values to represent window size
		_windowWidth = _width * 32;
		_windowHeight = (_height * 32) + 100;

		sf::Vector2f boardSize(float(_windowWidth), (float)_windowHeight - 100);
		boardArea.setSize(boardSize);

		for (unsigned int y = 0; y < _height; y++) {
			for (unsigned int x = 0; x < _width; x++) {
				_listOfTiles[x][y]->SetRevealedSprite();
			}
		}

		_tileCount = _width * _height;
		safeTileCount = _tileCount - _mineCount;
		SetMenuArea();
		SetMenuButtons();

		ifile.close();
	}
}

// Assigning values from otherBoard to this board
Board& Board::operator=(const Board& otherBoard) {
	// Gameplay Area
	_width = otherBoard._width;
	_height = otherBoard._height;
	_tileCount = otherBoard._tileCount; 
	_mineCount = otherBoard._mineCount;
	_flagCount = otherBoard._flagCount;
	boardArea = otherBoard.boardArea;
	isGameOver = false;
	isWon = false;
	safeTileCount = otherBoard.safeTileCount;

	// Menu
	menuArea = otherBoard.menuArea;
	faceButton = otherBoard.faceButton;
	debugButton = otherBoard.debugButton;
	test1Button = otherBoard.test1Button;
	test2Button = otherBoard.test2Button;
	test3Button = otherBoard.test3Button;

	// Window
	_windowWidth = otherBoard._windowWidth;
	_windowHeight = otherBoard._windowHeight;
	SetMenuArea();
	SetMenuButtons();
	Resize2dVector();

	// Get the tiles from other into this
	for (unsigned int x = 0; x < _width; x++)
		for (unsigned int y = 0; y < _height; y++) {
			delete _listOfTiles[x][y];
			_listOfTiles[x][y] = new Tile(x, y);
			// REMEMBER TO ACTUALLY CHANGE THE VALUES AND NOT JUST ASSIGN POINTERS TO POINTERS
			*_listOfTiles[x][y] = *otherBoard._listOfTiles[x][y];
		}

	// Set the adjacent tiles once all tiles have been transferred
	for (unsigned int x = 0; x < _width; x++)
		for (unsigned int y = 0; y < _height; y++)
			_listOfTiles[x][y]->SetAdjacentTiles(_listOfTiles, x, y);

	return *this;
}

Board::~Board() {
	for (unsigned int x = 0; x < _width; x++) {
		for (unsigned int y = 0; y < _height; y++)
			delete _listOfTiles[x][y];
	}
}

unsigned int Board::GetWidth()
{
	return _width;
}

unsigned int Board::GetHeight()
{
	return _height;
}

int Board::GetMineCount()
{
	return _mineCount;
}

int Board::GetFlagCount() {
	return _flagCount;
}

unsigned int Board::GetTileCount()
{
	return _tileCount;
}

unsigned int Board::GetWindowWidth()
{
	return _windowWidth;
}

unsigned int Board::GetWindowHeight()
{
	return _windowHeight;
}

vector<vector<Tile*>>& Board::GetTiles()
{
	return _listOfTiles;
}

void Board::IncrementFlagCount() {
	_flagCount++;
}

void Board::DecrementFlagCount()
{
	_flagCount--;
}

bool Board::GetDebug() {
	return debug;
}

void Board::SetDebug() {
	debug = !debug;
}

sf::RectangleShape Board::GetBoardArea()
{
	return boardArea;
}

void Board::Resize2dVector() {
	// resize the 2d vector
	_listOfTiles.resize(_width);
	for (unsigned int i = 0; i < _width; i++)
		_listOfTiles.at(i).resize(_height);
}

void Board::Populate2dVector() {
	// fill 2d vector with tiles
	for (unsigned int y = 0; y < _height; y++) {
		for (unsigned int x = 0; x < _width; x++) {
			_listOfTiles[x][y] = new Tile(x, y);

			_listOfTiles[x][y]->GetTileRectangle().setPosition(_listOfTiles[x][y]->GetPosition());
			_listOfTiles[x][y]->GetTileRectangle().setSize(sf::Vector2f(32.f, 32.f));
		}
	}
}

void Board::PlaceMinesRandomly() {
	// Randomize mine placement
	unsigned int numOfMines = 0;
	while (numOfMines != _mineCount) {
		unsigned int x = Random::Int(0, _width - 1);
		unsigned int y = Random::Int(0, _height - 1);

		// mine already exists
		if (_listOfTiles[x][y]->GetMine())
			continue;

		// mine does not exist
		_listOfTiles[x][y]->SetMine();
		numOfMines++;
	}
}

// MENU
sf::RectangleShape* Board::GetMenuArea() {
	return &menuArea;
}
vector<sf::RectangleShape*>& Board::GetMenuButtons() {
	return menuButtons;
}

void Board::SetMenuArea() {
	sf::Vector2f menuMiddle;
	menuMiddle.x = ((float)_windowWidth / 2) - 32;
	menuMiddle.y = (float)_windowHeight - 100;

	sf::Vector2f menuSize((float)_windowWidth, (float)100);
	menuArea.setPosition(menuMiddle);
	menuArea.setSize(menuSize);
}

void Board::SetMenuButtons() {
	sf::Vector2f menuMiddle;
	menuMiddle.x = ((float)_windowWidth / 2) - 32;
	menuMiddle.y = (float)_windowHeight - 100;
	sf::Vector2f buttonSize((float)64, (float)64);

	faceButton.setPosition(menuMiddle);
	faceButton.setSize(buttonSize);
	
	debugButton.setPosition(menuMiddle.x + 64 + 64, menuMiddle.y);
	debugButton.setSize(buttonSize);
	// set textures for the 3 test board buttons
	for (unsigned int i = 1; i < menuButtons.size() - 1; i++) {
		menuButtons[i]->setPosition(menuMiddle.x + (64 * (i + 2)), menuMiddle.y);
		menuButtons[i]->setSize(buttonSize);
	}
}

void Board::SetWinStatus(bool state)
{
	isWon = state;
}

void Board::SetGameStatus(bool state) {
	isGameOver = state;
}

bool Board::GetWinStatus() {
	return isWon;
}

bool Board::GetGameStatus() {
	return isGameOver;
}

void Board::IncrementSafeTileCount()
{
	safeTileCount++;
}

void Board::DecrementSafeTileCount() {
	if (safeTileCount == 0)
		return;
	else
		safeTileCount--;
}

unsigned int Board::GetSafeTileCount() {
	return safeTileCount;
}