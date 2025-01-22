// SoundMenu.hpp
#ifndef SOUNDMENU_HPP
#define SOUNDMENU_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"

class SoundMenu
{
public:
    SoundMenu(sf::RenderWindow& window, const sf::Font& font, float initialVolume);

    void handleEvent(const sf::Event& event);
    void update();
    void render();

    float getVolume() const;
    void setVolume(float volume);

    bool isBackButtonPressed() const;

private:
    sf::RenderWindow& mWindow;
    sf::Font mFont;
    sf::Text mTitleText;

    Button mIncreaseVolumeButton;
    Button mDecreaseVolumeButton;
    Button mBackButton;

    sf::Text mVolumeText; // Ses seviyesi metni

    float mVolume;
    bool mBackButtonPressed;

    void updateVolumeText(); // Yeni bir yardýmcý fonksiyon
};

#endif // SOUNDMENU_HPP
