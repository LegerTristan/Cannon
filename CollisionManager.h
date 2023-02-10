#pragma once

#include <vector>
#include "CollisionComponent.h"

using namespace std;

const float PHYSIC_CHECK_RATE = 0.1f;	// Check rate of all collision components in the game.

/// <summary>
/// Manager that handle all things in connection with collisions.
/// </summary>
class CollisionManager
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	CollisionManager();
	~CollisionManager() {}

	// GETTER & SETTER

	bool HasToCheckPhysic();	// Check if it is time to check all collisions components
	void SetLastCheckTime();

	/// <summary>
	/// Update all collision components of the game.
	/// </summary>
	/// <param name="entities">Vector of entities present in the game</param>
	void UpdateCollision(vector<class Entity*>& entities);

	/// <summary>
	/// Decrease life of entites and kill them if it can.
	/// If it is an enemy, call KillByPlayer() method.
	/// </summary>
	/// <param name="_entities">Vector of entites present in the game</param>
	/// <param name="j">Current index of the enemy</param>
	/// <param name="i">Current index of the ball</param>
	void HandleEntityCollision(vector<Entity*>& _entities, unsigned int& j, unsigned int i);

private:

	/// <summary>
	/// Rate of checking collisions. Used for reducing potential lags.
	/// </summary>
	float mPhysicCheckRate;

	/// <summary>
	/// Last time a physic took place.
	/// </summary>
	float mLastCheckTime;

	/// <summary>
	/// Current time of the the engine.
	/// </summary>
	float mCurrentTime;
};

