#pragma once
#include <SFML/Graphics.hpp>

#include "Board.hpp"
#include "Piece.hpp"
#include "Renderer.hpp"

class Game
{
public:
    Game();
    void run();

private:
    unsigned int windowWidth;
    unsigned int windowHeight;
    sf::RenderWindow window;

private:
    Board board;
    Renderer renderer;

private:
    Piece::Color player;
    Tile* selectedTile;

private:
    void proccessEvents();
    void update();
    void render();

private:
    void handleMouseClick(const sf::Vector2i& mousePos);
};