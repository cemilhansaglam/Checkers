// GameOverState.hpp
#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"

class GameOverState
{
public:
    GameOverState(sf::RenderWindow& window, const std::string& winner);

    void handleEvent(const sf::Event& event);
    void update();
    void render();

    bool isRestartRequested() const;
    bool isReturnToMenuRequested() const;
    bool isExitRequested() const;

private:
    sf::RenderWindow& mWindow;

    sf::Font mFont;
    sf::Text mGameOverText;

    Button mRestartButton;
    Button mMenuButton;
    Button mExitButton;

    bool mRestartRequested;
    bool mReturnToMenuRequested;
    bool mExitRequested;
};

#endif // GAMEOVERSTATE_HPP
