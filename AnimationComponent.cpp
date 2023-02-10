#include "AnimationComponent.h"
#include "json.hpp"
#include "Game.h"
#include <fstream>


using json = nlohmann::json;

AnimationComponent::AnimationComponent(Entity* _entity, float _nextAnimDelay
	, const char* _filePath) : EntityComponent(_entity)
{
	mFrameIndex = 0;
	mNextAnimDelay = _nextAnimDelay;
	mCurrentAnimTime = 0.0f;

	json tempFile;
	std::ifstream i(_filePath);
	i >> tempFile;

	AnimationFrame newFrame;
	if (tempFile.is_object())
	{
		json frames = tempFile["frames"];

		for (auto f : frames)
		{
			newFrame.mUVRectPos = Vector2i(f["frame"]["x"], f["frame"]["y"]);
			newFrame.mUVRectSize = Vector2i(f["frame"]["w"], f["frame"]["h"]);

			mFrames.push_back(newFrame);
		}
	}

	mOwner->setOrigin({newFrame.mUVRectSize.x / 2.0f, newFrame.mUVRectSize.y / 2.0f });
	mOwner->setTextureRect({
			mFrames[0].mUVRectPos.x, mFrames[0].mUVRectPos.y,
			mFrames[0].mUVRectSize.x, mFrames[0].mUVRectSize.y
	});
}

//AnimationComponent::AnimationComponent(Entity* _entity, float _nextAnimDelay, vector<AnimationFrame> _frames)
//	: EntityComponent(_entity)
//{
//	mFrameIndex = 0;
//	mNextAnimDelay = _nextAnimDelay;
//	mCurrentAnimTime = 0.0f;
//	mFrames = _frames;
//
//	mOwner->setOrigin({ mFrames[0].mUVRectSize.x / 2.0f, mFrames[0].mUVRectSize.y / 2.0f });
//	mOwner->setTextureRect({
//			mFrames[0].mUVRectPos.x, mFrames[0].mUVRectPos.y,
//			mFrames[0].mUVRectSize.x, mFrames[0].mUVRectSize.y
//	});
//}

void AnimationComponent::UpdateAnimSprite()
{
	mCurrentAnimTime += Game::GetInstance()->GetTimer()->GetDeltaTime();
	if (mCurrentAnimTime >= mNextAnimDelay)
	{
		mFrameIndex++;

		if (mFrameIndex >= mFrames.size())
		{
			mFrameIndex = 0;
		}

		AnimationFrame currentFrame = mFrames[mFrameIndex];
		mOwner->setTextureRect({ 
			currentFrame.mUVRectPos.x, currentFrame .mUVRectPos.y,
			currentFrame.mUVRectSize.x, currentFrame.mUVRectSize.y
		});

		mCurrentAnimTime -= mNextAnimDelay;
	}
}
