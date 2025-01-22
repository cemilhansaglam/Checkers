// MainMenu.hpp
#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <SFML/Graphics.hpp>

class MainMenu
{
public:
    MainMenu(sf::RenderWindow& window);

    void handleEvent(const sf::Event& event);
    void update();
    void render();

    bool isPlayButtonPressed();
    bool isQuitButtonPressed();

private:
    sf::RenderWindow& mWindow;

    // Yaz� tipi ve metin nesneleri
    
    // Ba�l�k resmi ("CHECKERS" yerine)
    sf::Texture mTitleTexture;  // Yeni eklenen texture
    sf::Sprite mTitleSprite;    // Yeni eklenen sprite

    // Arka plan resmi
    sf::Texture mBackgroundTexture;
    sf::Sprite mBackgroundSprite;

    // "Play" butonu
    sf::Sprite mPlayButtonSprite;
    sf::Texture mPlayButtonTexture;

    // "Quit" butonu
    sf::Sprite mQuitButtonSprite;
    sf::Texture mQuitButtonTexture;

    bool mPlayButtonPressed;
    bool mQuitButtonPressed;
};

#endif // MAINMENU_HPP
