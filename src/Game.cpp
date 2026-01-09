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
    renderer.fillSelectedTile(selectedTile);
    renderer.fillLegalMoves(selectedLegalMoves.front());

    renderer.drawPieces(board);
    renderer.fillCapturablePieces(selectedLegalMoves.back());

    window.display();
}

void Game::handleMouseClick(const sf::Vector2i &mousePos)
{
    Tile *clickedTile = renderer.getTileFromCoord(mousePos, board);
    if (!clickedTile)
        return;

    if (clickedTile->isOccupied() &&
        (!selectedTile || (selectedTile && selectedTile->getPiece()->getColor() == clickedTile->getPiece()->getColor())))
    {
        selectedTile = clickedTile;

        Piece *selectedPiece = selectedTile->getPiece();

        if (selectedPiece)
        {
            selectedLegalMoves = selectedPiece->getLegalMoves(board);
        }
        else
        {
            selectedLegalMoves = {{}, {}};
        }

        return;
    }

    if (!selectedTile)
        return;

    if (std::find(selectedLegalMoves.front().begin(), selectedLegalMoves.front().end(), clickedTile) != selectedLegalMoves.front().end())
    {
        Piece *piece = selectedTile->getPiece();
        clickedTile->setPiece(piece);
        selectedTile->setPiece(nullptr);
        piece->setTile(clickedTile);
    }
    else if (std::find(selectedLegalMoves.back().begin(), selectedLegalMoves.back().end(), clickedTile) != selectedLegalMoves.back().end())
    {
        Piece *piece = selectedTile->getPiece();
        clickedTile->setPiece(piece);
        selectedTile->setPiece(nullptr);
        piece->setTile(clickedTile);
    }

    selectedTile = nullptr;
    selectedLegalMoves = selectedLegalMoves = {{}, {}};
}