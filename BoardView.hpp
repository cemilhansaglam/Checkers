// BoardView.hpp
#ifndef BOARDVIEW_HPP
#define BOARDVIEW_HPP

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include <vector>

class BoardView
{
public:
    BoardView(const Board& board);

    void draw(sf::RenderWindow& window);

private:
    void initializeTiles();

    const Board& mBoard;
    std::vector<std::vector<sf::RectangleShape>> mTiles;

    sf::CircleShape mPieceShape;
    sf::CircleShape mKingShape;
    sf::CircleShape mHighlightShape;
};

#endif // BOARDVIEW_HPP
