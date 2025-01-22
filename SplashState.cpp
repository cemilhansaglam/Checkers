// SplashState.cpp
#include "SplashState.hpp"
#include <iostream>

SplashState::SplashState(sf::RenderWindow& window)
    : mWindow(window), mDisplayTime(10.f) // Splash ekran� 10 saniye g�r�necek
{
    // Arka plan resmini y�kle
    if (!mBackgroundTexture.loadFromFile("Resources/res/Splash_2.jpg"))
    {
        std::cout << "Splash arka plan resmi y�klenemedi!" << std::endl;
    }
    mBackgroundSprite.setTexture(mBackgroundTexture);
    mBackgroundSprite.setScale(
        static_cast<float>(mWindow.getSize().x) / mBackgroundTexture.getSize().x,
        static_cast<float>(mWindow.getSize().y) / mBackgroundTexture.getSize().y
    );

    // Zamanlay�c�y� ba�lat
    mClock.restart();
}

void SplashState::handleEvent(const sf::Event& event)
{
    // �ste�e ba�l� olarak, splash ekran� t�klan�rsa hemen ge�ilebilir
    if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed)
    {
        mDisplayTime = 0.f; // S�reyi s�f�rlayarak hemen ge�i� yap
    }
}

void SplashState::update()
{
    // Zamanlay�c�y� kontrol et
    if (mClock.getElapsedTime().asSeconds() >= mDisplayTime)
    {
        // Splash ekran� tamamland�
    }
}

void SplashState::render()
{
    mWindow.draw(mBackgroundSprite);
}

bool SplashState::isFinished() const
{
    return mClock.getElapsedTime().asSeconds() >= mDisplayTime;
}
