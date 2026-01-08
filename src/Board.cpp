#include "Board.hpp"
#include "Piece.hpp"
#include "Tile.hpp"

Board::Board()
{
    tiles.resize(SIZE);
    for (int r = 0; r < SIZE; ++r)
    {
        tiles[r].reserve(SIZE);
        for (int c = 0; c < SIZE; ++c)
        {
            tiles[r].emplace_back(r, c);
        }
    }

    initBoard();
}

Tile &Board::getTile(int row, int col)
{
    return tiles[row][col];
}

void Board::initBoard()
{
    // Black
    for (int c = 0; c < SIZE; ++c) {
        Piece* pawn = new Piece(Piece::Type::Pawn, Piece::Color::Black);
        Tile& tile = getTile(1, c);

        tile.setPiece(pawn);
        pawn->setTile(&tile);
    }

    // White
    for (int c = 0; c < SIZE; ++c) {
        Piece* pawn = new Piece(Piece::Type::Pawn, Piece::Color::White);
        Tile& tile = getTile(6, c);

        tile.setPiece(pawn);
        pawn->setTile(&tile);
    }

    
}