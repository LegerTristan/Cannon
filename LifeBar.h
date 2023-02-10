#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

const int DEFAULT_PLAYER_LIFE = 3;			// Default lifes of player, when an enemy pass outside the screen,
											// it takes one life from the player

const float SPACE_BETWEEN_LIFE = 30.0f;		// Space between two life sprite
const Vector2f HEART_SPRITE_SCALE = Vector2f(0.05f, 0.05f);

/// <summary>
/// UI class that represents player's life.
/// </summary>
class LifeBar
{
public:

	// CONSTRUCTORS & DESTRUCTOR

	LifeBar(Vector2f position);
	~LifeBar() {}

	// GETTER

	int GetPlayerLife() const;

	/// <summary>
	/// Draw all heart sprites
	/// </summary>
	/// <param name="window">Game window</param>
	void DrawHP(RenderWindow* window);

	/// <summary>
	/// Reduce Player HP by the amount passed in param.
	/// Also, set transparent last life removed.
	/// </summary>
	/// <param name="amount">Amount of HP removed</param>
	void DecreaseHP(const int& amount);

private:

	/// <summary>
	/// Sprites used to represent life points of the player
	/// </summary>
	Sprite mLifeSprites[DEFAULT_PLAYER_LIFE];

	/// <summary>
	/// Position of the sprite.
	/// </summary>
	Vector2f mPosition;

	/// <summary>
	/// Current player's life
	/// </summary>
	int mPlayerLife;
};

