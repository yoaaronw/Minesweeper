#pragma once
#include "Tile.h"
#include "StoreTextures.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace chrono;
using namespace sf;

class Board {
    int cols;
    int rows;
    int numTiles;
    int numMines;
    vector<int> mineTiles;
    vector<Tile> tiles;
    StoreTextures textures;
    map<string, Sprite> sprites;
public:
    Board();
    Board(int cols, int rows, int numMines);
    void InitializeTextures();
    void InitializeSprites();
    void CreateTiles();
    bool TileIsAdjacent(Tile mainTile, Tile tile2);
    void SetAdjacentTiles();
    void DrawBoard(RenderWindow &window);
    void DrawSprite(RenderWindow &window, string name);
    bool MouseOverButton(string buttonName, RenderWindow &window);
    int SelectedTileIndex(int xMousePos, int yMousePos);
    void FlagUnFlagTile(RenderWindow &window);
    int numFlags();
    void RevealTiles(int selectedIndex);
    bool MineHit(RenderWindow &window);
    void DrawMines(RenderWindow &window);
    void FlagMines();
    void PausedBoard(RenderWindow &window);
    void DebugMode(RenderWindow &window);
    void MineCounter(RenderWindow &window, int mineCount);
    void Timer(RenderWindow &window, duration<long long, ratio<1, 1000000000>> time);
    void ResetBoard();
    bool GameWon();
};
