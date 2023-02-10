#pragma once

#include "CollisionComponent.h"
#include "MoveComponent.h"
#include "AnimationComponent.h"

template<class T, class Y>
class ScalarUpgradeComponent;

const unsigned int DEFAULT_ENEMY_LIFE = 1;				// Base life of enemies
const float ENEMY_XP_SCALAR = 2.0f;						// Scalar of XP upgrade
const float ENEMY_VELOCITY_SCALAR = 0.4f;				// Scalar of velocity upgrade
const float DEFAULT_ENEMY_VELOCITY_BONUS = 1.0f;		// Default enemies velocity in velocity upgrade

/// <summary>
/// Inherit from Entity class.
/// It is a type of entity which the player needs to destroy before they make him lose his HP.
/// </summary>
class Enemy : public Entity
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	Enemy(const Vector2f position, const Texture* enemyTexture);
	virtual ~Enemy();

	// GETTERS

	float GetXP() const;
	unsigned int GetScore() const;
	float ComputeGlobalVelocity(const float upgradeValue) const;
	float ComputeGlobalXP(const float upgradeValue) const;
	short ComputeGlobalLife(const float upgradeValue) const;

	/// <summary>
	/// Inherited from Entity.
	/// Update enemy display, along his collision and move component.
	/// </summary>
	/// <param name="window">Game window</param>
	virtual void Update(RenderWindow* window);

	/// <summary>
	/// Give XP to player and score for scoreManager and call Die() function.
	/// </summary>
	virtual void KillByPlayer();

	/// <summary>
	/// Reduce player's life by 1 and call Die() function.
	/// </summary>
	virtual void KillByGame();

	/// <summary>
	/// Inherited from Entity.
	/// Call base method and decrease enemy nbr in wave manager.
	/// </summary>
	virtual void Die() override;

protected:

	/// <summary>
	/// Upgrade of the XP given by enemies.
	/// </summary>
	static ScalarUpgradeComponent<Enemy, float>* mXPUp;

	/// <summary>
	/// Upgrade of enemies speed.
	/// </summary>
	static ScalarUpgradeComponent<Enemy, float>* mSpeedUp;

	/// <summary>
	/// Upgrade of enemies speed.
	/// </summary>
	static ScalarUpgradeComponent<Enemy, short>* mLifeUp;

	/// <summary>
	/// Animation component of the enemy
	/// </summary>
	AnimationComponent* mAnimComp;

	/// <summary>
	/// Current global velocity of enemies added to their base velocity.
	/// </summary>
	static float mGlobalVelocity; 

	/// <summary>
	/// New velocity computed after adding global enemies velocity with their base velocity.
	/// </summary>
	Vector2f mVelocity;

	/// <summary>
	/// Quantity of XP this enemy will give to the player.
	/// </summary>
	float mXP;

	/// <summary>
	/// Quantity of XP this enemy will give to the player.
	/// </summary>
	static float mGlobalXP;

	/// <summary>
	/// Quantity of score this enemy will give to the player.
	/// </summary>
	unsigned int mGivenScore;

	/// <summary>
	/// Quantity of life this enemy will have.
	/// </summary>
	static short mGlobalLife;

	/// <summary>
	/// Virtual pure method used to set velocity at the construction of a new instance derived from Enemy
	/// </summary>
	void UpdateVelocity(const Vector2f& baseVelocity);

	/// <summary>
	/// Virtual pure method used to set given XP at the construction of a new instance derived from Enemy
	/// </summary>
	virtual void UpdateXP(const float& baseXP);

	/// <summary>
	/// Virtual pure method used to set life at the construction of a new instance derived from Enemy
	/// </summary>
	virtual void UpdateLife(const short& baseLife);
};