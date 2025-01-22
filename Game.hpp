// Game.hpp
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Board.hpp"
#include "BoardView.hpp"
#include "InputHandler.hpp"
#include "MainMenu.hpp"
#include "SplashState.hpp"
#include "GameOverState.hpp"
#include "PauseMenu.hpp"
#include "Button.hpp"
#include "SidePanel.hpp" // Yan paneli dahil edin
#include "SoundMenu.hpp" // SoundMenu'yu ekliyoruz


enum class GameState
{
    Splash,
    MainMenu,
    Playing,
    Paused,
    GameOver,
    SoundMenu // Yeni durum eklendi
};

class Game
{
public:
    Game();
    void run();

    void resetGame();

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow mWindow;
    Board mBoard;
    std::unique_ptr<BoardView> mBoardView;
    std::unique_ptr<InputHandler> mInputHandler;

    bool mIsRunning;

    // Ana men�
    std::unique_ptr<MainMenu> mMainMenu;

    // Splash ekran�
    std::unique_ptr<SplashState> mSplashState;

    // Game Over durumu
    std::unique_ptr<GameOverState> mGameOverState;

    // Pause men�s�
    std::unique_ptr<PauseMenu> mPauseMenu;

    // Sound men�s�
    std::unique_ptr<SoundMenu> mSoundMenu; // Ses men�s� eklendi

    float mCurrentVolume; // Oyunun genel ses seviyesi

    // Oyun durumu
    GameState mGameState;

    // Yeniden ba�latma talebi
    bool mRestartRequested;

    // Kazanan oyuncu
    std::string mWinner;

    // Yaz� tipi
    sf::Font mFont; // mSidePanel'den �nce tan�mlanmal�

    // Yan panel
    SidePanel mSidePanel; // mFont'tan sonra ba�lat�lacak


};

#endif // GAME_HPP
