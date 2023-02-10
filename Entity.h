#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class CollisionComponent;
class MoveComponent;

/// <summary>
/// Inherit from Sprite of SFML graphics lib.
/// It is a Sprite that have a collision and a move component, allowing it to move and collide with other things.
/// </summary>
class Entity : public Sprite
{
public:

	// CONSTRUCTORS & DESTRUCTOR

	Entity(const Vector2f position, const Texture* texture);
	virtual ~Entity();

	// GETTER

	CollisionComponent* GetCollisionComp() const;
	bool HasLife() const;

	/// <summary>
	/// Virtual pure method use for updating any elements an entity needs to update.
	/// </summary>
	/// <param name="window">Game window</param>
	virtual void Update(RenderWindow* window) = 0;

	/// <summary>
	/// Decrease current life of the entity by 1.
	/// </summary>
	void DecreaseLife();

	/// <summary>
	/// Remove entity from entities vector LevelState.
	/// Mainly used for entity derived class.
	/// </summary>
	virtual void Die();

protected:

	/// <summary>
	/// Collision component of the entity
	/// </summary>
	CollisionComponent* mCollisionComp;

	/// <summary>
	/// Move component of the entity
	/// </summary>
	MoveComponent* mMoveComp;

	/// <summary>
	/// Current life of the entity
	/// </summary>
	short mLife;
};

