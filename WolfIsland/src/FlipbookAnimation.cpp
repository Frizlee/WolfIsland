#include "FlipbookAnimation.hpp"
#include "SpriteSheet.hpp"
using namespace std;


FlipbookAnimation::FlipbookAnimation()
	: mCurrentTime{ 0.0 }, mPlayDirection{ 0.0 }, mRepeat{ true }
{
}

FlipbookAnimation::FlipbookAnimation(shared_ptr<class SpriteSheet> spriteSheet, 
	const vector<uint32_t>& keyFrames, double duration)
	: mCurrentTime{ 0.0 }, mPlayDirection{ 0.0 }, mRepeat{ true }
{
	create(spriteSheet, keyFrames, duration);
}

void FlipbookAnimation::create(shared_ptr<class SpriteSheet> spriteSheet, 
	vector<uint32_t> keyFrames, double duration)
{
	mSpriteSheet = spriteSheet;
	swap(mKeyFramesIndices, keyFrames);
	mDuration = duration;
}


FlipbookAnimation::~FlipbookAnimation()
{
}

void FlipbookAnimation::start()
{
	mPlayDirection = 1.0;
}

void FlipbookAnimation::restart()
{
	mCurrentTime = 0.0;
	mPlayDirection = 1.0;
}

void FlipbookAnimation::reset()
{
	stop();
	mCurrentTime = 0.0;
}

void FlipbookAnimation::reverse()
{
	mPlayDirection = -1.0;
	
	if (mCurrentTime == 0.0)
		mCurrentTime = mDuration;
}

void FlipbookAnimation::stop()
{
	mPlayDirection = 0.0;
}

void FlipbookAnimation::update(double deltaTime)
{
	mCurrentTime += deltaTime * mPlayDirection;

	if ((mCurrentTime > mDuration || mCurrentTime < 0.0) && !mRepeat)
		stop();

	while (mCurrentTime > mDuration)
		mCurrentTime -= mDuration;

	while (mCurrentTime < 0.0)
		mCurrentTime = mDuration - mCurrentTime;
}

void FlipbookAnimation::setRepeat(bool state)
{
	mRepeat = true;
}

weak_ptr<const class Sprite> FlipbookAnimation::getCurrentSprite() const
{
	uint32_t index = static_cast<uint32_t>((mCurrentTime / mDuration) * mKeyFramesIndices.size());

	return mSpriteSheet->getSprite(mKeyFramesIndices[index]);
}
