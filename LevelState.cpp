#include <iostream>

#include "LevelState.h"
#include "CollisionManager.h"
#include "UpgradeManager.h"
#include "WaveManager.h"
#include "ScoreManager.h"
#include "HUD.h"
#include "GroundEnemy.h"
#include "FloatEnemy.h"
#include "Player.h"
#include "Cannon.h"
#include "Game.h"

LevelState::LevelState()
{
	mWaveManager = new WaveManager();
	mCollisionManager = new CollisionManager();
	mHUD = new HUD();
	mScoreManager = new ScoreManager();

	mCannon = nullptr;
	mPlayer = nullptr;
}

LevelState::~LevelState()
{
	delete mCannon;
	
	for (unsigned int i = 0; i < mEntities.size(); ++i)
	{
		delete mEntities[i];
	}

	delete mCollisionManager;
	delete mWaveManager;
	delete mScoreManager;
	delete mHUD;
	delete mPlayer;
}

Cannon* LevelState::GetCannon() const
{
	return mCannon;
}

WaveManager* LevelState::GetWaveManager() const
{
	return mWaveManager;
}

CollisionManager* LevelState::GetCollisionManager() const
{
	return mCollisionManager;
}

ScoreManager* LevelState::GetScoreManager() const
{
	return mScoreManager;
}

Player* LevelState::GetPlayer() const
{
	return mPlayer;
}

LevelState* LevelState::GetInstance()
{
	if (!mInstance)
		mInstance = new LevelState();

	return mInstance;
}

void LevelState::InitFeatures()
{
	mWaveManager->InitTimeSpeedUp();

	mPlayer = new Player();

	mCannon = new Cannon({ CANNON_POS_X, WINDOW_HEIGHT - CANNON_POS_Y });

	mLevelBackground.setTexture(*Game::GetInstance()->GetTextureManager()->
		GetTexture("Assets/Textures/Cannon_Background.png").get());
}

void LevelState::Update(RenderWindow* _window)
{
	_window->draw(mLevelBackground);

	if (mPlayer->GetLifeBar()->GetPlayerLife() > 0)
	{
		mCannon->UpdateRotAngle();
		mScoreManager->DrawScore(_window);

		mWaveManager->UpdateEnemySpawn();

		UpdateEntities(_window);

		if (mCollisionManager->HasToCheckPhysic())
		{
			mCollisionManager->UpdateCollision(mEntities);
			mCollisionManager->SetLastCheckTime();
		}

		mHUD->UpdateTimerText(mWaveManager->GetCurrentTime());
		mHUD->UpdateWaveText(mWaveManager->GetIncomingWave());
		mHUD->DrawHUD(_window);

		mPlayer->DrawPlayerInfo(_window);
	}
	else
	{
		mScoreManager->DisplayFinalScore();
		mScoreManager->DrawScore(_window);
	}
}

void LevelState::UpdateEntities(RenderWindow* _window)
{
	// Update all entities
	for (unsigned int i = 0; i < mEntities.size(); ++i)
		mEntities[i]->Update(_window);

	// Update cannon
	mCannon->Update(_window);
}

void LevelState::AddEntity(Entity* _entity)
{
	mEntities.push_back(_entity);
}

void LevelState::RemoveEntity(Entity* _entity)
{
	if (!_entity)
		return;

	auto itEntity = find(mEntities.begin(), mEntities.end(), _entity);

	if (itEntity != mEntities.end())
		mEntities.erase(itEntity);
}

void LevelState::ReduceHP(const int& _amount)
{
	mPlayer->GetLifeBar()->DecreaseHP(_amount);
}
