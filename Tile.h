#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Tile {
    int xPos;
    int yPos;
    int index;
    bool mine = false;
    bool flagged = false;
    bool revealed = false;
    int adjacentMines;
public:
    vector<Tile*> adjacentTiles;
    Tile();
    Tile(int xPos, int yPos, int index);
    Tile(const Tile &d);
    Tile &operator=(const Tile &d);
    void DrawTile(RenderWindow &window, Texture &tileTexture);
    void setMine();
    void destroyMine();
    bool isMine();
    void flag();
    void unFlag();
    bool isFlagged();
    void revealTile();
    void hideTile();
    bool isRevealed();
    int GetX();
    int GetY();
    int GetIndex();
    void setAdjacentMines();
    int GetAdjacentMines();
};
