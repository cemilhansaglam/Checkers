// Button.hpp
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>

class Button
{
public:
    Button(const sf::Vector2f& size, const sf::Vector2f& position);

    void setFont(const sf::Font& font);
    void setText(const std::string& text);
    void setCallback(const std::function<void()>& callback);

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void update(const sf::RenderWindow& window);
    void render(sf::RenderWindow& window);

    bool isClicked() const;

private:
    sf::RectangleShape mShape;
    sf::Text mText;
    std::function<void()> mCallback;
    bool mIsHovered;
    bool mIsClicked;
};

#endif // BUTTON_HPP
