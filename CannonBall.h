#pragma once

#include "ParabolicMoveComponent.h"
#include "CollisionComponent.h"

template<class T, class Y>
class ScalarUpgradeComponent;

const string CANNON_BALL_TEXTURE = "Assets/Textures/Cannon_Ball.png";

const unsigned int DEFAULT_BALL_LIFE = 1;
const float DEFAULT_BALL_SCALE = 0.2f;
const float BALL_SCALE_SCALAR = 10.f;

/// <summary>
/// Inherit from Entity.
/// A cannon ball is a ball that follows a parabolic trajectory.
/// It is destroyed when colliding withan enemy.
/// </summary>
class CannonBall : public Entity
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	CannonBall(const Vector2f position, const Vector2f velocity);
	~CannonBall() = default;

	Vector2f ComputeScale(const float upgradeValue) const;
	short ComputeLife(const float upgradeValue) const;

	/// <summary>
	/// Inherited from Entity class.
	/// Update display and positiong along the movement, if Move() returns false, then destroy the ball.
	/// </summary>
	/// <param name="window">Game window</param>
	void Update(RenderWindow* window) override;

private:

	/// <summary>
	/// Upgrade for the scale of the ball
	/// </summary>
	static ScalarUpgradeComponent<CannonBall, Vector2f>* mScaleUp;

	/// <summary>
	/// Upgrade for the life of the ball, allowing the cannon's ball to hit multiple enemies.
	/// </summary>
	static ScalarUpgradeComponent<CannonBall, short>* mLifeUp;

	/// <summary>
	/// Current global scale for all balls.
	/// </summary>
	static Vector2f mBallScale;

	/// <summary>
	/// Current global ùax life for all balls.
	/// </summary>
	static short mMaxBallLife;
};

