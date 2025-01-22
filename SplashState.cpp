// SplashState.cpp
#include "SplashState.hpp"
#include <iostream>

SplashState::SplashState(sf::RenderWindow& window)
    : mWindow(window), mDisplayTime(10.f) // Splash ekraný 10 saniye görünecek
{
    // Arka plan resmini yükle
    if (!mBackgroundTexture.loadFromFile("Resources/res/Splash_2.jpg"))
    {
        std::cout << "Splash arka plan resmi yüklenemedi!" << std::endl;
    }
    mBackgroundSprite.setTexture(mBackgroundTexture);
    mBackgroundSprite.setScale(
        static_cast<float>(mWindow.getSize().x) / mBackgroundTexture.getSize().x,
        static_cast<float>(mWindow.getSize().y) / mBackgroundTexture.getSize().y
    );

    // Zamanlayýcýyý baþlat
    mClock.restart();
}

void SplashState::handleEvent(const sf::Event& event)
{
    // Ýsteðe baðlý olarak, splash ekraný týklanýrsa hemen geçilebilir
    if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed)
    {
        mDisplayTime = 0.f; // Süreyi sýfýrlayarak hemen geçiþ yap
    }
}

void SplashState::update()
{
    // Zamanlayýcýyý kontrol et
    if (mClock.getElapsedTime().asSeconds() >= mDisplayTime)
    {
        // Splash ekraný tamamlandý
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
