#include "TimeManager.h"

TimeManager::TimeManager()
{
	mCurrentTime = mClock.getElapsedTime();
	mDeltaTime = 0.0f;
}

float TimeManager::GetDeltaTime() const
{
	return mDeltaTime;
}

float TimeManager::GetCurrentTime() const
{
	return mCurrentTime.asSeconds();
}

void TimeManager::SetPause(const bool& _pause)
{
	mIsPaused = _pause;

	if (mIsPaused)
	{
		mRunTime = mCurrentTime;
	}
	else
	{
		mClock.restart();
	}
}

void TimeManager::UpdateCurrentTime()
{
	if(!mIsPaused)
		mCurrentTime = mClock.getElapsedTime() + mRunTime;
}

void TimeManager::UpdateLastTime()
{
	if(!mIsPaused)
		mLastTime = mCurrentTime;
}

void TimeManager::CalculateDeltaTime()
{
	if(!mIsPaused)
		mDeltaTime = mCurrentTime.asSeconds() - mLastTime.asSeconds();;
}
