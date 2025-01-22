// PauseMenu.hpp
#ifndef PAUSEMENU_HPP
#define PAUSEMENU_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"

class PauseMenu
{
public:
    PauseMenu(sf::RenderWindow& window);

    void handleEvent(const sf::Event& event);
    void update();
    void render();

    bool isResumeRequested();
    bool isRestartRequested();
    bool isReturnToMenuRequested();
    bool isExitRequested();
    bool isSoundSettingsRequested(); // Yeni fonksiyon

private:
    sf::RenderWindow& mWindow;

    sf::Font mFont;
    sf::Text mPauseText;

    Button mResumeButton;
    Button mRestartButton;
    Button mMenuButton;
    Button mExitButton;
    Button mSoundSettingsButton; // Ses ayarlar� butonu

    bool mResumeRequested;
    bool mRestartRequested;
    bool mReturnToMenuRequested;
    bool mExitRequested;
    bool mSoundSettingsRequestedFlag; // Ses ayarlar� istek bayra��
};

#endif // PAUSEMENU_HPP
