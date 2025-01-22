// SidePanel.hpp
#ifndef SIDEPANEL_HPP
#define SIDEPANEL_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"

class SidePanel
{
public:
    SidePanel(const sf::Font& font);

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void update(const sf::RenderWindow& window, bool isWhiteTurn);
    void render(sf::RenderWindow& window);

    bool isUndoButtonClicked() const;
    bool isPauseButtonClicked() const;

private:
    sf::RectangleShape mBackground;
    sf::Text mTurnText;

    Button mUndoButton;
    Button mPauseButton;

    bool mIsUndoButtonClicked;
    bool mIsPauseButtonClicked;
};

#endif // SIDEPANEL_HPP
