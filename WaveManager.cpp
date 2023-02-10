#include <iostream>
#include "WaveManager.h"
#include "LevelState.h"
#include "Game.h"
#include "FloatEnemy.h"
#include "SpawnerWraith.h"
#include "GroundEnemy.h"
#include "RunnerGolem.h"
#include "Boss.h"
#include "ScalarUpgradeComponent.h"
#include "EntityFactory.h"


WaveManager::WaveManager()
{
	mStartTime = mCurrentTime = Game::GetInstance()->GetTimer()->GetCurrentTime();
	mTimeSpeed = DEFAULT_TIME_SPEED;
	mCurrentEnemyMaxNbr = 0;
	mEnemyMaxNbr = ENEMY_MAX_NBR_START;
	mCountdownBeforeWave = COUNTDOWN_BEFORE_WAVE;
	mIncomingWave = false;
	mCountdownWasDecreased = false;

	// Set wave timeline
	mWaveTimeline = new TimelineComponent<WaveManager>(this, &WaveManager::SpawnEnemy,
		0.5f, 1.0f, true, 0.6f * mEnemyMaxNbr);

	mWaveFrequencyUp = nullptr;
}

WaveManager::~WaveManager()
{
	if (mWaveTimeline)
	{
		delete mWaveTimeline;
		mWaveTimeline = nullptr;
	}
}

float WaveManager::GetCurrentTime() const
{
	return mCurrentTime;
}

bool WaveManager::GetIncomingWave() const
{
	return mIncomingWave;
}

float WaveManager::ComputeTimeSpeed(const float _upgradeRank) const
{
	return DEFAULT_TIME_SPEED + (_upgradeRank / TIME_SPEED_SCALAR);
}

void WaveManager::UpdateEnemySpawn()
{
	mCurrentTime = Game::GetInstance()->GetTimer()->GetCurrentTime();

	float elapsedTime = (mCurrentTime - mStartTime) * mTimeSpeed;

	mCurrentEnemyMaxNbr = (int)(sinf(elapsedTime) * mEnemyMaxNbr);

	if (mIncomingWave)
		SpawnWave();		

	if (mCurrentEnemyMaxNbr >= 0)
	{
		if (mCurrentEnemiesNbr < (unsigned int)mCurrentEnemyMaxNbr)
			SpawnEnemy();

		DecreaseWaveCountdown();
	}
	else
		mCountdownWasDecreased = false;

	mWaveTimeline->UpdateTimeline();
}

void WaveManager::DecreaseWaveCountdown()
{
	if (!mIncomingWave && !mCountdownWasDecreased && mCurrentEnemyMaxNbr >= mEnemyMaxNbr)
	{
		mCountdownBeforeWave--;
		mCountdownWasDecreased = !mCountdownWasDecreased;
		if (mCountdownBeforeWave == 0)
			mIncomingWave = true;
	}
}

void WaveManager::SpawnEnemy()
{
	if (rand() % 2 == 0)
	{
		if (rand() % 10 <= 2)
		{
			EntityFactory::CreateEntity<SpawnerWraith>(Vector2f(WINDOW_WIDTH + SPAWN_ENEMY_OFFSET_X,
				(rand() % SPAWN_FLOAT_ENEMY_OFFSET_Y_RANGE) + SPAWN_FLOAT_ENEMY_OFFSET_Y_MIN));
		}
		else
		{
			EntityFactory::CreateEntity<FloatEnemy>(Vector2f(WINDOW_WIDTH + SPAWN_ENEMY_OFFSET_X,
				(rand() % SPAWN_FLOAT_ENEMY_OFFSET_Y_RANGE) + SPAWN_FLOAT_ENEMY_OFFSET_Y_MIN));
		}
	}
	else
	{
		if (rand() % 10 <= 3)
		{
			EntityFactory::CreateEntity<RunnerGolem>(
				Vector2f(WINDOW_WIDTH + SPAWN_ENEMY_OFFSET_X, WINDOW_HEIGHT - SPAWN_GROUND_ENEMY_OFFSET_Y));
		}
		else
		{
			EntityFactory::CreateEntity<GroundEnemy>(
				Vector2f(WINDOW_WIDTH + SPAWN_ENEMY_OFFSET_X, WINDOW_HEIGHT - SPAWN_GROUND_ENEMY_OFFSET_Y));
		}
	}

	mCurrentEnemiesNbr++;
}

void WaveManager::SpawnBoss()
{
	EntityFactory::CreateEntity<Boss>(Vector2f(WINDOW_WIDTH + SPAWN_POS_BOSS.x, WINDOW_HEIGHT - SPAWN_POS_BOSS.y));
	mInBossCooldown = true;
}

void WaveManager::DecreaseEnemyNbr()
{
	mCurrentEnemiesNbr--;
}

void WaveManager::SpawnWave()
{
	mWaveTimeline->Start();
	mIncomingWave = false;
	mCountdownBeforeWave = COUNTDOWN_BEFORE_WAVE;
	mEnemyMaxNbr++;

	if (!mInBossCooldown && rand() % DEFAULT_BOSS_APPEARANCE_PERCENTAGE == 0)
		SpawnBoss();
	else
		mInBossCooldown = false;

}

void WaveManager::InitTimeSpeedUp()
{
	mWaveFrequencyUp = new ScalarUpgradeComponent<WaveManager, float>(this, &WaveManager::ComputeTimeSpeed, mTimeSpeed,
		"Wave frequency increase !", "Assets/Textures/Up_Wave_Frequency.png", UpgradeType::ENEMY, 3);
}
