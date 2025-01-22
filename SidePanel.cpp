// SidePanel.cpp
#include "SidePanel.hpp"

SidePanel::SidePanel(const sf::Font& font)
    : mUndoButton(sf::Vector2f(180.f, 40.f), sf::Vector2f(900.f, 200.f)),
    mPauseButton(sf::Vector2f(180.f, 40.f), sf::Vector2f(900.f, 260.f)),
    mIsUndoButtonClicked(false),
    mIsPauseButtonClicked(false)
{
    // Arka plan
    mBackground.setSize(sf::Vector2f(200.f, 800.f));
    mBackground.setPosition(800.f, 0.f);
    mBackground.setFillColor(sf::Color(50, 50, 50));

    // Sýra gösterimi
    mTurnText.setFont(font);
    mTurnText.setCharacterSize(24);
    mTurnText.setFillColor(sf::Color::White);
    mTurnText.setPosition(820.f, 100.f);

    // Geri alma butonu
    mUndoButton.setFont(font);
    mUndoButton.setText("Undo");

    // Pause butonu
    mPauseButton.setFont(font);
    mPauseButton.setText("Pause");
}

void SidePanel::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    mUndoButton.handleEvent(event, window);
    mPauseButton.handleEvent(event, window);
}

void SidePanel::update(const sf::RenderWindow& window, bool isWhiteTurn)
{
    // Sýra gösterimini güncelle
    std::string turn = isWhiteTurn ? "White to move.." : "Black to move.";
    mTurnText.setString(turn);

    // Butonlarý güncelle
    mUndoButton.update(window);
    mPauseButton.update(window);

    mIsUndoButtonClicked = mUndoButton.isClicked();
    mIsPauseButtonClicked = mPauseButton.isClicked();
}

void SidePanel::render(sf::RenderWindow& window)
{
    window.draw(mBackground);
    window.draw(mTurnText);
    mUndoButton.render(window);
    mPauseButton.render(window);
}

bool SidePanel::isUndoButtonClicked() const
{
    return mIsUndoButtonClicked;
}

bool SidePanel::isPauseButtonClicked() const
{
    return mIsPauseButtonClicked;
}
