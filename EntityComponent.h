#pragma once

#include "Entity.h"

/// <summary>
/// A class that needs an entity in order to work.
/// Add a specific behavior to an entity.
/// </summary>
class EntityComponent
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	EntityComponent(Entity* entity) { mOwner = entity; }
	~EntityComponent() {}

	// GETTER

	Entity* GetOwner() const;

protected:

	/// <summary>
	/// Owner of the component
	/// </summary>
	Entity* mOwner;
};

