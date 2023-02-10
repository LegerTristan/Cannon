#pragma once

#include "LifeBar.h"
#include "Gauge.h"

const float MAX_XP_START = 10.0f;						// Max XP needed for lvl up at the satrt of the game
const float LEVEL_CHARACTER_SIZE = 18.0f;				// Character size of level up text
const float XP_SCALAR = 1.8f;							// XP scalar applied at every level up

const Vector2f TEXT_POS = Vector2f(200.f, 15.0f);		// Position of the gauge
const Vector2f LIFEBAR_POS = Vector2f(150.0f, 20.0f);	// Position of the lifebar
const Vector2f GAUGE_SIZE = Vector2f(100.0f, 6.0f);		// Size of the gauge
const Vector2f GAUGE_POS = Vector2f(50.0f, 75.0f);		// Position of the gauge

const Color GAUGE_COLOR = Color(180U, 0U, 255U);		// Color of the gauge

/// <summary>
/// Contains all the informations tied to the player such as HP, level, and current upgrades.
/// </summary>
class Player 
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	Player();
	~Player();

	//GETTER

	LifeBar* GetLifeBar() const;

	/// <summary>
	/// Increment current level and increase max xp amount.
	/// Also, refresh level text on the screen.
	/// </summary>
	void IncreaseLevel();

	/// <summary>
	/// Increase currentXP by adding an amount.
	/// If currentXP > maxXP, then call IncreaseLevel() and reset current xp by the difference between maxXP and currentXP
	/// </summary>
	/// <param name="amount">The a&mount of xp to ad to the current</param>
	void IncreaseXP(const float& amount);

	/// <summary>
	/// Draw player's informations on the screen like lifebar, level gauge etc.
	/// </summary>
	/// <param name="window">Game window</param>
	void DrawPlayerInfo(RenderWindow* window);

private:

	/// <summary>
	/// Player's lifebar
	/// </summary>
	LifeBar* mLifeBar;

	/// <summary>
	/// Player's level gauge
	/// </summary>
	Gauge* mLevelGauge;

	/// <summary>
	/// Player's level displayed in a text
	/// </summary>
	Text mLevelText;

	/// <summary>
	/// Max XP amount needed for level up
	/// </summary>
	float mMaxXP;

	/// <summary>
	/// Current XP of the player
	/// </summary>
	float mCurrentXP;

	/// <summary>
	/// Current level of the player
	/// </summary>
	int mCurrentLevel;
};

