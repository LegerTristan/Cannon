#pragma once

#include "MoveComponent.h"

const float TIME_FLOW_SPEED = 5.0f;				// Speed of the flow of time.

/// <summary>
/// Inherited from MoveComponent.
/// Allows owner to move in a parabolic trajectory, usefull for balls that need to take in account the gravity.
/// </summary>
class ParabolicMoveComponent : public MoveComponent
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	ParabolicMoveComponent(Entity* entity, Vector2f velocity) : MoveComponent(entity, velocity) {}
	~ParabolicMoveComponent() {}

	/// <summary>
	/// Return the formula of the trajectory used by the ParabolicMoveComponent
	/// </summary>
	/// <returns>The formula of the trajectory</returns>
	virtual Vector2f GetTrajectory() override;

	/// <summary>
	/// Move the player along a parabolic trajectory
	/// The parabolic trajectory use the next formula to calculate owner's position :	X = V0.X * t + P0.X
	///																					Y = (g / 2) * t² + V0.Y * t + P0.Y
	/// Fact : That is g / 2 cause of the Y axis which is inverted.
	/// </summary>
	virtual bool Move() override;

};

