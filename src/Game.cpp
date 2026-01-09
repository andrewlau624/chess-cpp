#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "Renderer.hpp"

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
        else if (event->is<sf::Event::MouseButtonPressed>())
        {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            handleMouseClick(pos);
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
    renderer.fillSelectedTile(selectedTile);

    window.display();
}

void Game::handleMouseClick(const sf::Vector2i &mousePos)
{
    Tile *clickedTile = renderer.getTileFromCoord(mousePos, board);
    if (!clickedTile)
        return;

    if (clickedTile->isOccupied())
    {
        selectedTile = clickedTile;
        return;
    }

    if (!selectedTile)
        return;

    Piece *selectedPiece = selectedTile->getPiece();
    auto legalMoves = selectedPiece->getLegalMoves(board);

    if (std::find(legalMoves.begin(), legalMoves.end(), clickedTile) != legalMoves.end())
    {
        clickedTile->setPiece(selectedPiece);
        selectedTile->setPiece(nullptr);
        selectedPiece->setTile(clickedTile);
    }

    selectedTile = nullptr;
}
