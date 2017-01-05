///-------------------------------------------------------------------------------------------------
// file:	src\Sprite.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include "VertexLayout.hpp"
#include <glm/vec2.hpp>

/// <summary>	A sprite. </summary>
class Sprite
{
	friend class Renderer;

public:
	/// <summary>	Default constructor. </summary>
	Sprite();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="topRight">  	The top right. </param>
	/// <param name="uvDownLeft">	The uv down left. </param>
	/// <param name="uvTopRight">	The uv top right. </param>
	/// <param name="z">		 	The z coordinate. </param>
	/// <param name="tex">		 	[in,out] The tex. </param>
	/// <param name="vao">		 	[in,out] The vao. </param>
	/// <param name="renderer">  	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Sprite(const glm::vec2& topRight, const glm::vec2& uvDownLeft,
		const glm::vec2& uvTopRight, float z, std::shared_ptr<class Texture>& tex,
		std::shared_ptr<class VertexArray>& vao, class Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="topRight">  	The top right. </param>
	/// <param name="uvDownLeft">	The uv down left. </param>
	/// <param name="uvTopRight">	The uv top right. </param>
	/// <param name="z">		 	The z coordinate. </param>
	/// <param name="tex">		 	[in,out] The tex. </param>
	/// <param name="vao">		 	[in,out] The vao. </param>
	/// <param name="renderer">  	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(const glm::vec2& topRight, const glm::vec2& uvDownLeft, 
		const glm::vec2& uvTopRight, float z, std::shared_ptr<class Texture>& tex,
		std::shared_ptr<class VertexArray>& vao, class Renderer& renderer);
	
	
	/// <summary>	Destructor. </summary>
	~Sprite();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the texture. </summary>
	///
	/// <returns>	The texture. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<const class Texture> getTexture() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the buffer. </summary>
	///
	/// <returns>	The buffer. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const std::vector<TextureVertexLayout::Data>& getBuffer() const;

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
	const glm::vec2& getBounds() const;

private:
	/// <summary>	The buffer. </summary>
	std::vector<TextureVertexLayout::Data> mBuffer;
	/// <summary>	The vao. </summary>
	std::shared_ptr<class VertexArray> mVao;
	/// <summary>	The vbo position. </summary>
	std::uint32_t mVboPosition;
	/// <summary>	The texture. </summary>
	std::shared_ptr<class Texture> mTexture;
	/// <summary>	The bounds. </summary>
	glm::vec2 mBounds;
};

