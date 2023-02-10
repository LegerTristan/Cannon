#pragma once

#include <string>
#include "EntityComponent.h"

using namespace std;

/// <summary>
/// Tag of the collision component.
/// Used to separate ball's collision from enemy's collision
/// </summary>
enum class CollisionTag
{
	BALL = 0,
	ENEMY = 1,
};

/// <summary>
/// Inherit from Component.
/// A component that allow an entity to collide with other entity tha can collide.
/// </summary>
class CollisionComponent : public EntityComponent
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	CollisionComponent(Entity* entity, const CollisionTag tag, const char* _hitBoxPath);
	~CollisionComponent() {}

	// GETTERS & SETTER

	CollisionTag GetCollisionTag() const;
	RectangleShape GetHitBox() const;
	
	void SetHitBox(const FloatRect& newHitBox);

	/// <summary>
	/// Check if this component collide with another CollisionComponent passed in parameter.
	/// </summary>
	/// <param name="otherCollision">The other CollisionComponent to check if it collide with</param>
	/// <returns>If collide the other CollisionComponent in parameter</returns>
	bool CollideWith(const CollisionComponent* otherCollision);

private:

	/// <summary>
	/// Tag of the collision component
	/// </summary>
	CollisionTag mCollisionTag;

	/// <summary>
	/// HitBox of the collision component
	/// </summary>
	RectangleShape mHitBox;
};

