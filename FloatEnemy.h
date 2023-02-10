#pragma once

#include "Enemy.h"
#include "FloatMoveComponent.h"

const string FLOAT_ENEMY_TEXTURE = "Assets/Textures/Wraith_Walking_1.png";	// Path of the texture

const Vector2f FLOAT_ENEMY_VELOCITY = Vector2f(-8.0f, 0.0f);				// Velocity of floating enemy
const Vector2f FLOAT_ENEMY_SCALE = Vector2f(0.3f, 0.3f);					// Scale of floating enemy

const float FLOAT_ENEMY_XP = 7.0f;											// XP of floating enemy
const unsigned int FLOAT_ENEMY_SCORE = 8;									// Score of floating enemy

/// <summary>
/// Inherit from Enemy class.
/// It is a special enemy that move with a floating trajectory.
/// Perfect for representing aerial enemy.
/// </summary>
class FloatEnemy : public Enemy
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	FloatEnemy(const Vector2f& position);
	FloatEnemy(const Vector2f& position, const string& texturePath);
	~FloatEnemy() {}
};

