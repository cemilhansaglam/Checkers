// Button.cpp
#include "Button.hpp"

Button::Button(const sf::Vector2f& size, const sf::Vector2f& position)
    : mIsHovered(false), mIsClicked(false)
{
    mShape.setSize(size);
    mShape.setOrigin(size.x / 2.f, size.y / 2.f);
    mShape.setPosition(position);
    mShape.setFillColor(sf::Color::Blue);

    mText.setCharacterSize(24);
    mText.setFillColor(sf::Color::White);
}

void Button::setFont(const sf::Font& font)
{
    mText.setFont(font);
}

void Button::setText(const std::string& text)
{
    mText.setString(text);

    // Yazý sýnýrlarýný al
    sf::FloatRect textBounds = mText.getLocalBounds();

    // Yazýnýn orijinini ortalayacak þekilde ayarla
    mText.setOrigin(
        textBounds.left + textBounds.width / 2.f,
        textBounds.top + textBounds.height / 2.f
    );

    // Butonun global boyutlarýný al ve yazýyý merkeze yerleþtir
    sf::FloatRect buttonBounds = mShape.getGlobalBounds();
    mText.setPosition(
        buttonBounds.left + buttonBounds.width / 2.f,
        buttonBounds.top + buttonBounds.height / 2.f
    );
}



void Button::setCallback(const std::function<void()>& callback)
{
    mCallback = callback;
}

void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    mIsClicked = false;

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);

            if (mShape.getGlobalBounds().contains(mousePosF))
            {
                mIsClicked = true;
                if (mCallback)
                {
                    mCallback();
                }
            }
        }
    }
}

void Button::update(const sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);

    if (mShape.getGlobalBounds().contains(mousePosF))
    {
        mShape.setFillColor(sf::Color(0, 100, 200)); // Hover rengi
        mIsHovered = true;
    }
    else
    {
        mShape.setFillColor(sf::Color::Blue);
        mIsHovered = false;
    }
}

void Button::render(sf::RenderWindow& window)
{
    window.draw(mShape);
    window.draw(mText);
}

bool Button::isClicked() const
{
    return mIsClicked;
}
