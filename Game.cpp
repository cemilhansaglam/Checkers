// Game.cpp
#include "Game.hpp"
#include <iostream>

Game::Game()
    : mWindow(sf::VideoMode(1000, 800), "Checkers"),
    mBoard(),
    mIsRunning(true),
    mRestartRequested(false),
    mGameState(GameState::Splash),
    mFont(), // mFont'u baþlatýyoruz
    mSidePanel(mFont), // mSidePanel'i mFont ile baþlatýyoruz
    mCurrentVolume(50.f) // Varsayýlan ses seviyesi
{
    // Yazý tipini yükle
    if (!mFont.loadFromFile("Resources/fonts/Marker Felt.ttf"))
    {
        std::cout << "Yazý tipi yüklenemedi!" << std::endl;
    }

    mBoardView = std::make_unique<BoardView>(mBoard);

    mInputHandler = std::make_unique<InputHandler>(mBoard, *this);

    mWindow.setFramerateLimit(60);

    // Ana menüyü oluþtur
    mMainMenu = std::make_unique<MainMenu>(mWindow);

    // Splash ekranýný oluþtur
    mSplashState = std::make_unique<SplashState>(mWindow);

    // GameOverState henüz oluþturulmuyor, oyun bittiðinde oluþturulacak

    // SoundMenu þimdilik nullptr, ihtiyacýmýz olduðunda oluþturacaðýz.
    mSoundMenu = nullptr;

    // Baþlangýçta InputHandler'a mevcut volume'u iletelim
    mInputHandler->setVolume(mCurrentVolume);
}

void Game::run()
{
    while (mIsRunning)
    {
        processEvents();
        update();
        render();

        if (mRestartRequested)
        {
            resetGame();
            mRestartRequested = false;
        }
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            mIsRunning = false;
            mWindow.close();
        }
        else if (mGameState == GameState::Splash)
        {
            mSplashState->handleEvent(event);
        }
        else if (mGameState == GameState::MainMenu)
        {
            mMainMenu->handleEvent(event);

            if (mMainMenu->isPlayButtonPressed())
            {
                mGameState = GameState::Playing;
            }
            else if (mMainMenu->isQuitButtonPressed())
            {
                mIsRunning = false;
                mWindow.close();
            }
        }
        else if (mGameState == GameState::Playing)
        {
            // Yan panelin butonlarýný iþlemek için
            mSidePanel.handleEvent(event, mWindow);

            if (mSidePanel.isUndoButtonClicked())
            {
                if (mBoard.undoMove())
                {
                    std::cout << "Hamle geri alýndý." << std::endl;
                }
                else
                {
                    std::cout << "Geri alýnacak hamle yok." << std::endl;
                }
            }
            if (mSidePanel.isPauseButtonClicked())
            {
                mGameState = GameState::Paused;
                mPauseMenu = std::make_unique<PauseMenu>(mWindow);
            }
            else
            {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                {
                    mGameState = GameState::Paused;
                    mPauseMenu = std::make_unique<PauseMenu>(mWindow);
                }
                else
                {
                    mInputHandler->handleEvent(event, mWindow);
                }
            }
        }
        else if (mGameState == GameState::Paused)
        {
            mPauseMenu->handleEvent(event);
            // PauseMenu'de "Sound Settings" butonu basýldýðýnda GameState'i SoundMenu yapacaðýz
            if (mPauseMenu->isSoundSettingsRequested())
            {
                // SoundMenu'yu mevcut volume ile oluþtur
                mGameState = GameState::SoundMenu;
                mSoundMenu = std::make_unique<SoundMenu>(mWindow, mFont, mCurrentVolume);
            }
        }
        else if (mGameState == GameState::GameOver)
        {
            mGameOverState->handleEvent(event);
        }

        else if (mGameState == GameState::SoundMenu)
        {
            mSoundMenu->handleEvent(event);

            if (mSoundMenu->isBackButtonPressed())
            {
                mGameState = GameState::Paused; // Ses menüsünden geri dönünce pause menüsüne dönüyoruz
            }
        }
    }
}

void Game::update()
{
    if (mGameState == GameState::Splash)
    {
        mSplashState->update();
        if (mSplashState->isFinished())
        {
            mGameState = GameState::MainMenu;
        }
    }
    else if (mGameState == GameState::MainMenu)
    {
        mMainMenu->update();
    }
    else if (mGameState == GameState::Playing)
    {
        mSidePanel.update(mWindow, mBoard.isWhiteTurn());

        if (mBoard.isGameOver())
        {
            mGameState = GameState::GameOver;
            mWinner = mBoard.getWinner();
            mGameOverState = std::make_unique<GameOverState>(mWindow, mWinner);
        }
    }
    else if (mGameState == GameState::Paused)
    {
        mPauseMenu->update();

        if (mPauseMenu->isResumeRequested())
        {
            mGameState = GameState::Playing;
        }
        else if (mPauseMenu->isRestartRequested())
        {
            resetGame();
        }
        else if (mPauseMenu->isReturnToMenuRequested())
        {
            mGameState = GameState::MainMenu;
        }
        else if (mPauseMenu->isExitRequested())
        {
            mIsRunning = false;
            mWindow.close();
        }
    }
    else if (mGameState == GameState::GameOver)
    {
        mGameOverState->update();

        if (mGameOverState->isRestartRequested())
        {
            resetGame();
        }
        else if (mGameOverState->isReturnToMenuRequested())
        {
            mGameState = GameState::MainMenu;
        }
        else if (mGameOverState->isExitRequested())
        {
            mIsRunning = false;
            mWindow.close();
        }
    }
    else if (mGameState == GameState::SoundMenu)
    {
        mSoundMenu->update();
        float newVolume = mSoundMenu->getVolume();

        if (newVolume != mCurrentVolume)
        {
            mCurrentVolume = newVolume;
            mInputHandler->setVolume(mCurrentVolume); // Ses seviyesi ayarýný burada güncelleyin
        }

        if (mSoundMenu->isBackButtonPressed())
        {
            mGameState = GameState::Paused;
        }
    }
}

void Game::render()
{
    mWindow.clear();

    if (mGameState == GameState::Splash)
    {
        mSplashState->render();
    }
    else if (mGameState == GameState::MainMenu)
    {
        mMainMenu->render();
    }
    else if (mGameState == GameState::Playing)
    {
        mBoardView->draw(mWindow);
        mSidePanel.render(mWindow); // Yan paneli çiz
    }
    else if (mGameState == GameState::Paused)
    {
        mBoardView->draw(mWindow);
        mSidePanel.render(mWindow); // Yan paneli çiz
        mPauseMenu->render();
    }
    else if (mGameState == GameState::GameOver)
    {
        mGameOverState->render();
    }
    else if (mGameState == GameState::SoundMenu)
    {
        mSoundMenu->render();
    }

    mWindow.display();
}

void Game::resetGame()
{
    mBoard.reset();
    mBoardView = std::make_unique<BoardView>(mBoard);
    mInputHandler = std::make_unique<InputHandler>(mBoard, *this);
    mInputHandler->setVolume(mCurrentVolume); // Reset sonrasý da volume korunsun
    mGameState = GameState::Playing;
}
