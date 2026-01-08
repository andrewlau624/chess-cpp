#include "Piece.hpp"
#include "Tile.hpp"

Piece::Piece(Type t, Color c) : type(t), color(c) {}

Piece::Type Piece::getType() const { return type; }
Piece::Color Piece::getColor() const { return color; }

void Piece::setTile(Tile* t) { tile = t; }
Tile* Piece::getTile() const { return tile; }