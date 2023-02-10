#include "ParabolicMoveComponent.h"
#include "Game.h"
#include "LevelState.h"

Vector2f ParabolicMoveComponent::GetTrajectory()
{
	mCurrentTime = Game::GetInstance()->GetTimer()->GetCurrentTime();
	float elapsedTime = (mCurrentTime - mInitialTime) * TIME_FLOW_SPEED;

	Vector2f currentVelocity = mVelocity * elapsedTime;
	currentVelocity.y += (g / 2 * pow(elapsedTime, 2));

	return currentVelocity;
}

bool ParabolicMoveComponent::Move()
{
	mOwner->setPosition(mInitialPos + GetTrajectory());

	if (IsOwnerOutsideScreen())
	{
		LevelState::GetInstance()->RemoveEntity(mOwner);
		return false;
	}

	return true;
}
