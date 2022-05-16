#include <SFML/Graphics.hpp>
#include <iostream>
#include<map>
#include "Board.h"
#include "TextureManager.h"
#include "Tile.h"
using namespace std;
// committing a comment
// test 2

void DrawBoard(Board& board, sf::RenderWindow& window, map<string, sf::Sprite>& sprites);
void DrawMenu(Board& board, sf::RenderWindow& window, map<string, sf::Sprite>& sprites);
void DrawFace(Board& board, sf::RenderWindow& window, map<string, sf::Sprite>& sprites);
void StoreSprites(map<string, sf::Sprite>& sprites);
void StoreDigits(sf::Sprite& digits, map<string, sf::Sprite>& singleDigits);
void DrawDigits(Board& board, sf::RenderWindow& window, map<string, sf::Sprite>& digits);
void DrawAll(Board& board, sf::RenderWindow& window, map<string, sf::Sprite>& sprites, map<string, sf::Sprite >& digits);

void FlagFunction(Tile* currTile, Board& board);
void RevealTile(Tile* tile, Board& board);
Tile* CheckTileClick(Board& board, sf::RenderWindow& window, sf::Vector2f mousePos);
void DrawDebug(Tile* currTile, sf::RenderWindow& window, map<string, sf::Sprite>& sprites);
void RevealAllMines(Board& board, sf::RenderWindow& window, map<string, sf::Sprite>& sprites);
void FlagAllMines(Board& board, sf::RenderWindow& window, map<string, sf::Sprite>& sprites);

int main()
{
    Board board("boards/config.cfg");

    map<string, sf::Sprite> sprites;
    StoreSprites(sprites);

    map<string, sf::Sprite> singleDigits;
    StoreDigits(sprites.at("digits"), singleDigits);

    sf::RenderWindow window(sf::VideoMode(board.GetWindowWidth(), board.GetWindowHeight()), "Minesweeper");
    DrawAll(board, window, sprites, singleDigits);

    while (window.isOpen()) {

        sf::Event event;
        sf::Mouse mouse;

        // when the game is over
        while (board.GetGameStatus()) {
            while (window.pollEvent(event))
                if (event.type == sf::Event::Closed) {
                    window.close();
                    TextureManager::Clear();
                }

            sf::Vector2f mousePos((float)mouse.getPosition(window).x, (float)mouse.getPosition(window).y);

            if (mouse.isButtonPressed(mouse.Left)) {
                if (board.GetMenuArea()->getGlobalBounds().contains(mousePos)) {
                    // check for specific button
                    unsigned int i = 0;
                    for (; i < board.GetMenuButtons().size(); i++) {
                        if (board.GetMenuButtons()[i]->getGlobalBounds().contains(mousePos))
                            break;
                    }

                    switch (i)
                    {
                        // load test 1
                    case 1:
                    {
                       // Board testBoard("boards/testboard1.brd");
                        Board* testBoard = new Board("boards/testboard1.brd");
                        board = *testBoard;
                        delete testBoard;
                        board.SetGameStatus(false);
                        board.SetWinStatus(false);
                        DrawAll(board, window, sprites, singleDigits);
                        break;
                    }
                    // load test 2
                    case 2: {
                        Board* testBoard = new Board("boards/testboard2.brd");
                        board = *testBoard;
                        delete testBoard;
                        board.SetGameStatus(false);
                        board.SetWinStatus(false);
                        DrawAll(board, window, sprites, singleDigits);
                        break;
                    }
                          // load test 3
                    case 3: {
                        Board* testBoard = new Board("boards/testboard3.brd");
                        board = *testBoard;
                        delete testBoard;
                        board.SetGameStatus(false);
                        board.SetWinStatus(false);
                        DrawAll(board, window, sprites, singleDigits);
                        break;
                    }

                          // face Button, this functionality is optional
                    case 4: {
                        Board* testBoard = new Board("boards/config.cfg");
                        board = *testBoard;
                        delete testBoard;
                        board.SetGameStatus(false);
                        board.SetWinStatus(false);
                        DrawAll(board, window, sprites, singleDigits);
                        break;
                    }
                    default:
                        break;
                    }
                }
            }
        }

        while (window.pollEvent(event))
        {
            sf::Vector2f mousePos((float)mouse.getPosition(window).x, (float)mouse.getPosition(window).y);
            // check the type of the event...
            switch (event.type)
            {
            // window closed
            case sf::Event::Closed:
                window.close();
                TextureManager::Clear();
                break;

            // button pressed
            case sf::Event::MouseButtonPressed:
                if (mouse.isButtonPressed(mouse.Left)) {
                    if (board.GetBoardArea().getGlobalBounds().contains(mousePos)) {
                        Tile* clickedTile = CheckTileClick(board, window, mousePos);
                        RevealTile(clickedTile, board);

                        if (clickedTile->GetMine()) {
                            board.SetGameStatus(true);
                            board.SetWinStatus(false);
                            RevealAllMines(board, window, sprites);
                        }
                        else if (board.GetSafeTileCount() == 0) {
                            board.SetGameStatus(true);
                            board.SetWinStatus(true);
                            FlagAllMines(board, window, sprites);
                            if (board.GetDebug() == true)
                                board.SetDebug();
                        }

                        DrawAll(board, window, sprites, singleDigits);
                        break;
                    }
                    if (board.GetMenuArea()->getGlobalBounds().contains(mousePos)) {
                        // check for specific button
                        unsigned int i = 0;
                        for (; i < board.GetMenuButtons().size(); i++) {
                            if (board.GetMenuButtons()[i]->getGlobalBounds().contains(mousePos))
                                break;
                        }

                        switch (i)
                        {
                            // debug button
                        case 0:
                            board.SetDebug();
                            DrawAll(board, window, sprites, singleDigits);
                            break;

                            // load test 1
                        case 1:
                        {
                            Board* testBoard = new Board("boards/testboard1.brd");
                            board = *testBoard;
                            delete testBoard;
                            DrawAll(board, window, sprites, singleDigits);
                            break;
                        }
                            // load test 2
                        case 2: {
                            Board* testBoard = new Board("boards/testboard2.brd");
                            board = *testBoard;
                            delete testBoard;
                            DrawAll(board, window, sprites, singleDigits);
                            break;
                        }
                            // load test 3
                        case 3: {
                            Board* testBoard = new Board("boards/testboard3.brd");
                            board = *testBoard;
                            delete testBoard;
                            DrawAll(board, window, sprites, singleDigits);
                            break;
                        }

                            // face Button, this functionality is optional
                        case 4: {
                            Board* testBoard = new Board("boards/config.cfg");
                            board = *testBoard;
                            delete testBoard;
                            DrawAll(board, window, sprites, singleDigits);
                            break;
                        }
                        default:
                            break;
                        }
                    }
                }
                if (mouse.isButtonPressed(mouse.Right)) {
                    // place flag
                    // get the position of the mouse
                    // find a tile that contains the mouse coordinates
                    FlagFunction(CheckTileClick(board, window, mousePos), board);

                    DrawAll(board, window, sprites, singleDigits);
                    break;
                }

            // we don't process other types of events
            default:
                break;
            }
        }
    }
    return 0;
}

void StoreSprites(map<string, sf::Sprite>& sprites) {
    sf::Sprite debug(TextureManager::GetTexture("debug"));
    sf::Sprite digits(TextureManager::GetTexture("digits"));
    sf::Sprite face_happy(TextureManager::GetTexture("face_happy"));
    sf::Sprite face_lose(TextureManager::GetTexture("face_lose"));
    sf::Sprite face_win(TextureManager::GetTexture("face_win"));
    sf::Sprite flag(TextureManager::GetTexture("flag"));
    sf::Sprite mine(TextureManager::GetTexture("mine"));
    sf::Sprite number_1(TextureManager::GetTexture("number_1"));
    sf::Sprite number_2(TextureManager::GetTexture("number_2"));
    sf::Sprite number_3(TextureManager::GetTexture("number_3"));
    sf::Sprite number_4(TextureManager::GetTexture("number_4"));
    sf::Sprite number_5(TextureManager::GetTexture("number_5"));
    sf::Sprite number_6(TextureManager::GetTexture("number_6"));
    sf::Sprite number_7(TextureManager::GetTexture("number_7"));
    sf::Sprite number_8(TextureManager::GetTexture("number_8"));
    sf::Sprite test_1(TextureManager::GetTexture("test_1"));
    sf::Sprite test_2(TextureManager::GetTexture("test_2"));
    sf::Sprite test_3(TextureManager::GetTexture("test_3"));
    sf::Sprite tile_hidden(TextureManager::GetTexture("tile_hidden"));
    sf::Sprite tile_revealed(TextureManager::GetTexture("tile_revealed"));

    sprites.emplace("debug", debug);
    sprites.emplace("digits", digits);
    sprites.emplace("face_happy", face_happy);
    sprites.emplace("face_lose", face_lose);
    sprites.emplace("face_win", face_win);
    sprites.emplace("flag", flag);
    sprites.emplace("mine", mine);
    sprites.emplace("number_1", number_1);
    sprites.emplace("number_2", number_2);
    sprites.emplace("number_3", number_3);
    sprites.emplace("number_4", number_4);
    sprites.emplace("number_5", number_5);
    sprites.emplace("number_6", number_6);
    sprites.emplace("number_7", number_7);
    sprites.emplace("number_8", number_8);
    sprites.emplace("test_1", test_1);
    sprites.emplace("test_2", test_2);
    sprites.emplace("test_3", test_3);
    sprites.emplace("tile_hidden", tile_hidden);
    sprites.emplace("tile_revealed", tile_revealed);
}
void StoreDigits(sf::Sprite& digits, map<string, sf::Sprite>& singleDigits) {
    unsigned int leftStart = 0;
    unsigned int topStart = 0;
    unsigned int width = 21;
    unsigned int height = 32;

    // When the specific digit is empty
    sf::IntRect firstRect(leftStart, topStart, width, height);
    digits.setTextureRect(firstRect);
    singleDigits.emplace("", digits);
    
    // when the digits exist
    for (unsigned int i = 0; i < 10; i++) {
        sf::IntRect newRect(leftStart, topStart, width, height);
        digits.setTextureRect(newRect);
        singleDigits.emplace(to_string(i), digits);
        
        leftStart += width;
    }

    // when there is a negative value
    sf::IntRect finalRect(leftStart, topStart, width, height);
    digits.setTextureRect(finalRect);
    singleDigits.emplace("-", digits);
}
void DrawBoard(Board& board, sf::RenderWindow& window, map<string, sf::Sprite>& sprites) {
    for (unsigned int x = 0; x < board.GetWidth(); x++) {
        for (unsigned int y = 0; y < board.GetHeight(); y++) {
            Tile* currTile = board.GetTiles()[x][y];

            // Base case tile is already revealed no need to draw anymore for this currTile
            // order of images: background, (bomb or number)
            if (currTile->GetRevealed()) {
                sprites.at(currTile->GetBackgroundSprite()).setPosition(currTile->GetPosition());
                window.draw(sprites.at(currTile->GetBackgroundSprite()));

                sprites.at(currTile->GetRevealedSprite()).setPosition(currTile->GetPosition());
                window.draw(sprites.at(currTile->GetRevealedSprite()));
                continue;
            }
            // Normal case: tile is not revealed
            // order of images from back to front: tile_empty, (bomb or number), tile_hidden, flag
            sprites.at("tile_hidden").setPosition(board.GetTiles()[x][y]->GetPosition());
            window.draw(sprites.at("tile_hidden"));
            if (currTile->GetFlag()) {
                sprites.at("flag").setPosition(currTile->GetPosition());
                window.draw(sprites.at("flag"));
            }

            // board.GetDebug()
            if (board.GetDebug())
                DrawDebug(currTile, window, sprites);
        }
    }
}
void DrawMenu(Board& board, sf::RenderWindow& window, map<string, sf::Sprite>& sprites) {
    // drawing the smiley face
    sprites.at("debug").setPosition(board.GetMenuButtons()[0]->getPosition());
    window.draw(sprites.at("debug"));    

    DrawFace(board, window, sprites);

    for (unsigned int i = 1; i < board.GetMenuButtons().size() - 1; i++) {
        string fileName = "test_" + to_string(i);
        sprites.at(fileName).setPosition(board.GetMenuButtons()[i]->getPosition());
        window.draw(sprites.at(fileName));
    }
}
void DrawDigits(Board& board, sf::RenderWindow& window, map<string, sf::Sprite>& digits) {

    // convert int to string
    string number = to_string(board.GetMineCount() - board.GetFlagCount());
    bool isNeg = false;

    // find if the output is negative
    if (board.GetMineCount() - board.GetFlagCount() < 0)
        isNeg = true;
   
    // break string into substrings, and store in numbers container
    vector<string> numbers;
    for (int i = 0; i < number.size(); i++) {
        string tempString = number.substr(i, 1);
        numbers.push_back(tempString);
    }

    // set positions for each digit and draw it

    // Check if negative, if so draw the negative sign immediately 
    if (isNeg) {
        digits.at("-").setPosition(0, (float)board.GetWindowHeight() - 100);
        window.draw(digits.at("-"));
        numbers.erase(numbers.begin());
    }

    // will literally place 0's in front of the number
    // ex. 52 == 052, 1 == 001
    if (numbers.size() < 3) {
        unsigned int i = 0;
        for (; i < 3 - numbers.size(); i++) {
            digits.at("0").setPosition(21 * ((float)i + 1), (float)board.GetWindowHeight() - 100);
            window.draw(digits.at("0"));
        }
        
        // will literally place the actual number after all of the zeros
        for (unsigned int j = 0; j < numbers.size(); j++) {
            digits.at(numbers.at(j)).setPosition(21 * ((float)i + (float)j + 1), (float)board.GetWindowHeight() - 100);
            window.draw(digits.at(numbers.at(j)));
        }
    }
    else { // If there the number is 532 we will output 532 without any 0's in front of it
        for (unsigned int i = 0; i < numbers.size(); i++) {
            digits.at(numbers.at(i)).setPosition(21 * ((float)i + 1), (float)board.GetWindowHeight() - 100);
            window.draw(digits.at(numbers.at(i)));
        }
    }
}
void DrawAll(Board& board, sf::RenderWindow& window, map<string, sf::Sprite>& sprites, map<string, sf::Sprite>& digits) {
    window.clear(sf::Color::White);
    DrawBoard(board, window, sprites);
    DrawMenu(board, window, sprites);
    DrawDigits(board, window, digits);
    window.display();
}

void FlagFunction(Tile* currTile, Board& board) {
    
    if (currTile == nullptr || currTile->GetRevealed())
        return;

    // If the game has been won
    if (board.GetWinStatus()) {
        if (!currTile->GetFlag()) {
            currTile->SetFlag(true);
            board.IncrementFlagCount();
        }
        return;
    }

    // if the game is still ongoing
    if (!currTile->GetFlag()) {
        currTile->SetFlag(true); // this specific tile's hasFlag will become true
        board.IncrementFlagCount();
    }
    else if (currTile->GetFlag()) {
        currTile->SetFlag(false);
        board.DecrementFlagCount();
    }
}

// Work by recursion
void RevealTile(Tile* tile, Board& board) {
    // base cases
        // It is a mine
        // it is flagged
        // Tile already revealed
        // tile being revealed is not empty
    if (tile == nullptr)
        return;
    if (tile->GetFlag())
        return;
    if (tile->GetRevealed())
        return;
    if (tile->GetMine()) {
        tile->SetRevealedState(true);
        tile->SetRevealedSprite();
        return;
    }

    tile->SetRevealedState(true);
    tile->SetRevealedSprite();
    board.DecrementSafeTileCount();

    if (tile->GetRevealedSprite() != tile->GetBackgroundSprite()) {
        return;
    }

    // recursion case
    for (unsigned int i = 0; i < tile->GetAdjacentTiles().size(); i++)
        RevealTile(tile->GetAdjacentTiles()[i], board);
}

Tile* CheckTileClick(Board& board, sf::RenderWindow& window, sf::Vector2f mousePos) {
    for (unsigned int x = 0; x < board.GetWidth(); x++) {
        for (unsigned int y = 0; y < board.GetHeight(); y++) {
            Tile* currTile = board.GetTiles()[x][y];

            if (currTile->GetTileRectangle().getGlobalBounds().contains(mousePos))
                return currTile;
        }
    }
    return nullptr;
}

void DrawDebug(Tile* currTile, sf::RenderWindow& window, map<string, sf::Sprite>& sprites) {
    if (currTile->GetMine()) {
        sprites.at(currTile->GetRevealedSprite()).setPosition(currTile->GetPosition());
        window.draw(sprites.at(currTile->GetRevealedSprite()));
    }
}

void RevealAllMines(Board& board, sf::RenderWindow& window, map<string, sf::Sprite>& sprites) {
    for (unsigned int x = 0; x < board.GetWidth(); x++) {
        for (unsigned int y = 0; y < board.GetHeight(); y++) {
            Tile* currTile = board.GetTiles()[x][y];

            // if the current tile has a mine

            if (currTile->GetMine()) {
                if (currTile->GetFlag())
                    currTile->SetFlag(false);
                RevealTile(currTile, board);
            }
        }
    }
}

void FlagAllMines(Board& board, sf::RenderWindow& window, map<string, sf::Sprite>& sprites) {
    for (unsigned int x = 0; x < board.GetWidth(); x++) {
        for (unsigned int y = 0; y < board.GetHeight(); y++) {
            Tile* currTile = board.GetTiles()[x][y];
            FlagFunction(currTile, board);
        }
    }
}

void DrawFace(Board& board, sf::RenderWindow& window, map<string, sf::Sprite>& sprites) {
    if (!board.GetGameStatus()) { // game is not over yet
        sprites.at("face_happy").setPosition(board.GetMenuButtons()[4]->getPosition());
        window.draw(sprites.at("face_happy"));
    }
    else { // game is over
        if (board.GetWinStatus()) {
            sprites.at("face_win").setPosition(board.GetMenuButtons()[4]->getPosition());
            window.draw(sprites.at("face_win"));
        }
        else {
            sprites.at("face_lose").setPosition(board.GetMenuButtons()[4]->getPosition());
            window.draw(sprites.at("face_lose"));
        }
    }
}