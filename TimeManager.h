#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

/// <summary>
/// Contains the current time and delta time of the engine.
/// Can be accessed via static call through the singleton instance.
/// </summary>
class TimeManager
{
public:

	// CONSTRUCTOR

	TimeManager();
	~TimeManager() {}

	// GETTERS & SETTER

	float GetDeltaTime() const;
	float GetCurrentTime() const;
	void SetPause(const bool& pause);


	/// <summary>
	/// Update the current via the clock.
	/// </summary>
	void UpdateCurrentTime();

	/// <summary>
	/// Update the last time and set it equal to the current time.
	/// </summary>
	void UpdateLastTime();

	/// <summary>
	/// Calcul the deltaTime.
	/// </summary>
	void CalculateDeltaTime();

private:

	/// <summary>
	/// Clock to update the current time and which has the elapsed time since the last restart function called.
	/// </summary>
	Clock mClock;

	/// <summary>
	/// The currentTime saved by the manager (current frame) and the last time (last frame)
	/// </summary>
	Time mCurrentTime, mLastTime, mRunTime;

	/// <summary>
	/// DeltaTime of the time between current frame and last frame.
	/// </summary>
	float mDeltaTime;

	/// <summary>
	/// Is the time currently paused or not.
	/// </summary>
	bool mIsPaused = false;

};

