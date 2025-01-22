// InputHandler.cpp
#include "InputHandler.hpp"
#include <iostream>

InputHandler::InputHandler(Board& board, Game& game)
    : mBoard(board), mGame(game)
{
    if (!mMoveSoundBuffer.loadFromFile("Resources/audio/Wing.wav"))
    {
        std::cout << "Ses dosyasý yüklenemedi!" << std::endl;
    }
    mMoveSound.setBuffer(mMoveSoundBuffer);

}

void InputHandler::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        if (event.mouseButton.button == sf::Mouse::Left && !mBoard.isGameOver())
        {
            if (!mBoard.selectPieceAt(mousePosF.x, mousePosF.y))
            {
                // Eðer bir taþ seçiliyse ve seçili taþýn hareketi baþarýsýzsa, taþý hareket ettirmeye çalýþ
                if (!mBoard.moveSelectedPieceTo(mousePosF.x, mousePosF.y))
                {
                    mBoard.deselectPiece();
                }
                else
                {
                    // Hareket baþarýlý, sesi çal
                    mMoveSound.play();
                }
            }
        }
    }
}
void InputHandler::setVolume(float volume)
{
    // Volume'u 0.0f - 100.0f aralýðýna sabitleyebilirsiniz
    if (volume < 0.f) volume = 0.f;
    if (volume > 100.f) volume = 100.f;

    mMoveSound.setVolume(volume);
}
