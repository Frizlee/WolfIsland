///-------------------------------------------------------------------------------------------------
// file:	src\SpriteSheet.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include <glm/vec2.hpp>

/// <summary>	A sprite sheet. </summary>
class SpriteSheet
{
	friend class Renderer;

public:
	/// <summary>	Default constructor. </summary>
	SpriteSheet();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="sprites">	The sprites. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	SpriteSheet(const std::vector<std::shared_ptr<class Sprite>>& sprites);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="sprites">	The sprites. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(const std::vector<std::shared_ptr<class Sprite>>& sprites);
	
	/// <summary>	Destructor. </summary>
	~SpriteSheet();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Adds a sprite. </summary>
	///
	/// <param name="sprite">	The sprite. </param>
	///
	/// <returns>	A std::uint32_t. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t addSprite(std::shared_ptr<class Sprite> sprite);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the texture. </summary>
	///
	/// <returns>	The texture. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<const class Texture> getTexture() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets a sprite. </summary>
	///
	/// <param name="index">	Zero-based index of the. </param>
	///
	/// <returns>	The sprite. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<const class Sprite> getSprite(std::uint32_t index) const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the vao. </summary>
	///
	/// <returns>	The vao. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<const class VertexArray> getVao() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the vao. </summary>
	///
	/// <returns>	The vao. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<class VertexArray> getVao();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the bounds. </summary>
	///
	/// <returns>	The bounds. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const glm::vec2& getBounds();

private:
	/// <summary>	The sprites. </summary>
	std::vector<std::shared_ptr<class Sprite>> mSprites;
};

