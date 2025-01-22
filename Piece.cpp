// Piece.cpp
#include "Piece.hpp"
#include <cmath>

Piece::Piece(bool isWhite)
    : mIsWhite(isWhite), mIsKing(false), mSelected(false)
{
}

void Piece::setPosition(float x, float y)
{
    mPosition = sf::Vector2f(x, y);
}

void Piece::setPosition(const sf::Vector2f& position)
{
    mPosition = position;
}

sf::Vector2f Piece::getPosition() const
{
    return mPosition;
}

bool Piece::contains(sf::Vector2f point) const
{
    float dx = point.x - mPosition.x;
    float dy = point.y - mPosition.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance <= 40.f; // Taþ yarýçapý 40 piksel
}

bool Piece::isWhite() const
{
    return mIsWhite;
}

void Piece::makeKing()
{
    mIsKing = true;
}

void Piece::demoteFromKing()
{
    mIsKing = false;
}

bool Piece::isKing() const
{
    return mIsKing;
}

void Piece::setSelected(bool selected)
{
    mSelected = selected;
}

bool Piece::isSelected() const
{
    return mSelected;
}
