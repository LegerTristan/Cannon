#pragma once

#include "Enemy.h"
#include "StraightMoveComponent.h"

const string GROUND_ENEMY_TEXTURE = "Assets/Textures/Golem_Walking_1.png";	// Path of the texture

const float GROUND_ENEMY_XP = 4.0f;											// XP given by ground enemies

const unsigned int GROUND_ENEMY_SCORE = 5;									// Score given by grounds enemies

const Vector2f GROUND_ENEMY_VELOCITY = Vector2f(-10.0f, 0.0f);				// Velocity of ground enemies
const Vector2f GROUND_ENEMY_SCALE = Vector2f(0.25f, 0.25f);					// Scale of ground enemies

/// <summary>
/// Inherit from Enemy class.
/// It is a special enemy that move with a straight trajectory.
/// Perfect for representing ground enemy.
/// </summary>
class GroundEnemy : public Enemy
{
public:

	// CONSTRUCTORS & DESTRUCTOR

	GroundEnemy(const Vector2f& position);
	GroundEnemy(const Vector2f& position, const string& texturePath);
	~GroundEnemy() {}
};

