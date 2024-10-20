#include "Tile.h"

Tile::Tile()
{
    xPos = 0;
    yPos = 0;
}
Tile::Tile(int xPos, int yPos, int index)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->index = index;
}
Tile::Tile(const Tile &d)
{
    this->xPos = d.xPos;
    this->yPos = d.yPos;
    this->index = d.index;
    this->mine = d.mine;
    this->flagged = d.mine;
    this->revealed = d.revealed;
    this->adjacentTiles = d.adjacentTiles;
    this->adjacentMines = d.adjacentMines;
}
Tile &Tile::operator=(const Tile &d)
{
    this->xPos = d.xPos;
    this->yPos = d.yPos;
    this->index = d.index;
    this->mine = d.mine;
    this->flagged = d.mine;
    this->revealed = d.revealed;
    this->adjacentTiles = d.adjacentTiles;
    this->adjacentMines = d.adjacentMines;
    return *this;
}
void Tile::DrawTile(RenderWindow &window, Texture &tileTexture)
{
    Sprite tile;
    tile.setTexture(tileTexture);
    tile.setPosition(Vector2f(xPos, yPos));
    window.draw(tile);
}
void Tile::setMine()
{
    mine = true;
}
void Tile::destroyMine()
{
    mine = false;
}
bool Tile::isMine()
{
    return mine;
}
void Tile::flag()
{
    flagged = true;
}
void Tile::unFlag()
{
    flagged = false;
}
bool Tile::isFlagged()
{
    return flagged;
}
void Tile::revealTile()
{
    revealed = true;
}
void Tile::hideTile()
{
    revealed = false;
}
bool Tile::isRevealed()
{
    return revealed;
}
int Tile::GetX()
{
    return xPos;
}
int Tile::GetY()
{
    return yPos;
}
int Tile::GetIndex()
{
    return index;
}
void Tile::setAdjacentMines()
{
    int mineCount;
    for (int i = 0; i < adjacentTiles.size(); ++i)
    {
        if (adjacentTiles.at(i)->isMine())
        {
            ++mineCount;
        }
    }
    adjacentMines = mineCount;
}
int Tile::GetAdjacentMines()
{
    return adjacentMines;
}
