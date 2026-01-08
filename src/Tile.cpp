#include "Piece.hpp"
#include "Tile.hpp"

Tile::Tile(int r, int c) : row(r), col(c), piece(nullptr) {}

int Tile::getRow() const { return row; }
int Tile::getCol() const { return col; }

Piece* Tile::getPiece() const { return piece; }
void Tile::setPiece(Piece* p) { piece = p; }
bool Tile::isOccupied() const { return piece != nullptr; }