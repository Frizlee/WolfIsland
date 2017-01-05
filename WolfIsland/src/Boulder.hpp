///-------------------------------------------------------------------------------------------------
// file:	src\Boulder.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include "GameObject.hpp"

/// <summary>	A boulder. </summary>
class Boulder :	public GameObject
{
public:
	/// <summary>	Default constructor. </summary>
	Boulder();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="boulderSprite">	The boulder sprite. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Boulder(std::shared_ptr<class Sprite> boulderSprite);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="boulderSprite">	The boulder sprite. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::shared_ptr<class Sprite> boulderSprite);

	/// <summary>	Destructor. </summary>
	~Boulder();

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

	/// <summary>	Resources. </summary>
	std::shared_ptr<class Sprite> mSprite;
};

