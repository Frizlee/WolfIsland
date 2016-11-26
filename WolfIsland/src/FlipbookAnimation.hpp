#pragma once
#include "Prerequisites.hpp"


class FlipbookAnimation
{
public:
	FlipbookAnimation();

	FlipbookAnimation(std::shared_ptr<class SpriteSheet> spriteSheet, 
		const std::vector<std::uint32_t>& keyFrames, double duration);
	void create(std::shared_ptr<class SpriteSheet> spriteSheet,
		std::vector<std::uint32_t> keyFrames, double duration);

	~FlipbookAnimation();
	
	// start from current position
	void start(); 

	// start reverse form current position or if 0 from end
	void reverse();

	// start form 0
	void restart();

	// set position to 0 and if playing - stops
	void reset(); 

	// stops playing
	void stop();

	void update(double deltaTime);

	void setRepeat(bool state);

	std::weak_ptr<const class Sprite> getCurrentSprite() const;

private:
	std::vector<std::uint32_t> mKeyFramesIndices;
	std::shared_ptr<class SpriteSheet> mSpriteSheet;

	double mDuration;
	double mCurrentTime;
	double mPlayDirection;

	bool mRepeat;
};

