#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

#include "TimeManager.h"
#include "TextureManager.h"

class GameState;
class UpgradeManager;

using namespace std;
using namespace sf;

const Color CLEAR_COLOR = Color(240, 240, 240, 255);	// Background color when window clear method is called.

/// <summary>
/// Main class. Handle GameState and update the last one that will be displayed on screen.
/// Contains also a TimeManager and TextureManager to handle elements that is necessary in every state.
/// </summary>
class Game
{
public:

	// CONSTRUCTORS & DESTRUCTORS

	Game();
	~Game();

	// GETTERS

	static Game* GetInstance();
	inline TimeManager* GetTimer() const;
	inline TextureManager* GetTextureManager() const;
	inline UpgradeManager* GetUpgradeManager() const;

	/// <summary>
	/// Add a new state to the stack of states in the game and init state's features.
	/// </summary>
	/// <param name="newState">New state to add in the game</param>
	void AddState(GameState* newState);

	/// <summary>
	/// Call the method Update(RenderWindow* window) of the last state in the stack
	/// </summary>
	void UpdateState();

	/// <summary>
	/// Remove the last state in the stack
	/// </summary>
	void RemoveState();

	/// <summary>
	/// Main loop of the program.
	/// While the window is open, the game continues.
	/// </summary>
	void LaunchGame();

	/// <summary>
	/// Display the upgarde menu via a new state and pause the timer manager,  if display is true.
	/// Else close the upgrade menu by removing the upgrade state and restart the TimerManager.
	/// </summary>
	/// <param name="display">Handle if the upgrade menu will be display or not</param>
	void UpdateUpgradeMenu(bool&& display);

private:

	/// <summary>
	/// Stack of GameStates
	/// </summary>
	stack<GameState*> mStates;

	/// <summary>
	/// Window of the game
	/// </summary>
	RenderWindow mWindow;

	/// <summary>
	/// Handle every elements bind to the time
	/// </summary>
	TimeManager* mTimeManager;

	/// <summary>
	/// Contains all the textures that was load at least one time.
	/// </summary>
	TextureManager* mTextureManager;

	/// <summary>
	/// Contains references to every upgardes in the game and a reference to the upgrade menu and state.
	/// </summary>
	UpgradeManager* mUpgradeManager;

	/// <summary>
	/// Singleton instance of the game
	/// </summary>
	static Game* mInstance;

};

TextureManager* Game::GetTextureManager() const
{
	return mTextureManager;
}

inline UpgradeManager* Game::GetUpgradeManager() const
{
	return mUpgradeManager;
}

TimeManager* Game::GetTimer() const
{
	return mTimeManager;
}

