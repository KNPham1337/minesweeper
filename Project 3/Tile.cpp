#include "Tile.h"
#include <iostream>

sf::Vector2f Tile::GetPosition()
{
    return position;
}

Tile::Tile(unsigned int x, unsigned int y) {
    hasFlag = false;
    hasMine = false; 
    isRevealed = false;
    position.x = x * 32;
    position.y = y * 32;
}

Tile& Tile::operator=(const Tile& otherTile) {
    hasMine = otherTile.hasMine;
    hasFlag = otherTile.hasFlag;
    isRevealed = otherTile.isRevealed;
    position = otherTile.position;
    revealedSprite = otherTile.revealedSprite;
    tileRectangle = otherTile.tileRectangle; 
    // set adjacent tiles in the board operator=

    return *this;
}

Tile::~Tile() {
    
}

bool Tile::GetMine()
{
    return hasMine;
}

bool Tile::GetFlag()
{
    return hasFlag;
}

bool Tile::GetRevealed() {
    return isRevealed;
}

string Tile::GetBackgroundSprite()
{
    return backgroundSprite;
}

string Tile::GetRevealedSprite()
{
    return revealedSprite;
}

void Tile::SetMine()
{
    hasMine = true;
}

vector<Tile*>& Tile::GetAdjacentTiles()
{
    return adjacentTiles;
}

void Tile::SetAdjacentTiles(vector<vector<Tile*>>& tiles, unsigned int x, unsigned int y)
{
    unsigned int height = tiles.at(x).size();
    unsigned int width = tiles.size();
    
    // x - 1, y -1; utilizing the fact that unsigned underflows
    if (x - 1 < width && y - 1 < height)
        adjacentTiles.push_back(tiles[x - 1][y - 1]);
    // x + 1, y + 1
    if (x + 1 < width && y + 1 < height)
        adjacentTiles.push_back(tiles[x + 1][y + 1]);
    // x - 1, y + 1
    if (x - 1 < width && y + 1 < height)
        adjacentTiles.push_back(tiles[x - 1][y + 1]);
    // x + 1, y - 1
    if (x + 1 < width && y - 1 < height)
        adjacentTiles.push_back(tiles[x + 1][y - 1]);

    // x - 1
    if (x - 1 < width)
        adjacentTiles.push_back(tiles[x - 1][y]);
    // x + 1
    if (x + 1 < width)
        adjacentTiles.push_back(tiles[x + 1][y]);
    // y - 1
    if (y - 1 < height)
        adjacentTiles.push_back(tiles[x][y - 1]);
    // y + 1
    if (y + 1 < height)
        adjacentTiles.push_back(tiles[x][y + 1]);
}

void Tile::SetRevealedSprite() {
    // tiles with mines already have the correct sprite
    if (hasMine) {
        revealedSprite = "mine";
        return;
    }
    
    // check for how many mines are nearby
    unsigned int totalNearbyMines = 0;
    for (unsigned int i = 0; i < adjacentTiles.size(); i++) {
        if (adjacentTiles.at(i)->hasMine)
            totalNearbyMines++;
    }

    // tiles are made with tile_revealed sprites by default
    if (totalNearbyMines == 0) {
        revealedSprite = backgroundSprite;
        return;
    }

    // Set the number to appear when the tile is revealed
    string numberOfMines = "number_" + to_string(totalNearbyMines);
    revealedSprite = numberOfMines;
}

sf::RectangleShape& Tile::GetTileRectangle() {
    return tileRectangle;
}

void Tile::SetFlag(bool flag)
{
    hasFlag = flag;
}

void Tile::SetRevealedState(bool state)
{
    isRevealed = state;
}
