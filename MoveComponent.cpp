#include "MoveComponent.h"
#include "Game.h"
#include "Constants.h"

MoveComponent::MoveComponent(Entity* _entity, Vector2f _velocity) : EntityComponent(_entity)
{
	// Set Velocity
	mVelocity = _velocity;
	mInitialTime = mCurrentTime = Game::GetInstance()->GetTimer()->GetCurrentTime();
	mInitialPos = mOwner->getPosition();
}

bool MoveComponent::IsOwnerOutsideScreen() const
{
	return mOwner->getPosition().x <= DEFAULT_MIN_BOUNDARY || mOwner->getPosition().y >= WINDOW_HEIGHT + PADDING_HEIGHT;
}
