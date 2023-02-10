#pragma once

#include "MoveComponent.h"

template<class T, typename Y>
class ScalarUpgradeComponent;

const float DEFAULT_FLOAT_VARIATION = 10.0f;	// Default float variation in floating upgrade
const float FLOAT_VARIATION_SCALAR = 2.5f;		// Scalar for floating variation upgrade.

const float FLOW_SPEED = 4.0f;				// Speed of the flow of time.

/// <summary>
/// Inherited from MoveComponent.
/// Allows owner to move in a straight trajectory with a floating like movement on Y axis.
/// </summary>
class FloatMoveComponent : public MoveComponent
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	FloatMoveComponent(Entity* entity, Vector2f velocity);
	~FloatMoveComponent() {}

	// GETTER

	float ComputeFloatVariation(const float upgradeValue) const;

	/// <summary>
	/// Return the formula of the trajectory used by the FloatMoveComponent
	/// </summary>
	/// <returns>The formula of the trajectory</returns>
	virtual Vector2f GetTrajectory() override;

	/// <summary>
	/// Move the player along a straight trajectory with a floating like movement on Y axis.
	/// The next formula is used to calculate owner's position :	X = V0.X * t + P0.X
	///																Y = sinf(t) * mFloatVariation + P0.Y
	/// </summary>
	virtual bool Move() override;

private:

	/// <summary>
	/// Upgrade of the variation float of floating entities.
	/// </summary>
	static ScalarUpgradeComponent<FloatMoveComponent, float>* mVariationUp;

	/// <summary>
	/// Scale used on the returned value of the sinf(t) to increase to floating movement.
	/// </summary>
	static float mFloatVariation;

};

