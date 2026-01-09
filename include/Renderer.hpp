#pragma once
#include <SFML/Graphics.hpp>
#include <map>

#include "Piece.hpp"
#include "Tile.hpp"

class Renderer
{
private:
    sf::RenderWindow &window;

    sf::Texture whiteTileTexture;
    sf::Texture blackTileTexture;

    int boardSize;
    float boardScale;

    std::map<std::pair<Piece::Type, Piece::Color>, sf::Texture> pieceTextures;

    void loadAssets();

public:
    Renderer(sf::RenderWindow& win, int size);

    void drawBoard();
    void drawPieces(Board& board);

public:
    Tile* getTileFromCoord(const sf::Vector2i& pos, Board& board) const;
    void fillSelectedTile(Tile* tile);
};