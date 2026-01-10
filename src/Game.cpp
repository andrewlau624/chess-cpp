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

    if (clickedTile->isOccupied() && clickedTile != board.enPassantTile &&
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

    for (auto &moves : selectedLegalMoves)
    {
        bool isNormalMove = std::find(moves.begin(), moves.end(), clickedTile) != moves.end();

        if (!isNormalMove)
            continue;

        executeMove(selectedTile, clickedTile);
        break;
    }

    selectedTile = nullptr;
    selectedLegalMoves = {{}, {}};
}

void Game::executeMove(Tile *from, Tile *to)
{
    if (!from || !to)
        return;

    Piece *piece = from->getPiece();
    if (!piece)
        return;

    if (board.enPassantTile)
    {
        if (to == board.enPassantTile && piece->getType() == Piece::Type::Pawn)
            to->getPiece()->getTile()->setPiece(nullptr);
        board.enPassantTile->setPiece(nullptr);
    }

    board.enPassantTile = nullptr;
    if (piece->getType() == Piece::Type::Pawn)
    {
        int dr = std::abs(from->getRow() - to->getRow());
        if (dr == 2)
        {
            int midRow = (from->getRow() + to->getRow()) / 2;
            Tile *enPassantTile = board.getTile(midRow, from->getCol());
            board.enPassantTile = enPassantTile;
            enPassantTile->setPiece(from->getPiece());
        }
    }

    if (piece->getType() == Piece::Type::Rook)
    {
        if (piece->getColor() == Piece::Color::White)
        {
            if (from->getRow() == 7 && from->getCol() == 0)
                board.whiteCastleQueenSide = false;
            else if (from->getRow() == 7 && from->getCol() == 7)
                board.whiteCastleKingSide = false;
        }
        else
        {
            if (from->getRow() == 0 && from->getCol() == 0)
                board.blackCastleQueenSide = false;
            else if (from->getRow() == 0 && from->getCol() == 7)
                board.blackCastleKingSide = false;
        }
    }
    else if (piece->getType() == Piece::Type::King)
    {
        if (piece->getColor() == Piece::Color::White)
        {
            board.whiteCastleQueenSide = false;
            board.whiteCastleKingSide = false;
        }
        else
        {
            board.blackCastleQueenSide = false;
            board.blackCastleKingSide = false;
        }

        int c = to->getCol();
        int r = to->getRow();
        int dc = std::abs(from->getCol() - c);
        if (dc == 2)
        {
            if (c == 2) {
                Tile* rook = board.getTile(r, 0);
                Tile* newRook = board.getTile(r, 3);

                newRook->setPiece(rook->getPiece());
                newRook->getPiece()->setTile(newRook);

                rook->setPiece(nullptr);
            } else if (c == 6) {
                Tile* rook = board.getTile(r, 7);
                Tile* newRook = board.getTile(r, 5);

                newRook->setPiece(rook->getPiece());
                newRook->getPiece()->setTile(newRook);

                rook->setPiece(nullptr);
            }
        }
    }

    to->setPiece(piece);
    from->setPiece(nullptr);
    piece->setTile(to);
}
