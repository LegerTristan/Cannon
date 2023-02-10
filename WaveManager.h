#pragma once

#include "Enemy.h"
#include "TimelineComponent.h"

template<class T, class Y>
class ScalarUpgradeComponent;

const Vector2f SPAWN_POS_BOSS = Vector2f(150.0f, 210.0f);		// Boss spawn position

const float DEFAULT_TIME_SPEED = 0.6f;							// Time speed's flow at the start of the game
const float TIME_SPEED_SCALAR = 10.0f;							// Time speed's scalar applied to the wave frequency upgrade

const float SPAWN_ENEMY_OFFSET_X = 50.0f;						// X offset for spawning new enemy
const float SPAWN_GROUND_ENEMY_OFFSET_Y = 60.0f;				// Y offset for spawning new ground enemy

const unsigned int SPAWN_FLOAT_ENEMY_OFFSET_Y_RANGE = 300.0f;	// Range of Y offset for spawning new floating enemy
const unsigned int SPAWN_FLOAT_ENEMY_OFFSET_Y_MIN = 100.0f;		// Min value of Y offset for spawning new floating enemy

const int ENEMY_MAX_NBR_START = 3;								// Max number of enemy at the start
const int COUNTDOWN_BEFORE_WAVE = 4;							// Countdown before a new wave of enemies is incoming
const int DEFAULT_BOSS_APPEARANCE_PERCENTAGE = 2;				// Percentage that a boss appears when a wave is coming

/// <summary>
/// Manager that handle all things in connection with the spawn of enemies such as mas spawn, or waves.
/// </summary>
class WaveManager
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	WaveManager();
	~WaveManager();

	// GETTERS

	float GetCurrentTime() const;
	bool GetIncomingWave() const;

	float ComputeTimeSpeed(const float upgradeRank) const;

	/// <summary>
	/// Update the curent enemy max number the game wan have at the same time.
	///	Also, decrease the wave coutdown and potentially call SpawnWave().
	/// </summary>
	void UpdateEnemySpawn();

	/// <summary>
	/// Decrease the wave countodwn until it comes to 0.
	/// If 0, then update the incoming wave boolean.
	/// </summary>
	void DecreaseWaveCountdown();

	/// <summary>
	/// Spawn a new random enemy
	/// </summary>
	void SpawnEnemy();

	/// <summary>
	/// Spawn a new boss
	/// </summary>
	void SpawnBoss();

	/// <summary>
	/// Decrement current enemies number present in the level.
	/// </summary>
	void DecreaseEnemyNbr();

	/// <summary>
	/// Spawn a new wave of enemies equals to the enemy max number at start (= 3)
	/// </summary>
	void SpawnWave();

	/// <summary>
	/// Initialize upgrade of wave frequency
	/// </summary>
	void InitTimeSpeedUp();


private:

	/// <summary>
	/// Timeline Component that handles appearance of the wave
	/// </summary>
	TimelineComponent<WaveManager>* mWaveTimeline;

	/// <summary>
	/// Upgrade of the wave of enemies frequency 
	/// </summary>
	ScalarUpgradeComponent<WaveManager, float>* mWaveFrequencyUp;
	
	/// <summary>
	/// Time when the manager was constructed.
	/// </summary>
	float mStartTime;

	/// <summary>
	/// Current time of the manager, similar to the current time of the engine but we apply the difference by the start time.
	/// </summary>
	float mCurrentTime;

	/// <summary>
	/// Flow speed of the time.
	/// </summary>
	float mTimeSpeed;

	/// <summary>
	/// Total enemy max number at the same time. This member is not modified by the flow of time.
	/// </summary>
	int mEnemyMaxNbr;

	/// <summary>
	/// Current enemy max number at the same time. This member is modified by the flow of time.
	/// </summary>
	int mCurrentEnemyMaxNbr;

	/// <summary>
	/// Countdown before a new wave appear
	/// </summary>
	int mCountdownBeforeWave;

	/// <summary>
	/// Curent enemies number present if the level.
	/// </summary>
	unsigned int mCurrentEnemiesNbr = 0;

	/// <summary>
	/// Tell if a new wave is coming.
	/// </summary>
	bool mIncomingWave;

	/// <summary>
	/// Tell if the countdown was already decreased in this period where current enemy max nbr is > 0
	/// </summary>
	bool mCountdownWasDecreased = false;

	/// <summary>
	/// Tell if the previous has a boss and so, need to do a random or not for spawning a new boss.
	/// </summary>
	bool mInBossCooldown = false;
};

