#pragma once
#include <vector>

#include "Tile.hpp"

class Board
{
public:
    static constexpr int SIZE = 8;

    Board();
    Tile* getTile(int row, int col);

    Tile* enPassantTile;

    bool whiteCastleQueenSide  = true;
    bool whiteCastleKingSide = true;
    bool blackCastleQueenSide  = true;
    bool blackCastleKingSide = true;

private:
    std::vector<std::vector<Tile>> tiles;

    void initBoard();
};