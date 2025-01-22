// SplashState.hpp
#ifndef SPLASHSTATE_HPP
#define SPLASHSTATE_HPP

#include <SFML/Graphics.hpp>

class SplashState
{
public:
    SplashState(sf::RenderWindow& window);

    void handleEvent(const sf::Event& event);
    void update();
    void render();

    bool isFinished() const;

private:
    sf::RenderWindow& mWindow;

    sf::Texture mBackgroundTexture;
    sf::Sprite mBackgroundSprite;

    sf::Clock mClock;
    float mDisplayTime; // Splash ekranýnýn gösterileceði süre (saniye cinsinden)
};

#endif // SPLASHSTATE_HPP
