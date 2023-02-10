#include "StraightMoveComponent.h"
#include "Game.h"
#include "LevelState.h"

Vector2f StraightMoveComponent::GetTrajectory()
{
	mCurrentTime = Game::GetInstance()->GetTimer()->GetCurrentTime();
	float elapsedTime = (mCurrentTime - mInitialTime) * TIME_FLOW_SPEED;		// 4.0f is used to accelerate the flow of the time 

	return mVelocity* elapsedTime;
}

bool StraightMoveComponent::Move()
{
	mOwner->setPosition(mInitialPos + GetTrajectory());

	if (IsOwnerOutsideScreen())
	{
		LevelState::GetInstance()->RemoveEntity(mOwner);
		return false;
	}

	return true;
}
