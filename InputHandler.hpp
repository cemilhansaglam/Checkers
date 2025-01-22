// InputHandler.hpp
#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Board.hpp"

class Game; // Ýleri bildirim

class InputHandler
{
public:
    InputHandler(Board& board, Game& game);

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

    void setVolume(float volume); // Ses seviyesini ayarlamak için yeni fonksiyon

private:
    Board& mBoard;
    Game& mGame;

    sf::SoundBuffer mMoveSoundBuffer;
    sf::Sound mMoveSound;
};

#endif // INPUTHANDLER_HPP
