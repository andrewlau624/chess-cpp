#include "Board.hpp"
#include "Renderer.hpp"
#include <SFML/Graphics.hpp>

Renderer::Renderer(sf::RenderWindow &win, int size) : window(win), boardSize(size)
{
    loadAssets();
}

void Renderer::drawBoard()
{
    float tileSize = boardSize / Board::SIZE;

    for (int r = 0; r < Board::SIZE; ++r)
    {
        for (int c = 0; c < Board::SIZE; ++c)
        {
            std::optional<sf::Sprite> tileSprite = sf::Sprite((r + c) % 2 == 0 ? whiteTileTexture : blackTileTexture);

            float scale = tileSize / tileSprite->getTexture().getSize().x;
            tileSprite->setScale({scale, scale});

            tileSprite->setPosition({c * tileSize, r * tileSize});

            window.draw(*tileSprite);
        }
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
            Tile *tile = board.getTile(r, c);

            if (!tile->isOccupied())
            {
                continue;
            }

            Piece *piece = tile->getPiece();

            if (piece != nullptr)
            {
                std::optional<sf::Sprite> sprite = sf::Sprite(pieceTextures[{piece->getType(), piece->getColor()}]);

                float scale = tileSize / sprite->getTexture().getSize().x * .6f;
                sprite->setScale({scale, scale});

                float offset = border + (tileSize - sprite->getTexture().getSize().x * scale) / 2;
                sprite->setPosition({c * tileSize + offset, r * tileSize + offset});

                window.draw(*sprite);
            }
        }
    }
}

void Renderer::fillSelectedTile(Tile *tile)
{
    if (!tile)
    {
        return;
    }

    float tileSize = boardSize / Board::SIZE;

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(tileSize, tileSize));
    rectangle.setPosition({tileSize * tile->getCol(), tileSize * tile->getRow()});
    rectangle.setFillColor(sf::Color(255, 255, 255, 128));
    window.draw(rectangle);
}

void Renderer::loadAssets()
{
    // Board
    if (!whiteTileTexture.loadFromFile("assets/white_square.png"))
    {
    }
    if (!blackTileTexture.loadFromFile("assets/black_square.png"))
    {
    }

    whiteTileTexture.setSmooth(false);
    blackTileTexture.setSmooth(false);

    // White
    sf::Texture whitePawn;
    sf::Texture whiteKnight;
    sf::Texture whiteBishop;
    sf::Texture whiteRook;
    sf::Texture whiteQueen;
    sf::Texture whiteKing;

    whitePawn.setSmooth(true);
    whiteKnight.setSmooth(true);
    whiteBishop.setSmooth(true);
    whiteRook.setSmooth(true);
    whiteQueen.setSmooth(true);
    whiteKing.setSmooth(true);

    if (!whitePawn.loadFromFile("assets/w_pawn.png"))
    {
    };
    pieceTextures[{Piece::Type::Pawn, Piece::Color::White}] = whitePawn;
    if (!whiteKnight.loadFromFile("assets/w_knight.png"))
    {
    };
    pieceTextures[{Piece::Type::Knight, Piece::Color::White}] = whiteKnight;
    if (!whiteBishop.loadFromFile("assets/w_bishop.png"))
    {
    };
    pieceTextures[{Piece::Type::Bishop, Piece::Color::White}] = whiteBishop;
    if (!whiteRook.loadFromFile("assets/w_rook.png"))
    {
    };
    pieceTextures[{Piece::Type::Rook, Piece::Color::White}] = whiteRook;
    if (!whiteQueen.loadFromFile("assets/w_queen.png"))
    {
    };
    pieceTextures[{Piece::Type::Queen, Piece::Color::White}] = whiteQueen;
    if (!whiteKing.loadFromFile("assets/w_king.png"))
    {
    };
    pieceTextures[{Piece::Type::King, Piece::Color::White}] = whiteKing;

    // Black
    sf::Texture blackPawn;
    sf::Texture blackKnight;
    sf::Texture blackBishop;
    sf::Texture blackRook;
    sf::Texture blackQueen;
    sf::Texture blackKing;

    blackPawn.setSmooth(true);
    blackKnight.setSmooth(true);
    blackBishop.setSmooth(true);
    blackRook.setSmooth(true);
    blackQueen.setSmooth(true);
    blackKing.setSmooth(true);

    if (!blackPawn.loadFromFile("assets/b_pawn.png"))
    {
    };
    pieceTextures[{Piece::Type::Pawn, Piece::Color::Black}] = blackPawn;
    if (!blackKnight.loadFromFile("assets/b_knight.png"))
    {
    };
    pieceTextures[{Piece::Type::Knight, Piece::Color::Black}] = blackKnight;
    if (!blackBishop.loadFromFile("assets/b_bishop.png"))
    {
    };
    pieceTextures[{Piece::Type::Bishop, Piece::Color::Black}] = blackBishop;
    if (!blackRook.loadFromFile("assets/b_rook.png"))
    {
    };
    pieceTextures[{Piece::Type::Rook, Piece::Color::Black}] = blackRook;
    if (!blackQueen.loadFromFile("assets/b_queen.png"))
    {
    };
    pieceTextures[{Piece::Type::Queen, Piece::Color::Black}] = blackQueen;
    if (!blackKing.loadFromFile("assets/b_king.png"))
    {
    };
    pieceTextures[{Piece::Type::King, Piece::Color::Black}] = blackKing;
}

Tile *Renderer::getTileFromCoord(const sf::Vector2i &pos, Board &board) const
{
    float tileSize = boardSize / Board::SIZE;

    int r = pos.y / tileSize;
    int c = pos.x / tileSize;

    return board.getTile(r, c);
}