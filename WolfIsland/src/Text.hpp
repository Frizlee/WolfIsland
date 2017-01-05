///-------------------------------------------------------------------------------------------------
// file:	src\Text.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include "VertexLayout.hpp"
#include <glm/vec4.hpp>

/// <summary>	A text. </summary>
class Text
{
	friend class Renderer;

public:
	/// <summary>	Default constructor. </summary>
	Text();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="content">	  	The content. </param>
	/// <param name="fnt">		  	The font. </param>
	/// <param name="vao">		  	[in,out] The vao. </param>
	/// <param name="vboPosition">	The vbo position. </param>
	/// <param name="renderer">   	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Text(const std::string& content, std::shared_ptr<class Font> fnt, 
		std::shared_ptr<class VertexArray>& vao, std::uint32_t vboPosition, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="content">	  	The content. </param>
	/// <param name="fnt">		  	The font. </param>
	/// <param name="vao">		  	[in,out] The vao. </param>
	/// <param name="vboPosition">	The vbo position. </param>
	/// <param name="renderer">   	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(const std::string& content, std::shared_ptr<class Font> fnt, 
		std::shared_ptr<class VertexArray>& vao, std::uint32_t vboPosition, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Updates the content. </summary>
	///
	/// <param name="content"> 	The content. </param>
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void updateContent(const std::string& content, class Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Sets a color. </summary>
	///
	/// <param name="color">	The color. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setColor(const glm::vec4& color);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the color. </summary>
	///
	/// <returns>	The color. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const glm::vec4& getColor() const;

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
	const std::vector<TextVertexLayout::Data>& getBuffer() const;

private:
	/// <summary>	The buffer. </summary>
	std::vector<TextVertexLayout::Data> mBuffer;
	/// <summary>	The color. </summary>
	glm::vec4 mColor;
	/// <summary>	The vao. </summary>
	std::shared_ptr<class VertexArray> mVao;
	/// <summary>	The vbo position. </summary>
	std::uint32_t mVboPosition;
	/// <summary>	The texture. </summary>
	std::shared_ptr<class Texture> mTexture;
	/// <summary>	The font. </summary>
	std::shared_ptr<class Font> mFont;
};



