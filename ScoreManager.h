#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

const Vector2f SCORE_TEXT_POS = Vector2f(150.0f, 20.0f);		// Position of score's text

const float TEXT_CHARACTER_SIZE = 32.0f;						// Size of the character from the text

/// <summary>
/// Handle score of the level.
/// </summary>
class ScoreManager
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	ScoreManager();
	~ScoreManager() = default;

	/// <summary>
	/// Add score to the current score made and display the new score value.
	/// </summary>
	/// <param name="toAdd">To add to the score</param>
	void AddScore(const unsigned int& toAdd);

	/// <summary>
	/// Center position and zoom text by increasing character size.
	/// Finally, set Text's string in order to display the final score.
	/// </summary>
	void DisplayFinalScore();

	/// <summary>
	/// Draw score's text on the window
	/// </summary>
	/// <param name="window">Game window</param>
	void DrawScore(RenderWindow* window) const;

private:

	/// <summary>
	/// Text to display score.
	/// </summary>
	Text mScoreText;

	/// <summary>
	/// Previous high score registered in the game.
	/// </summary>
	unsigned int mHighScore;

	/// <summary>
	/// Score made in the current level.
	/// </summary>
	unsigned int mScore;
};

