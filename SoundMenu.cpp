// SoundMenu.cpp
#include "SoundMenu.hpp"
#include <iostream>

SoundMenu::SoundMenu(sf::RenderWindow& window, const sf::Font& font, float initialVolume)
    : mWindow(window),
    mFont(font),
    mIncreaseVolumeButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(window.getSize().x / 2.f, 300.f)),
    mDecreaseVolumeButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(window.getSize().x / 2.f, 400.f)),
    mBackButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(window.getSize().x / 2.f, 500.f)),
    mVolume(initialVolume),
    mBackButtonPressed(false)
{
    // Baþlýk metni "Sound Settings"
    mTitleText.setFont(mFont);
    mTitleText.setString("Sound Settings");
    mTitleText.setCharacterSize(48);
    mTitleText.setFillColor(sf::Color::White);
    sf::FloatRect titleBounds = mTitleText.getLocalBounds();
    mTitleText.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
    mTitleText.setPosition(window.getSize().x / 2.f, 100.f); // Ekranýn üst kýsmýna yerleþtirildi

    // Ses seviyesi metni
    mVolumeText.setFont(mFont);
    mVolumeText.setCharacterSize(36); // Daha büyük ve okunabilir boyut
    mVolumeText.setFillColor(sf::Color::Cyan);
    mVolumeText.setStyle(sf::Text::Bold);
    sf::FloatRect volumeBounds = mVolumeText.getLocalBounds();
    mVolumeText.setOrigin(volumeBounds.width / 2.f, volumeBounds.height / 2.f);
    mVolumeText.setPosition(window.getSize().x / 2.f, 200.f); // Baþlýðýn hemen altýna yerleþtirildi
    updateVolumeText(); // Baþlangýç metni

    // Buton metinleri
    mIncreaseVolumeButton.setFont(mFont);
    mIncreaseVolumeButton.setText("Increase Volume");

    mDecreaseVolumeButton.setFont(mFont);
    mDecreaseVolumeButton.setText("Decrease Volume");

    mBackButton.setFont(mFont);
    mBackButton.setText("Back");
}

void SoundMenu::handleEvent(const sf::Event& event)
{
    mIncreaseVolumeButton.handleEvent(event, mWindow);
    mDecreaseVolumeButton.handleEvent(event, mWindow);
    mBackButton.handleEvent(event, mWindow);

    if (mIncreaseVolumeButton.isClicked())
    {
        if (mVolume < 100.f)
        {
            mVolume += 10.f;
            updateVolumeText(); // Metni güncelle
        }
        std::cout << "Ses Seviyesi: " << mVolume << std::endl;
    }
    else if (mDecreaseVolumeButton.isClicked())
    {
        if (mVolume > 0.f)
        {
            mVolume -= 10.f;
            updateVolumeText(); // Metni güncelle
        }
        std::cout << "Ses Seviyesi: " << mVolume << std::endl;
    }
    else if (mBackButton.isClicked())
    {
        mBackButtonPressed = true;
    }

    // ESC ile geri dön
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        mBackButtonPressed = true;
    }
}

void SoundMenu::update()
{
    mIncreaseVolumeButton.update(mWindow);
    mDecreaseVolumeButton.update(mWindow);
    mBackButton.update(mWindow);
    // Ses seviyesi ayarlarýný sýnýrlýyoruz
    if (mVolume > 100.f)
        mVolume = 100.f;
    if (mVolume < 0.f)
        mVolume = 0.f;
}

void SoundMenu::render()
{
    mWindow.draw(mVolumeText); // Ses seviyesi metni
    mWindow.draw(mTitleText);
    mIncreaseVolumeButton.render(mWindow);
    mDecreaseVolumeButton.render(mWindow);
    mBackButton.render(mWindow);
}

float SoundMenu::getVolume() const
{
    return mVolume;
}

void SoundMenu::setVolume(float volume)
{
    mVolume = volume;
    if (mVolume < 0.f) mVolume = 0.f;
    if (mVolume > 100.f) mVolume = 100.f;
}

bool SoundMenu::isBackButtonPressed() const
{
    return mBackButtonPressed;
}

void SoundMenu::updateVolumeText()
{
    mVolumeText.setString("Volume: " + std::to_string(static_cast<int>(mVolume)));
}