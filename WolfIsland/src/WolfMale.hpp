///-------------------------------------------------------------------------------------------------
// file:	src\WolfMale.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include "gl_core_3_3.hpp"
#include "GameObject.hpp"
#include "FlipbookAnimation.hpp"


/// <summary>	A wolf male. </summary>
class WolfMale : public GameObject
{
public:
	/// <summary>	Default constructor. </summary>
	WolfMale();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="spriteSheet">	The sprite sheet. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	WolfMale(std::shared_ptr<class SpriteSheet> spriteSheet);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="spriteSheet">	The sprite sheet. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::shared_ptr<class SpriteSheet> spriteSheet);

	/// <summary>	Destructor. </summary>
	~WolfMale();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets real position. </summary>
	///
	/// <returns>	The real position. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const glm::vec2& getRealPos();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Draws the given renderer. </summary>
	///
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void draw(class Renderer& renderer) const override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Updates the move described by board. </summary>
	///
	/// <param name="board">	[in,out] The board. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void updateMove(class Board& board) override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Updates the action described by board. </summary>
	///
	/// <param name="board">	[in,out] The board. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void updateAction(class Board& board) override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Updates the given deltaTime. </summary>
	///
	/// <param name="deltaTime">	The delta time. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void update(float deltaTime) override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Sets a position. </summary>
	///
	/// <param name="pos">	The position. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setPos(const glm::tvec2<std::int32_t>& pos);

private:
	/// <summary>	The real position. </summary>
	glm::vec2 mRealPos;
	/// <summary>	The random disorder. </summary>
	glm::vec2 mRandomDisorder;

	/// <summary>	Animations. </summary>
	std::array<FlipbookAnimation, 10> mAnimations;
	/// <summary>	The current animation. </summary>
	std::uint32_t mCurrentAnimation;
	/// <summary>	The current idle. </summary>
	std::uint32_t mCurrentIdle;
	/// <summary>	The transition start position. </summary>
	glm::vec2 mTransitionStartPos;
	/// <summary>	The transition timer. </summary>
	float mTransitionTimer;
	/// <summary>	The corpse timer. </summary>
	float mCorpseTimer;

	/// <summary>	Logic. </summary>
	bool mChaseHare;
	/// <summary>	The fat. </summary>
	float mFat;
	/// <summary>	The mate tour timer. </summary>
	std::uint32_t mMateTourTimer;
};

