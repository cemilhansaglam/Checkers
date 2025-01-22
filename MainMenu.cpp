// MainMenu.cpp
#include "MainMenu.hpp"
#include <iostream>

MainMenu::MainMenu(sf::RenderWindow& window)
    : mWindow(window), mPlayButtonPressed(false), mQuitButtonPressed(false)
{
    // Arka plan resmini yükle
    if (!mBackgroundTexture.loadFromFile("Resources/res/arka_plan_2.jpg"))
    {
        std::cout << "Ana menü arka plan resmi yüklenemedi!" << std::endl;
    }
    mBackgroundSprite.setTexture(mBackgroundTexture);
    mBackgroundSprite.setScale(
        static_cast<float>(mWindow.getSize().x) / mBackgroundTexture.getSize().x,
        static_cast<float>(mWindow.getSize().y) / mBackgroundTexture.getSize().y
    );

    // "Play" butonunun resmini yükle
    if (!mPlayButtonTexture.loadFromFile("Resources/res/PLAY__buttons.png"))
    {
        std::cout << "'Play' buton resmi yüklenemedi!" << std::endl;
    }
    mPlayButtonSprite.setTexture(mPlayButtonTexture);

    // "Quit" butonunun resmini yükle
    if (!mQuitButtonTexture.loadFromFile("Resources/res/QUIT_buttons.png"))
    {
        std::cout << "'Quit' buton resmi yüklenemedi!" << std::endl;
    }
    mQuitButtonSprite.setTexture(mQuitButtonTexture);

    

    // Pencere boyutunu al
    sf::Vector2u windowSize = mWindow.getSize();

    

    // "Play" butonu
    sf::FloatRect playBounds = mPlayButtonSprite.getLocalBounds();
    mPlayButtonSprite.setOrigin(playBounds.width / 2.f, playBounds.height / 2.f);
    mPlayButtonSprite.setPosition(
        static_cast<float>(windowSize.x) / 2.f - playBounds.width / 1.5f, // Sol tarafa
        playBounds.height / 2.f + 20.f // Üstte olacak þekilde
    );

    // "Quit" butonu
    sf::FloatRect quitBounds = mQuitButtonSprite.getLocalBounds();
    mQuitButtonSprite.setOrigin(quitBounds.width / 2.f, quitBounds.height / 2.f);
    mQuitButtonSprite.setPosition(
        static_cast<float>(windowSize.x) / 2.f + quitBounds.width / 1.5f, // Sað tarafa
        quitBounds.height / 2.f + 20.f // Üstte olacak þekilde
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
    // Fare imleci butonlarýn üzerindeyken renk deðiþimi
    sf::Vector2i mousePos = sf::Mouse::getPosition(mWindow);
    sf::Vector2f mousePosF = mWindow.mapPixelToCoords(mousePos);

    // "Play" butonu
    if (mPlayButtonSprite.getGlobalBounds().contains(mousePosF))
    {
        mPlayButtonSprite.setColor(sf::Color(200, 200, 200)); // Daha açýk renk
    }
    else
    {
        mPlayButtonSprite.setColor(sf::Color(255, 255, 255)); // Normal renk
    }

    // "Quit" butonu
    if (mQuitButtonSprite.getGlobalBounds().contains(mousePosF))
    {
        mQuitButtonSprite.setColor(sf::Color(200, 200, 200)); // Daha açýk renk
    }
    else
    {
        mQuitButtonSprite.setColor(sf::Color(255, 255, 255)); // Normal renk
    }
}

void MainMenu::render()
{
    // Pencereyi temizleme iþlemi Game::render() fonksiyonunda yapýlýyorsa burada yapmaya gerek yok

    // Arka planý çiz
    mWindow.draw(mBackgroundSprite);

    // Baþlýk resmini çiz
    mWindow.draw(mTitleSprite);

    // Butonlarý çiz
    mWindow.draw(mPlayButtonSprite);
    mWindow.draw(mQuitButtonSprite);

    // Pencereyi görüntüleme iþlemi Game::render() fonksiyonunda yapýlýyorsa burada yapmaya gerek yok
}

bool MainMenu::isPlayButtonPressed()
{
    bool wasPressed = mPlayButtonPressed;
    mPlayButtonPressed = false; // Sýfýrla
    return wasPressed;
}

bool MainMenu::isQuitButtonPressed()
{
    bool wasPressed = mQuitButtonPressed;
    mQuitButtonPressed = false; // Sýfýrla
    return wasPressed;
}
