#pragma once
#include "MoveComponent.h"

const float TIME_FLOW_SPEED = 4.0f;				// Speed of the flow of time.

/// <summary>
/// Inherited from MoveComponent.
/// Allows owner to move in a straight trajectory.
/// </summary>
class StraightMoveComponent : public MoveComponent
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	StraightMoveComponent(Entity* entity, const Vector2f& velocity) : MoveComponent(entity, velocity) {}
	~StraightMoveComponent() {}

	/// <summary>
	/// Return the formula of the trajectory used by the StraightMoveComponent
	/// </summary>
	/// <returns>The formula of the trajectory</returns>
	virtual Vector2f GetTrajectory() override;

	/// <summary>
	/// Move the player along a straight trajectory
	/// The next formula is used to calculate owner's position :	X = V0.X * t + P0.X
	///																Y = V0.Y * t + P0.Y
	/// </summary>
	virtual bool Move() override;

};

