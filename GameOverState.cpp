// GameOverState.cpp
#include "GameOverState.hpp"
#include <iostream>

GameOverState::GameOverState(sf::RenderWindow& window, const std::string& winner)
    : mWindow(window),
    mRestartButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(window.getSize().x / 2.f, 300.f)),
    mMenuButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(window.getSize().x / 2.f, 400.f)),
    mExitButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(window.getSize().x / 2.f, 500.f)),
    mRestartRequested(false),
    mReturnToMenuRequested(false),
    mExitRequested(false)
{
    // Yazý tipini yükle
    if (!mFont.loadFromFile("Resources/fonts/Marker Felt.ttf"))
    {
        std::cout << "Yazý tipi yüklenemedi!" << std::endl;
    }

    // Oyun bitti metnini ayarla
    mGameOverText.setFont(mFont);
    mGameOverText.setCharacterSize(48);
    mGameOverText.setFillColor(sf::Color::White);
    mGameOverText.setStyle(sf::Text::Bold);
    mGameOverText.setString("Game Over: "+  winner + " Wins!");
    sf::FloatRect textBounds = mGameOverText.getLocalBounds();
    mGameOverText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    mGameOverText.setPosition(static_cast<float>(window.getSize().x) / 2.f, 150.f);

    // Butonlarý ayarla
    mRestartButton.setFont(mFont);
    mRestartButton.setText("Restart Game");

    mMenuButton.setFont(mFont);
    mMenuButton.setText("Main Menu");

    mExitButton.setFont(mFont);
    mExitButton.setText("Quit");
}

void GameOverState::handleEvent(const sf::Event& event)
{
    mRestartButton.handleEvent(event, mWindow);
    mMenuButton.handleEvent(event, mWindow);
    mExitButton.handleEvent(event, mWindow);

    if (mRestartButton.isClicked())
    {
        mRestartRequested = true;
    }
    else if (mMenuButton.isClicked())
    {
        mReturnToMenuRequested = true;
    }
    else if (mExitButton.isClicked())
    {
        mExitRequested = true;
    }
}

void GameOverState::update()
{
    mRestartButton.update(mWindow);
    mMenuButton.update(mWindow);
    mExitButton.update(mWindow);
}

void GameOverState::render()
{
   

    mWindow.draw(mGameOverText);
    mRestartButton.render(mWindow);
    mMenuButton.render(mWindow);
    mExitButton.render(mWindow);

   
}

bool GameOverState::isRestartRequested() const
{
    return mRestartRequested;
}

bool GameOverState::isReturnToMenuRequested() const
{
    return mReturnToMenuRequested;
}

bool GameOverState::isExitRequested() const
{
    return mExitRequested;
}
