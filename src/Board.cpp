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

Tile* Board::getTile(int row, int col)
{
    if (row >= SIZE || col >= SIZE || row < 0 || col < 0) {
        return nullptr;
    }

    return &tiles[row][col];
}

void Board::initBoard()
{
    // Black pieces
    for (int c = 0; c < SIZE; ++c)
    {
        Piece *pawn = new Piece(Piece::Type::Pawn, Piece::Color::Black);
        Tile* tile = getTile(1, c);
        tile->setPiece(pawn);
        pawn->setTile(tile);
    }

    Piece *bRook1 = new Piece(Piece::Type::Rook, Piece::Color::Black);
    Piece *bKnight1 = new Piece(Piece::Type::Knight, Piece::Color::Black);
    Piece *bBishop1 = new Piece(Piece::Type::Bishop, Piece::Color::Black);
    Piece *bQueen = new Piece(Piece::Type::Queen, Piece::Color::Black);
    Piece *bKing = new Piece(Piece::Type::King, Piece::Color::Black);
    Piece *bBishop2 = new Piece(Piece::Type::Bishop, Piece::Color::Black);
    Piece *bKnight2 = new Piece(Piece::Type::Knight, Piece::Color::Black);
    Piece *bRook2 = new Piece(Piece::Type::Rook, Piece::Color::Black);

    Tile* bRow = getTile(0, 0);
    bRow->setPiece(bRook1);
    bRook1->setTile(bRow);
    getTile(0, 1)->setPiece(bKnight1);
    bKnight1->setTile(getTile(0, 1));
    getTile(0, 2)->setPiece(bBishop1);
    bBishop1->setTile(getTile(0, 2));
    getTile(0, 3)->setPiece(bQueen);
    bQueen->setTile(getTile(0, 3));
    getTile(0, 4)->setPiece(bKing);
    bKing->setTile(getTile(0, 4));
    getTile(0, 5)->setPiece(bBishop2);
    bBishop2->setTile(getTile(0, 5));
    getTile(0, 6)->setPiece(bKnight2);
    bKnight2->setTile(getTile(0, 6));
    getTile(0, 7)->setPiece(bRook2);
    bRook2->setTile(getTile(0, 7));

    // White
    for (int c = 0; c < SIZE; ++c)
    {
        Piece *pawn = new Piece(Piece::Type::Pawn, Piece::Color::White);
        Tile* tile = getTile(6, c);
        tile->setPiece(pawn);
        pawn->setTile(tile);
    }

    Piece *wRook1 = new Piece(Piece::Type::Rook, Piece::Color::White);
    Piece *wKnight1 = new Piece(Piece::Type::Knight, Piece::Color::White);
    Piece *wBishop1 = new Piece(Piece::Type::Bishop, Piece::Color::White);
    Piece *wQueen = new Piece(Piece::Type::Queen, Piece::Color::White);
    Piece *wKing = new Piece(Piece::Type::King, Piece::Color::White);
    Piece *wBishop2 = new Piece(Piece::Type::Bishop, Piece::Color::White);
    Piece *wKnight2 = new Piece(Piece::Type::Knight, Piece::Color::White);
    Piece *wRook2 = new Piece(Piece::Type::Rook, Piece::Color::White);

    Tile* wRow = getTile(7, 0);
    wRow->setPiece(wRook1);
    wRook1->setTile(wRow);
    getTile(7, 1)->setPiece(wKnight1);
    wKnight1->setTile(getTile(7, 1));
    getTile(7, 2)->setPiece(wBishop1);
    wBishop1->setTile(getTile(7, 2));
    getTile(7, 3)->setPiece(wQueen);
    wQueen->setTile(getTile(7, 3));
    getTile(7, 4)->setPiece(wKing);
    wKing->setTile(getTile(7, 4));
    getTile(7, 5)->setPiece(wBishop2);
    wBishop2->setTile(getTile(7, 5));
    getTile(7, 6)->setPiece(wKnight2);
    wKnight2->setTile(getTile(7, 6));
    getTile(7, 7)->setPiece(wRook2);
    wRook2->setTile(getTile(7, 7));
}