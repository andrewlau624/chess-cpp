#include "Board.hpp"
#include "Renderer.hpp"
#include <SFML/Graphics.hpp>

Renderer::Renderer(sf::RenderWindow &win, int size) : window(win), boardSize(size)
{
    if (!boardTexture.loadFromFile("assets/board.png"))
    {
    };
    boardTexture.setSmooth(false);

    boardSprite = sf::Sprite(boardTexture);
    boardSprite->setPosition({0, 0});

    sf::Vector2u texSize = boardTexture.getSize();
    boardScale = boardSize / static_cast<float>(texSize.x);
    boardSprite->setScale({boardScale, boardScale});

    sf::Texture whitePawn;
    if (!whitePawn.loadFromFile("assets/w_pawn.png"))
    {
    };
    pieceTextures[{Piece::Type::Pawn, Piece::Color::White}] = whitePawn;

    sf::Texture blackPawn;
    if (!blackPawn.loadFromFile("assets/b_pawn.png"))
    {
    };
    pieceTextures[{Piece::Type::Pawn, Piece::Color::Black}] = blackPawn;
}

void Renderer::drawBoard()
{
    if (boardSprite)
    {
        window.draw(*boardSprite);
    }
}

void Renderer::drawPieces(Board &board)
{
    float border = 7.f * boardScale;
    float usableBoardSize = boardSize - 2 * border;
    float tileSize = usableBoardSize / Board::SIZE;
    
    for (int r = 0; r < Board::SIZE; ++r)
    {
        for (int c = 0; c < Board::SIZE; ++c)
        {
            Tile &tile = board.getTile(r, c);

            if (!tile.isOccupied())
            {
                continue;
            }

            Piece *piece = tile.getPiece();

            if (piece != nullptr)
            {
                std::optional<sf::Sprite> sprite = sf::Sprite(pieceTextures[{piece->getType(), piece->getColor()}]);

                float scale = tileSize / sprite->getTexture().getSize().x * .7f;
                sprite->setScale({scale, scale});

                float offset = border + (tileSize - sprite->getTexture().getSize().x * scale) / 2;
                sprite->setPosition({c * tileSize + offset, r * tileSize + offset});

                window.draw(*sprite);
            }
        }
    }
}