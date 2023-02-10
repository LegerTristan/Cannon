#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

/// <summary>
/// A Game state is a particular state of the game.
/// Similar to a specific window of the game such as the level window ou the menu window.
/// </summary>
class GameState
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	GameState() = default;
	virtual ~GameState() = default;


	/// <summary>
	/// Init features that is needed for the good work of the state.
	/// </summary>
	virtual void InitFeatures() = 0;

	/// <summary>
	/// Update the state, this method needs to be called in a loop
	/// </summary>
	/// <param name="window">Game window</param>
	virtual void Update(RenderWindow* window) = 0;

protected:
	
	/// <summary>
	/// Sprite of the background of the level
	/// </summary>
	Sprite mLevelBackground;
};

