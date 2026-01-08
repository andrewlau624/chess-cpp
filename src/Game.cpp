#include <SFML/Graphics.hpp>
#include "Game.hpp"

Game::Game()
    : windowWidth(800),
      windowHeight(800),
      window(sf::VideoMode({windowWidth, windowHeight}), "Chess C++"),
      board(),
      renderer(window, 800)
{
    window.setFramerateLimit(60);
}

void Game::run()
{
    while (window.isOpen())
    {
        proccessEvents();
        update();
        render();
    }
}

void Game::proccessEvents()
{
    while (const auto event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
    }
}

void Game::update()
{
}

void Game::render()
{
    window.clear(sf::Color::White);

    renderer.drawBoard();
    renderer.drawPieces(board);

    window.display();
}