#pragma once
#include <vector>

#include "Board.hpp"

class Tile;

class Piece
{
public:
    enum class Type
    {
        Pawn,
        Rook,
        Knight,
        Bishop,
        Queen,
        King
    };
    enum class Color
    {
        White,
        Black
    };

    Piece(Type t, Color c);

    Type getType() const;
    Color getColor() const;

    void setTile(Tile* t);
    Tile* getTile() const;

    bool canMoveTo(Tile* tile) const;
    std::vector<std::vector<Tile*>> getLegalMoves(Board& board) const;

private:
    Type type;
    Color color;
    Tile* tile;

    
};