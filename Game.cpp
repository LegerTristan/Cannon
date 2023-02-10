#include "Game.h"
#include "GameState.h"
#include "LevelState.h"
#include "UpgradeState.h"
#include "UpgradeManager.h"
#include "Cannon.h"
#include "Constants.h"

Game::Game() : mWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cannon")
{
    mTimeManager = new TimeManager();
    mTextureManager = new TextureManager();
    mUpgradeManager = new UpgradeManager();
}

Game::~Game()
{
    delete mTimeManager;
    delete mTextureManager;
    delete mUpgradeManager;

	while (mStates.size() > 0)
	{
		if (mStates.top())
		{
			delete mStates.top();
			mStates.pop();
		}
	}
}

Game* Game::GetInstance()
{
    if (!mInstance)
        mInstance = new Game();

    return mInstance;
}

void Game::AddState(GameState* _newState)
{
	mStates.push(_newState);
	_newState->InitFeatures();
}

void Game::UpdateState()
{
	mStates.top()->Update(&mWindow);
}

void Game::RemoveState()
{
	mStates.pop();
}

void Game::LaunchGame()
{
    while (mWindow.isOpen())
    {
        mTimeManager->UpdateCurrentTime();
        mTimeManager->CalculateDeltaTime();

        Event event;

        while (mWindow.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                mWindow.close();
            }

            if (event.type == Event::KeyPressed)
            {
                // To handle rotation of the cannon
                if (event.key.code == Keyboard::Up)
                    LevelState::GetInstance()->GetCannon()->SetMoveState(CannonMove::UP);
                if (event.key.code == Keyboard::Down)
                    LevelState::GetInstance()->GetCannon()->SetMoveState(CannonMove::DOWN);

                // To shoot
                if (event.key.code == Keyboard::Space)
                    LevelState::GetInstance()->GetCannon()->UpdateFirePower();
            }


            if (event.type == Event::KeyReleased)
            {
                // To handle rotation of the cannon
                if (event.key.code == Keyboard::Up)
                    LevelState::GetInstance()->GetCannon()->SetMoveState(CannonMove::NONE);
                if (event.key.code == Keyboard::Down)
                    LevelState::GetInstance()->GetCannon()->SetMoveState(CannonMove::NONE);

                // To shoot
                if (event.key.code == Keyboard::Space)
                {
                    if (LevelState::GetInstance()->GetCannon()->GetPreparingFire())
                        LevelState::GetInstance()->GetCannon()->LaunchCannonBall();
                }
            }
        }

        mWindow.clear(CLEAR_COLOR);

        UpdateState();

        mWindow.display();
        mTimeManager->UpdateLastTime();
    }
}

void Game::UpdateUpgradeMenu(bool&& _display)
{
    Game::GetInstance()->GetTimer()->SetPause(_display);

    if(_display)
        Game::GetInstance()->AddState(new UpgradeState(mUpgradeManager->GetRandomUpgradePairs(DEFAULT_UPGRADE_PAIR_NBR)));
    else
        Game::GetInstance()->RemoveState();
}
