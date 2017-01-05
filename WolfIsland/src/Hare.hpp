///-------------------------------------------------------------------------------------------------
// file:	src\Hare.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include "GameObject.hpp"
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include "gl_core_3_3.hpp"
#include "FlipbookAnimation.hpp"


/// <summary>	A hare. </summary>
class Hare : public GameObject
{
public:
	/// <summary>	Default constructor. </summary>
	Hare();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="spriteSheet">	The sprite sheet. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Hare(std::shared_ptr<class SpriteSheet> spriteSheet);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="spriteSheet">	The sprite sheet. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::shared_ptr<class SpriteSheet> spriteSheet);

	/// <summary>	Destructor. </summary>
	~Hare();

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

	///--------------------------------------------------------------------------------------------
	/// <summary>	Sets an eaten. </summary>
	///
	/// <param name="state">	True to state. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setEaten(bool state);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is eaten. </summary>
	///
	/// <returns>	True if eaten, false if not. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool isEaten();

private:
	/// <summary>	The real position. </summary>
	glm::vec2 mRealPos;
	/// <summary>	The random disorder. </summary>
	glm::vec2 mRandomDisorder;
	
	/// <summary>	Animations. </summary>
	std::array<FlipbookAnimation, 9> mAnimations;
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
	std::uint32_t mSplitTourTimer;
	/// <summary>	The life tours. </summary>
	std::uint32_t mLifeTours;
	/// <summary>	True if this object is eaten. </summary>
	bool mIsEaten;
};

