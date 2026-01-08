#pragma once
class Piece;

class Tile
{
public:
    Tile() : row(-1), col(-1), piece(nullptr) {}  
    Tile(int r, int c);

    int getRow() const;
    int getCol() const;

    Piece *getPiece() const;
    void setPiece(Piece *p);

    bool isOccupied() const;

private:
    int row, col;
    Piece *piece;
};