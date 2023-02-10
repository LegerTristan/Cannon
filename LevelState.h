#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameState.h"
#include "Constants.h"

class CollisionManager;
class UpgradeManager;
class WaveManager;
class ScoreManager;
class Entity;
class HUD;
class Player;
class Cannon;

using namespace std;
using namespace sf;

const float CANNON_POS_X = 50.0f;
const float CANNON_POS_Y = 30.0f;

/// <summary>
/// Game class that handle all the necessary elements in order to make the game playable.
/// All of his features is divided between managers and entities, except the management of the entities.
/// </summary>
class LevelState : public GameState
{
public:
	// CONSTRUCTOR & DESTRUCTOR

	LevelState();
	~LevelState();

	// GETTERS

	Cannon* GetCannon() const;
	WaveManager* GetWaveManager() const;
	CollisionManager* GetCollisionManager() const;
	ScoreManager* GetScoreManager() const;
	Player* GetPlayer() const;
	static LevelState* GetInstance();

	/// <summary>
	/// Inherited from GameState
	/// Initialize the time speed upgrade of wave manager and also the player, and the cannon.
	/// Finally, initialize the level's background sprite, 
	/// </summary>
	void InitFeatures() override final;

	/// <summary>
	/// Main method call in the level loop.
	/// Call all update methods of his managers and his entities.
	/// Also draw the level background.
	/// </summary>
	void Update(RenderWindow* window) override final;

	/// <summary>
	/// Update all entities and give them reference to the game windows.
	/// </summary>
	/// <param name="window">Game window</param>
	void UpdateEntities(RenderWindow* window);

	/// <summary>
	/// Add an enemy to the vector of enemies
	/// </summary>
	/// <param name="entity">The new enemy to add to the vector</param>
	void AddEntity(Entity* entity);

	/// <summary>
	/// Remove an entity from his concerned vector.
	/// </summary>
	/// <param name="entity"></param>
	void RemoveEntity(Entity* entity);

	/// <summary>
	/// Call DecreaseHP() method of the lifebar of the player and reduce it by the amount in parameter.
	/// </summary>
	/// <param name="amount">Amount of HP removed</param>
	void ReduceHP(const int& amount);

private:

	/// <summary>
	/// Vector of Entity, it contains all the entities of the current game.
	/// </summary>
	vector<Entity*> mEntities;

	/// <summary>
	/// Collision manager tha hanlde all features based on the physic.
	/// </summary>
	CollisionManager* mCollisionManager;

	/// <summary>
	/// Wave manager that handle all the features based on the wave appearance and the current spawn of enemy.
	/// </summary>
	WaveManager* mWaveManager;

	/// <summary>
	/// Score manager that handle score management.
	/// </summary>
	ScoreManager* mScoreManager;

	/// <summary>
	/// Main HUD of the game that contains the current time since the game has start and the wave flickering text.
	/// </summary>
	HUD* mHUD;

	/// <summary>
	/// Contains all members variables that are binded to the player such as XP.
	/// </summary>
	Player* mPlayer;

	/// <summary>
	/// Cannon that the player control in order to launch cannonball.
	/// </summary>
	Cannon* mCannon;

	/// <summary>
	/// Singleton instance of the game class.
	/// </summary>
	static LevelState* mInstance;
};

