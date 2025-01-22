// Piece.hpp
#ifndef PIECE_HPP
#define PIECE_HPP

#include <SFML/Graphics.hpp>

class Piece
{
public:
    Piece(bool isWhite);

    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    bool contains(sf::Vector2f point) const;
    bool isWhite() const;

    void makeKing();
    void demoteFromKing(); // Yeni fonksiyon
    bool isKing() const;

    void setSelected(bool selected);
    bool isSelected() const;

private:
    sf::Vector2f mPosition;
    bool mIsWhite;
    bool mIsKing;
    bool mSelected;
};

#endif // PIECE_HPP
