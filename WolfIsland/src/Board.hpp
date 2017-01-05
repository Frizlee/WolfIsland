///-------------------------------------------------------------------------------------------------
// file:	src\Board.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include "Sprite.hpp"
#include "VertexBuffer.hpp"
#include "gl_core_3_3.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

/// <summary>	A board. </summary>
class Board
{
public:
	/// <summary>	Default constructor. </summary>
	Board();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="width">	  	The width. </param>
	/// <param name="height">	  	The height. </param>
	/// <param name="spriteSheet">	The sprite sheet. </param>
	/// <param name="renderer">   	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Board(std::uint32_t width, std::uint32_t height, 
		std::shared_ptr<class SpriteSheet> spriteSheet, class Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="width">	  	The width. </param>
	/// <param name="height">	  	The height. </param>
	/// <param name="spriteSheet">	The sprite sheet. </param>
	/// <param name="renderer">   	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::uint32_t width, std::uint32_t height, 
		std::shared_ptr<class SpriteSheet> spriteSheet, class Renderer& renderer);
	
	/// <summary>	Destructor. </summary>
	~Board();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Draws the given renderer. </summary>
	///
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void draw(class Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the objects. </summary>
	///
	/// <returns>	The objects. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const std::vector<std::shared_ptr<class GameObject>>& getObjects() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the objects. </summary>
	///
	/// <param name="pos">  	The position. </param>
	/// <param name="saved">	(Optional) True if the data was saved. </param>
	///
	/// <returns>	The objects. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::vector<std::shared_ptr<class GameObject>> getObjects(const glm::tvec2<std::int32_t>& pos, 
		bool saved = true);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets surrounding objects. </summary>
	///
	/// <param name="pos">	The position. </param>
	///
	/// <returns>	The surrounding objects. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::vector<std::shared_ptr<class GameObject>> getSurroundingObjects(
		const glm::tvec2<std::int32_t>& pos);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Adds a game object. </summary>
	///
	/// <param name="object">	[in,out] The object. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void addGameObject(std::shared_ptr<class GameObject>& object);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the width. </summary>
	///
	/// <returns>	The width. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getWidth() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the height. </summary>
	///
	/// <returns>	The height. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getHeight() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Spawn wolf. </summary>
	///
	/// <param name="pos">	The position. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void spawnWolf(glm::tvec2<std::int32_t> pos);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Spawn hare. </summary>
	///
	/// <param name="pos">	The position. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void spawnHare(glm::tvec2<std::int32_t> pos);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets object counters. </summary>
	///
	/// <returns>	The object counters. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const std::array<std::int32_t, 5>& getObjectCounters();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is counters changed. </summary>
	///
	/// <returns>	True if counters changed, false if not. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool isCountersChanged();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Updates the turn described by app. </summary>
	///
	/// <param name="app">	[in,out] The application. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void updateTurn(class Application& app);

private:
	/// <summary>	The width. </summary>
	std::uint32_t mWidth;
	/// <summary>	The height. </summary>
	std::uint32_t mHeight;
	
	/// <summary>	The objects. </summary>
	std::vector<std::shared_ptr<class GameObject>> mObjects;
	/// <summary>	Stack of hare spawns. </summary>
	std::stack<glm::tvec2<std::int32_t>> mHareSpawnStack;
	/// <summary>	Stack of wolf spawns. </summary>
	std::stack<glm::tvec2<std::int32_t>> mWolfSpawnStack;

	/// <summary>	The object counters. </summary>
	std::array<std::int32_t, 5> mObjectCounters;
	/// <summary>	True if this object is counters changed. </summary>
	bool mIsCountersChanged;

	/// <summary>	Resources. </summary>
	std::vector<std::shared_ptr<VertexBuffer<PositionVertexLayout>>> mTileMap;
	/// <summary>	The sprite sheet. </summary>
	std::shared_ptr<SpriteSheet> mSpriteSheet;
};

