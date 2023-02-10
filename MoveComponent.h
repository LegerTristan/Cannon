#pragma once

#include "EntityComponent.h"

const float DEFAULT_MIN_BOUNDARY = -5.0f;	// Default minimal boundaries in X and Y axis for all entity that have a move component.
const float g = 9.8f;						// Constant of gravity's acceleration, defined here to be used in any subclass
											// that needs it.

const float PADDING_HEIGHT = 50.0f;			// Height padding for the screen boundary

/// <summary>
/// Component that allows is Owner to move based on a velocity passed in constructor
/// Move method needs to be override.
/// </summary>
class MoveComponent : public EntityComponent
{
public:

	// CONSTRUCTOR & DESTRUCTOR 

	MoveComponent(Entity* entity, Vector2f velocity);
	~MoveComponent() {}

	/// <summary>
	/// Return the formula of the trajectory used by the MoveComponent
	/// </summary>
	/// <returns>The formula of the trajectory</returns>
	virtual Vector2f GetTrajectory() = 0;

	/// <summary>
	/// Virtual pure method to move the owner along a predifined type of Movement
	/// </summary>
	virtual bool Move() = 0;

	/// <summary>
	/// Check if owner of this component is outside the screen.
	/// </summary>
	/// <returns>True if his position is below the minimal boundaries or above the maximal boundaries.</returns>
	bool IsOwnerOutsideScreen() const;

protected:

	/// <summary>
	/// Velocity of the component and so the Owner.
	/// </summary>
	Vector2f mVelocity;

	/// <summary>
	/// Initial position of the owner of the component.
	/// </summary>
	Vector2f mInitialPos;

	/// <summary>
	/// Initial time corresponds to the time were the component was created.
	/// </summary>
	float mInitialTime;

	/// <summary>
	/// Current time of the component and so the engine.
	/// </summary>
	float mCurrentTime;
};

