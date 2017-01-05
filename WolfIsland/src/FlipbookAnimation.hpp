///-------------------------------------------------------------------------------------------------
// file:	src\FlipbookAnimation.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"


/// <summary>	A flipbook animation. </summary>
class FlipbookAnimation
{
public:
	/// <summary>	Default constructor. </summary>
	FlipbookAnimation();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="spriteSheet">	The sprite sheet. </param>
	/// <param name="keyFrames">  	The key frames. </param>
	/// <param name="duration">   	The duration. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	FlipbookAnimation(std::shared_ptr<class SpriteSheet> spriteSheet, 
		const std::vector<std::uint32_t>& keyFrames, double duration);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="spriteSheet">	The sprite sheet. </param>
	/// <param name="keyFrames">  	The key frames. </param>
	/// <param name="duration">   	The duration. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::shared_ptr<class SpriteSheet> spriteSheet,
		std::vector<std::uint32_t> keyFrames, double duration);

	/// <summary>	Destructor. </summary>
	~FlipbookAnimation();
	
	/// <summary>	start from current position. </summary>
	void start(); 

	/// <summary>	start reverse form current position or if 0 from end. </summary>
	void reverse();

	/// <summary>	start form 0. </summary>
	void restart();

	/// <summary>	set position to 0 and if playing - stops. </summary>
	void reset(); 

	/// <summary>	stops playing. </summary>
	void stop();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Updates the given deltaTime. </summary>
	///
	/// <param name="deltaTime">	The delta time. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void update(double deltaTime);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Sets a repeat. </summary>
	///
	/// <param name="state">	True to state. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setRepeat(bool state);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets current sprite. </summary>
	///
	/// <returns>	The current sprite. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<const class Sprite> getCurrentSprite() const;

private:
	/// <summary>	The key frames indices. </summary>
	std::vector<std::uint32_t> mKeyFramesIndices;
	/// <summary>	The sprite sheet. </summary>
	std::shared_ptr<class SpriteSheet> mSpriteSheet;

	/// <summary>	The duration. </summary>
	double mDuration;
	/// <summary>	The current time. </summary>
	double mCurrentTime;
	/// <summary>	The play direction. </summary>
	double mPlayDirection;

	/// <summary>	True to repeat. </summary>
	bool mRepeat;
};

