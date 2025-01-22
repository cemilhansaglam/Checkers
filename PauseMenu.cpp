// PauseMenu.cpp
#include "PauseMenu.hpp"
#include <iostream>

PauseMenu::PauseMenu(sf::RenderWindow& window)
    : mWindow(window),
    mResumeButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(window.getSize().x / 2.f, 250.f)),
    mRestartButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(window.getSize().x / 2.f, 350.f)),
    mMenuButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(window.getSize().x / 2.f, 450.f)),
    mSoundSettingsButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(window.getSize().x / 2.f, 550.f)),
    mExitButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(window.getSize().x / 2.f, 650.f)), // Ses ayarlar� butonu konumu
    mResumeRequested(false),
    mRestartRequested(false),
    mReturnToMenuRequested(false),
    mExitRequested(false),
    mSoundSettingsRequestedFlag(false)
{
    // Yaz� tipini y�kle
    if (!mFont.loadFromFile("Resources/fonts/Marker Felt.ttf"))
    {
        std::cout << "Yaz� tipi y�klenemedi!" << std::endl;
    }

    // Duraklatma metnini ayarla
    mPauseText.setFont(mFont);
    mPauseText.setCharacterSize(48);
    mPauseText.setFillColor(sf::Color::White);
    mPauseText.setStyle(sf::Text::Bold);
    mPauseText.setString("Game Paused");
    sf::FloatRect textBounds = mPauseText.getLocalBounds();
    mPauseText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    mPauseText.setPosition(static_cast<float>(window.getSize().x) / 2.f, 150.f);

    // Butonlar� ayarla
    mResumeButton.setFont(mFont);
    mResumeButton.setText("Resume");

    mRestartButton.setFont(mFont);
    mRestartButton.setText("Restart Game");

    mMenuButton.setFont(mFont);
    mMenuButton.setText("Main Menu");

    mExitButton.setFont(mFont);
    mExitButton.setText("Quit");

    mSoundSettingsButton.setFont(mFont);
    mSoundSettingsButton.setText("Sound Menu");
}

void PauseMenu::handleEvent(const sf::Event& event)
{
    mResumeButton.handleEvent(event, mWindow);
    mRestartButton.handleEvent(event, mWindow);
    mMenuButton.handleEvent(event, mWindow);
    mExitButton.handleEvent(event, mWindow);
    mSoundSettingsButton.handleEvent(event, mWindow);

    if (mResumeButton.isClicked())
    {
        mResumeRequested = true;
    }
    else if (mRestartButton.isClicked())
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
    else if (mSoundSettingsButton.isClicked())
    {
        mSoundSettingsRequestedFlag = true; // Ses ayarlar� men�s�ne ge�mek istedi�imizi i�aretliyoruz
    }

    // ESC tu�una bas�l�rsa oyuna geri d�n
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        mResumeRequested = true;
    }
}

void PauseMenu::update()
{
    mResumeButton.update(mWindow);
    mRestartButton.update(mWindow);
    mMenuButton.update(mWindow);
    mExitButton.update(mWindow);
    mSoundSettingsButton.update(mWindow);
}

void PauseMenu::render()
{
    mWindow.draw(mPauseText);
    mResumeButton.render(mWindow);
    mRestartButton.render(mWindow);
    mMenuButton.render(mWindow);
    mExitButton.render(mWindow);
    mSoundSettingsButton.render(mWindow);
}

bool PauseMenu::isResumeRequested()
{
    if (mResumeRequested)
    {
        mResumeRequested = false;
        return true;
    }
    return false;
}

bool PauseMenu::isRestartRequested()
{
    if (mRestartRequested)
    {
        mRestartRequested = false;
        return true;
    }
    return false;
}

bool PauseMenu::isReturnToMenuRequested()
{
    if (mReturnToMenuRequested)
    {
        mReturnToMenuRequested = false;
        return true;
    }
    return false;
}

bool PauseMenu::isExitRequested()
{
    if (mExitRequested)
    {
        mExitRequested = false;
        return true;
    }
    return false;
}
bool PauseMenu::isSoundSettingsRequested()
{
    if (mSoundSettingsRequestedFlag)
    {
        mSoundSettingsRequestedFlag = false;
        return true;
    }
    return false;
}
