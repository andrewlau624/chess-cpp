#include <iostream>
#include <vector>

#include "Piece.hpp"
#include "Tile.hpp"

Piece::Piece(Type t, Color c) : type(t), color(c) {}

Piece::Type Piece::getType() const { return type; }
Piece::Color Piece::getColor() const { return color; }

void Piece::setTile(Tile *t) { tile = t; }
Tile *Piece::getTile() const { return tile; }

bool Piece::canMoveTo(Tile *tile) const
{
    if (!tile)
        return false;

    if (!tile->isOccupied())
        return true;

    return tile->getPiece()->getColor() != color;
};

std::vector<std::vector<Tile *>> Piece::getLegalMoves(Board &board) const
{
    std::vector<std::vector<Tile *>> legalMoves;

    if (!tile)
        return legalMoves;

    auto tryAdd = [&](int r, int c, std::vector<Tile *> &path, std::vector<Tile *> &captureVec) -> bool
    {
        Tile *t = board.getTile(r, c);
        if (!t)
            return false;

        path.push_back(t);

        if (t->isOccupied())
        {
            if (t->getPiece()->getColor() != color)
            {
                captureVec.push_back(t);
            }
            return false;
        }

        return true;
    };

    switch (type)
    {
    case Piece::Type::Pawn:
    {
        int dir = (color == Piece::Color::White) ? -1 : 1;
        int r = tile->getRow();
        int c = tile->getCol();

        std::vector<Tile *> path;
        std::vector<Tile *> captureVec;
        
        Tile *one = board.getTile(r + dir, c);
        if (one && !one->isOccupied())
        {
            path.push_back(one);

            bool onStart = (color == Piece::Color::White && r == 6) ||
                           (color == Piece::Color::Black && r == 1);
            if (onStart)
            {
                Tile *two = board.getTile(r + 2 * dir, c);
                if (two && !two->isOccupied())
                    path.push_back(two);
            }
        }

        for (int dc : {-1, 1})
        {
            Tile *diag = board.getTile(r + dir, c + dc);
            tryAdd(r + dir, c + dc, path, captureVec);
        }

        legalMoves.push_back(path);
        legalMoves.push_back(captureVec);

        break;
    }
    case Piece::Type::Rook:
    {
        const int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int r = tile->getRow();
        int c = tile->getCol();

        std::vector<Tile *> path;
        std::vector<Tile *> captureVec;

        for (auto &d : dirs)
        {
            for (int i = 1;; i++)
            {
                if (!tryAdd(r + d[0] * i, c + d[1] * i, path, captureVec))
                    break;
            }
        }
        break;
    }
    case Piece::Type::Bishop:
    {
        const int dirs[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        int r = tile->getRow();
        int c = tile->getCol();

        std::vector<Tile *> path;
        std::vector<Tile *> captureVec;


        for (auto &d : dirs)
        {
            for (int i = 1;; i++)
            {
                if (!tryAdd(tile->getRow() + d[0] * i, tile->getCol() + d[1] * i))
                    break;
            }
        }
        break;
    }
    case Piece::Type::Queen:
    {
        const int dirs[8][2] = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        for (auto &d : dirs)
        {
            for (int i = 1;; i++)
            {
                if (!tryAdd(tile->getRow() + d[0] * i, tile->getCol() + d[1] * i))
                    break;
            }
        }
        break;
        break;
    }
    case Piece::Type::Knight:
    {
        const int jumps[8][2] = {
            {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

        for (auto &j : jumps)
        {
            Tile *t = board.getTile(tile->getRow() + j[0], tile->getCol() + j[1]);
            if (!t)
                continue;

            if (!t->isOccupied() ||
                t->getPiece()->getColor() != color)
            {
                legalMoves.push_back(t);
            }
        }
        break;
    }
    case Piece::Type::King:
    {
        for (int dr = -1; dr <= 1; dr++)
        {
            for (int dc = -1; dc <= 1; dc++)
            {
                if (dr == 0 && dc == 0)
                    continue;

                Tile *t = board.getTile(tile->getRow() + dr, tile->getCol() + dc);
                if (!t)
                    continue;

                if (!t->isOccupied() ||
                    t->getPiece()->getColor() != color)
                {
                    legalMoves.push_back(t);
                }
            }
        }
        break;
    }
    default:
    {
        break;
    }
    }

    return legalMoves;
}