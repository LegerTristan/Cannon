#pragma once

#include "FlickerText.h"

const float HUD_CHARACTER_SIZE = 30.0f;	// Character size of HUD texts
const float HUD_Y_OFFSET = 10.0f;		// Y offset for most part of UI elements of the HUD

const Vector2f WAVE_TEXT_OFFSET = Vector2f(100.0f, 40.0f);

/// <summary>
/// Contains UI elements that is bind to the game such as timer, wave flicker text.
/// </summary>
class HUD
{
public:
	// CONSTRUCTOR & DESTRUCTOR

	HUD();
	~HUD();

	// GETTER

	static Font* GetGameFont();

	/// <summary>
	/// Update text for the game timer
	/// </summary>
	/// <param name="currentTime">Current time of the game</param>
	void UpdateTimerText(const float& currentTime);

	/// <summary>
	/// Update the flicker text for the incoming wave
	/// </summary>
	/// <param name="incomingWave">Boolean that tell if it has an incoming wave or not</param>
	void UpdateWaveText(const bool& incomingWave);

	/// <summary>
	/// Draw all UI elements
	/// </summary>
	/// <param name="window">Game window</param>
	void DrawHUD(RenderWindow* window) const;

protected:

	/// <summary>
	/// Background for the game's UI elements.
	/// </summary>
	Sprite mBackground;

	/// <summary>
	/// Flicker text for displaying an incoming wave.
	/// </summary>
	FlickerText* mWaveText;

	/// <summary>
	/// Text for displaying the timer
	/// </summary>
	Text mTimerText;

	/// <summary>
	/// Font of the game
	/// </summary>
	static Font* mFont;
};

