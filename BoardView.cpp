// BoardView.cpp
#include "BoardView.hpp"

BoardView::BoardView(const Board& board)
    : mBoard(board)
{

    mTiles.resize(8, std::vector<sf::RectangleShape>(8));


    initializeTiles();

    // Taþ þekilleri için ortak ayarlar
    mPieceShape.setRadius(40.f);
    mPieceShape.setOrigin(40.f, 40.f);

    mKingShape.setRadius(20.f);
    mKingShape.setOrigin(20.f, 20.f);
    mKingShape.setFillColor(sf::Color::Yellow);

    mHighlightShape.setRadius(42.f);
    mHighlightShape.setOrigin(42.f, 42.f);
    mHighlightShape.setFillColor(sf::Color::Transparent);
    mHighlightShape.setOutlineColor(sf::Color::Red);
    mHighlightShape.setOutlineThickness(4.f);
}

void BoardView::initializeTiles()
{
    float tileSize = 100.f;
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            mTiles[row][col].setSize(sf::Vector2f(tileSize, tileSize));
            mTiles[row][col].setPosition(col * tileSize, row * tileSize);
            if ((row + col) % 2 == 0)
            {
                mTiles[row][col].setFillColor(sf::Color(255, 206, 158)); // Açýk renk
            }
            else
            {
                mTiles[row][col].setFillColor(sf::Color(209, 139, 71)); // Koyu renk
            }
        }
    }
}

void BoardView::draw(sf::RenderWindow& window)
{
    // Tahtayý çiz
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            window.draw(mTiles[row][col]);
        }
    }

    // Taþlarý çiz
    for (const auto& piece : mBoard.getPieces())
    {
        mPieceShape.setPosition(piece->getPosition());
        if (piece->isWhite())
        {
            mPieceShape.setFillColor(sf::Color::White);
            mPieceShape.setOutlineColor(sf::Color::Black);
        }
        else
        {
            mPieceShape.setFillColor(sf::Color::Black);
            mPieceShape.setOutlineColor(sf::Color::White);
        }
        mPieceShape.setOutlineThickness(2.f);
        window.draw(mPieceShape);

        // Dama ise kral sembolünü çiz
        if (piece->isKing())
        {
            mKingShape.setPosition(piece->getPosition());
            window.draw(mKingShape);
        }

        // Seçili ise vurguyu çiz
        if (piece->isSelected())
        {
            mHighlightShape.setPosition(piece->getPosition());
            window.draw(mHighlightShape);
        }
    }
}
