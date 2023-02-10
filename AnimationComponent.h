#pragma once

#include <vector>
#include "EntityComponent.h"

using namespace std;

/// <summary>
/// Contains UV position and size of the UV rect of a frame of an animation.
/// </summary>
struct AnimationFrame
{
	Vector2i mUVRectPos, mUVRectSize;
};

/// <summary>
/// Component that create an animation on the sprite of the entity
/// based on JSON passed in constructor's param.
/// </summary>
class AnimationComponent : public EntityComponent
{
public:

	// CONSTRUCTORS & DESTRUCTOR

	AnimationComponent(Entity* entity, float nextAnimDelay, const char* filePath);
	//AnimationComponent(Entity* entity, float nextAnimDelay, vector<AnimationFrame> frames);	// Need later, for getting
																							// informations about animation
	~AnimationComponent() {}

	/// <summary>
	/// Update a sprite by passing to the next frame.
	/// And when reached the final frame, reset to the first.
	/// </summary>
	void UpdateAnimSprite();

private:

	/// <summary>
	/// Frames of the animation.
	/// </summary>
	vector<AnimationFrame> mFrames;

	/// <summary>
	/// Delay between every frame
	/// </summary>
	float mNextAnimDelay;

	/// <summary>
	/// Current elapsed Time since the last update.
	/// </summary>
	float mCurrentAnimTime;

	/// <summary>
	/// Index of the current frame.
	/// </summary>
	unsigned int mFrameIndex;
};

