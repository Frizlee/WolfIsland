///-------------------------------------------------------------------------------------------------
// file:	src\GameObject.hpp
//
// summary:
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include "gl_core_3_3.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

/// <summary>	A game object. </summary>
class GameObject
{
public:
	/// <summary>	Default constructor. </summary>
	GameObject();
	/// <summary>	Destructor. </summary>
	virtual ~GameObject() = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Draws the given renderer. </summary>
	///
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void draw(class Renderer& renderer) const = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Updates the move described by board. </summary>
	///
	/// <param name="board">	[in,out] The board. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void updateMove(class Board& board) = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Updates the action described by board. </summary>
	///
	/// <param name="board">	[in,out] The board. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void updateAction(class Board& board) = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Updates the given deltaTime. </summary>
	///
	/// <param name="deltaTime">	The delta time. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void update(float deltaTime) = 0;

	/// <summary>	Saves the current position. </summary>
	void saveCurrentPos();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the position. </summary>
	///
	/// <returns>	The position. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const glm::tvec2<std::int32_t>& getPos() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets saved position. </summary>
	///
	/// <returns>	The saved position. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const glm::tvec2<std::int32_t>& getSavedPos() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Sets a position. </summary>
	///
	/// <param name="pos">	The position. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void setPos(const glm::tvec2<std::int32_t>& pos) = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets object type. </summary>
	///
	/// <returns>	The object type. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const std::string& getObjectType();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Sets an active. </summary>
	///
	/// <param name="state">	True to state. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setActive(bool state);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is active. </summary>
	///
	/// <returns>	True if active, false if not. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool isActive() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is ready to delete. </summary>
	///
	/// <returns>	True if ready to delete, false if not. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool isReadyToDelete() const;

protected:
	/// <summary>	The type. </summary>
	std::string mType;
	/// <summary>	The position. </summary>
	glm::tvec2<std::int32_t> mPos;
	/// <summary>	The saved position. </summary>
	glm::tvec2<std::int32_t> mSavedPos;
	/// <summary>	True to active. </summary>
	bool mActive;
	/// <summary>	True to ready to delete. </summary>
	bool mReadyToDelete;
};

