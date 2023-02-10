#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

/// <summary>
/// A component that have is own timeline.
/// Allow is owner to do an action through a certain time, repeat it, or juste get the current time of this timeline.
/// The timeline flow is a float
/// </summary>
/// <typeparam name="T">Owner class that we ned in order to call an event of this class through the component.</typeparam>
template<class T>
class TimelineComponent
{
public:
	/// <summary>
	/// Event delegate
	/// </summary>
	typedef void (T::* Function)();

    // CONSTRUCTOR & DESTRUCTOR

	TimelineComponent(T* owner, Function ownerFunction, const float& triggerTime, const float& timeSpeed,
		const bool& repeatTrigger = false, const float& duration = -1.0f);
	~TimelineComponent() {}

    // GETTERS & SETTER

	float GetCurrentTime() const;
	float GetDuration() const;

	void SetDuration(const float& duration);

	/// <summary>
	/// Start the timeline.
    /// Means that the startTime is assigned at this moment, and the UpdateTimeline method willnow be called.
	/// </summary>
	void Start();

	/// <summary>
	/// Stop the timeline and reset all his members  necessary for the flow.
	/// </summary>
	void Reset();

	/// <summary>
	/// Update the current time of the timeline.
    /// Call HandleEvent method and reset the component if it reachs his duration (if it has one).
	/// </summary>
	/// <returns>Return the current time of the timeline</returns>
	float UpdateTimeline();

    /// <summary>
    /// Check if it can cal the event and if it needs to repeat it or not.
    /// </summary>
    void HandleEvent();

	/// <summary>
	/// Call the event bind to the timeline component.
	/// </summary>
	void CallEvent() const;

private:

	/// <summary>
	/// Owner of the component.
	/// Necessary for calling the event with the mOwnerFunction member
	/// </summary>
	T* mOwner;

	/// <summary>
	/// Function of the owner that will be called when the event trigger will be passed.
	/// </summary>
	Function mOwnerFunction;

    /// <summary>
    /// Clock of the timeline.
    /// </summary>
    Clock mTimelineClock;

	/// <summary>
	/// Time when the timeline start
	/// </summary>
	float mStartTime;
	
	/// <summary>
	/// Current time elapsed since the timeline start
	/// </summary>
	float mElapsedTime;
	
	/// <summary>
	/// Time when the event needs to be called
	/// </summary>
	float mCurrentTriggerTime;
	
	/// <summary>
	/// Flow's speed of the time.
	/// </summary>
	float mTimeSpeed;
	
	/// <summary>
	/// Duration of the timeline.
	/// When elapsed time reachs the duration, the component will be reset.
	/// If duration < 0, then it has no end.
	/// </summary>
	float mDuration = -1.0f;
	
	/// <summary>
	/// Use with repeat trigger boolean, interval of time betwwen two call of event.
	/// </summary>
	float mTriggerTime;

	/// <summary>
	/// Tell if the timeline is currently active
	/// </summary>
	bool mIsActive = false;
	
	/// <summary>
	/// Tell if the trigger for the event needs to be repeated until a possible end.
	/// </summary>
	bool mTriggerRepeat = false;
	
	/// <summary>
	/// Use with repeat trigger boolean at false, tell if the trigger was already passed or not.
	/// </summary>
	bool mWasTrigger = false;
};

template<class T>
inline TimelineComponent<T>::TimelineComponent(T* _owner, Function _ownerFunction, const float& _triggerTime,
	const float& _timeSpeed, const bool& _repeatTrigger, const float& _duration)
{
	mOwner = _owner;
	mOwnerFunction = _ownerFunction;
	mTriggerTime = mCurrentTriggerTime = _triggerTime;
    mTimelineClock = Clock();
	mStartTime = mElapsedTime = 0.0f;
	mTriggerRepeat = _repeatTrigger;
	mTimeSpeed = _timeSpeed;
	mDuration = _duration;
    mIsActive = false;
    mWasTrigger = false;
}

template<class T>
float TimelineComponent<T>::GetCurrentTime() const
{
    return mElapsedTime;
}

template<class T>
float TimelineComponent<T>::GetDuration() const
{
    return mDuration;
}

template<class T>
inline void TimelineComponent<T>::SetDuration(const float& _duration)
{
	mDuration = _duration;
}

template<class T>
void TimelineComponent<T>::Start()
{
    mStartTime = mElapsedTime = mTimelineClock.getElapsedTime().asSeconds();
    mIsActive = true;
	mCurrentTriggerTime = mTriggerTime;
}

template<class T>
void TimelineComponent<T>::Reset()
{
    mStartTime = mElapsedTime = 0.0f;
    mIsActive = false;
	mCurrentTriggerTime = mTriggerTime;
}

template<class T>
float TimelineComponent<T>::UpdateTimeline()
{
    if (mIsActive)
    {
        mElapsedTime = (mTimelineClock.getElapsedTime().asSeconds() - mStartTime) * mTimeSpeed;

        HandleEvent();

        if (mDuration >= 0.0f && mElapsedTime >= mDuration)
            Reset();

        return mElapsedTime;
    }
    else
        return 0.0f;
}

template<class T>
void TimelineComponent<T>::HandleEvent()
{
    if (mOwner && mOwnerFunction && mElapsedTime >= mCurrentTriggerTime && !mWasTrigger)
    {
        CallEvent();

        if (!mTriggerRepeat)
            mWasTrigger = true;
        else
            mCurrentTriggerTime = mElapsedTime + mTriggerTime;
    }
}

template<class T>
void TimelineComponent<T>::CallEvent() const
{
    (mOwner->*mOwnerFunction)();
}