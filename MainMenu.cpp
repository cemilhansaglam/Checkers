// MainMenu.cpp
#include "MainMenu.hpp"
#include <iostream>

MainMenu::MainMenu(sf::RenderWindow& window)
    : mWindow(window), mPlayButtonPressed(false), mQuitButtonPressed(false)
{
    // Arka plan resmini y�kle
    if (!mBackgroundTexture.loadFromFile("Resources/res/arka_plan_2.jpg"))
    {
        std::cout << "Ana men� arka plan resmi y�klenemedi!" << std::endl;
    }
    mBackgroundSprite.setTexture(mBackgroundTexture);
    mBackgroundSprite.setScale(
        static_cast<float>(mWindow.getSize().x) / mBackgroundTexture.getSize().x,
        static_cast<float>(mWindow.getSize().y) / mBackgroundTexture.getSize().y
    );

    // "Play" butonunun resmini y�kle
    if (!mPlayButtonTexture.loadFromFile("Resources/res/PLAY__buttons.png"))
    {
        std::cout << "'Play' buton resmi y�klenemedi!" << std::endl;
    }
    mPlayButtonSprite.setTexture(mPlayButtonTexture);

    // "Quit" butonunun resmini y�kle
    if (!mQuitButtonTexture.loadFromFile("Resources/res/QUIT_buttons.png"))
    {
        std::cout << "'Quit' buton resmi y�klenemedi!" << std::endl;
    }
    mQuitButtonSprite.setTexture(mQuitButtonTexture);

    

    // Pencere boyutunu al
    sf::Vector2u windowSize = mWindow.getSize();

    

    // "Play" butonu
    sf::FloatRect playBounds = mPlayButtonSprite.getLocalBounds();
    mPlayButtonSprite.setOrigin(playBounds.width / 2.f, playBounds.height / 2.f);
    mPlayButtonSprite.setPosition(
        static_cast<float>(windowSize.x) / 2.f - playBounds.width / 1.5f, // Sol tarafa
        playBounds.height / 2.f + 20.f // �stte olacak �ekilde
    );

    // "Quit" butonu
    sf::FloatRect quitBounds = mQuitButtonSprite.getLocalBounds();
    mQuitButtonSprite.setOrigin(quitBounds.width / 2.f, quitBounds.height / 2.f);
    mQuitButtonSprite.setPosition(
        static_cast<float>(windowSize.x) / 2.f + quitBounds.width / 1.5f, // Sa� tarafa
        quitBounds.height / 2.f + 20.f // �stte olacak �ekilde
    );
}

void MainMenu::handleEvent(const sf::Event& event)
{
    mPlayButtonPressed = false;
    mQuitButtonPressed = false;

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(mWindow);
            sf::Vector2f mousePosF = mWindow.mapPixelToCoords(mousePos);

            if (mPlayButtonSprite.getGlobalBounds().contains(mousePosF))
            {
                mPlayButtonPressed = true;
            }
            else if (mQuitButtonSprite.getGlobalBounds().contains(mousePosF))
            {
                mQuitButtonPressed = true;
            }
        }
    }
}

void MainMenu::update()
{
    // Fare imleci butonlar�n �zerindeyken renk de�i�imi
    sf::Vector2i mousePos = sf::Mouse::getPosition(mWindow);
    sf::Vector2f mousePosF = mWindow.mapPixelToCoords(mousePos);

    // "Play" butonu
    if (mPlayButtonSprite.getGlobalBounds().contains(mousePosF))
    {
        mPlayButtonSprite.setColor(sf::Color(200, 200, 200)); // Daha a��k renk
    }
    else
    {
        mPlayButtonSprite.setColor(sf::Color(255, 255, 255)); // Normal renk
    }

    // "Quit" butonu
    if (mQuitButtonSprite.getGlobalBounds().contains(mousePosF))
    {
        mQuitButtonSprite.setColor(sf::Color(200, 200, 200)); // Daha a��k renk
    }
    else
    {
        mQuitButtonSprite.setColor(sf::Color(255, 255, 255)); // Normal renk
    }
}

void MainMenu::render()
{
    // Pencereyi temizleme i�lemi Game::render() fonksiyonunda yap�l�yorsa burada yapmaya gerek yok

    // Arka plan� �iz
    mWindow.draw(mBackgroundSprite);

    // Ba�l�k resmini �iz
    mWindow.draw(mTitleSprite);

    // Butonlar� �iz
    mWindow.draw(mPlayButtonSprite);
    mWindow.draw(mQuitButtonSprite);

    // Pencereyi g�r�nt�leme i�lemi Game::render() fonksiyonunda yap�l�yorsa burada yapmaya gerek yok
}

bool MainMenu::isPlayButtonPressed()
{
    bool wasPressed = mPlayButtonPressed;
    mPlayButtonPressed = false; // S�f�rla
    return wasPressed;
}

bool MainMenu::isQuitButtonPressed()
{
    bool wasPressed = mQuitButtonPressed;
    mQuitButtonPressed = false; // S�f�rla
    return wasPressed;
}
