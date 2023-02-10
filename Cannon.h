#pragma once

#include "Entity.h"

template<class T, class Y>
class ScalarUpgradeComponent;

class Gauge;

const Vector2f DEFAULT_SCALE = Vector2f(0.2f, 0.2f);
const float DEFAULT_ROTATION = 30.0f;							// Default rotation at the start of the game
const Vector2f MOVING_PART_OFFSET = Vector2f(20.0f, -25.0f);	// Offset of the moving part in order to have a correct location

const float ADDING_ANGLE = 60.0f;								// Rotation angle to add when moving the cannon			
const float MAX_CANNON_ROTATION = 90.0f;						// Maximum rotation's angle of the cannon
const float MIN_CANNON_ROTATION = 20.0f;						// Minimum rotation's angle of the cannon
const float MAX_CANNON_FIRE_POWER = 125.0f;						// Maximum fire's power of the cannon
const float MIN_CANNON_FIRE_POWER = 75.0f;						// Minimum fire's power of the cannon

const float RADIAN_CONVERSION = (3.1415f / 180.0f);				// Convert degrees to radian.
const float ROTATION_OFFSET = 90.0f;							// Offset applied to the texture in order to orient the cannon.
const float DIST_FROM_CANNON = 50.0f;							// Distance from the origin of the texture.

const float DEFAULT_LOAD_SPEED = 15.0f;							// Default fire load speed of the cannon
const float LOAD_SPEED_SCALAR = 10.0f;							// Scalar applied to the rank of the upgrade "Fire load speed"

/// <summary>
/// Moving direction of the cannon.
/// </summary>
enum class CannonMove
{
	NONE = 0,
	UP = 1,
	DOWN = 2,
};


/// <summary>
/// A cannon is a launcher of a CannonBalls, it aims and charges to shoot a CannonBall.
/// It is controlled by the player via inputs.
/// Inherit from Sprite class of SFMLs graphics lib
/// </summary>
class Cannon : public Sprite
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	Cannon(Vector2f position);
	~Cannon();

	// GETTERS & SETTER

	Sprite GetMovingPartSprite() const;
	bool GetPreparingFire() const;
	float GetFireLoadPower(const float upgradeValue) const;

	void SetPreparingFire(const bool& prepareFire);
	void SetMoveState(const CannonMove& state);

	/// <summary>
	/// Update rotation angle of the moving part of the cannon sprite
	/// </summary>
	void UpdateRotAngle();

	/// <summary>
	/// Update fire power if it is currently charging
	/// Update cannon display as well as his fire power's gauge
	/// </summary>
	/// <param name="window"></param>
	void Update(RenderWindow* window);

	/// <summary>
	/// If not started to charge his fire, then turn it on
	/// If true, then increase fire power along the delta time and fill the gauge in function of the current fire power.
	/// </summary>
	void UpdateFirePower();

	/// <summary>
	/// Check if the cannon can shoot another ball of need to recharge (based on mShootTime)
	/// If can shoot, then spawn a new ball at the end of the cannon and initialize it.
	/// Reset all shooting parameters
	/// </summary>
	void LaunchCannonBall();

	/// <summary>
	/// Increase the rank of the fire load speed upgrade.
	/// </summary>
	void UpgradeSpeed();

private:

	/// <summary>
	/// Upgrade of the fire load speed of the cannon.
	/// </summary>
	ScalarUpgradeComponent<Cannon, float>* mFireLoadUp;

	/// <summary>
	/// Sprite of moving part of the cannon
	/// </summary>
	Sprite mMovingPartSprite;

	/// <summary>
	/// Fire power's gauge of the cannon
	/// </summary>
	Gauge* mCannonGauge;

	/// <summary>
	/// Current moving direction of the cannon.
	/// </summary>
	CannonMove mMoveState = CannonMove::NONE;

	/// <summary>
	/// Fire rate of the cannon.
	/// </summary>
	float mFireRate = 1.0f;

	/// <summary>
	/// Fire time is the time that the currentTime of the engine needs to exceed in order to shoot.
	/// </summary>
	float mFireTime = 0.0f;

	/// <summary>
	/// Fire Power is the current power of the cannon for his next shoot.
	/// </summary>
	float mFirePower = MIN_CANNON_FIRE_POWER;

	/// <summary>
	/// Handle if cannon is currently charging for the next shoot or not.
	/// </summary>
	bool mIsCharging = true;
};
