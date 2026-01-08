#pragma once
#include "Board.hpp"
#include <SFML/Graphics.hpp>
#include "Renderer.hpp"

class Game
{
public:
    Game();
    void run();

private:
    Board board;
    Renderer renderer;

private:
    void proccessEvents();
    void update();
    void render();

private:
    unsigned int windowWidth;
    unsigned int windowHeight;
    sf::RenderWindow window;
};