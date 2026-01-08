#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "Piece.hpp"

class Renderer
{
private:
    sf::RenderWindow &window;
    sf::Texture boardTexture;
    std::optional<sf::Sprite> boardSprite;

    int boardSize;
    float boardScale;

    std::map<std::pair<Piece::Type, Piece::Color>, sf::Texture> pieceTextures;

public:
    Renderer(sf::RenderWindow& win, int size);

    void drawBoard();
    void drawPieces(Board& board);
};