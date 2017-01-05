///-------------------------------------------------------------------------------------------------
// file:	src\Font.hpp
//
// summary:
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include "Resource.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "VertexLayout.hpp"
#include <glm/vec2.hpp>

/// <summary>	Exception for signalling font initialization errors. </summary>
class FontInitializationException : public std::exception
{
	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the what. </summary>
	///
	/// <returns>	Null if it fails, else a pointer to a const char. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual const char* what() const noexcept
	{
		return "Initialization of the Font object failed.";
	}
};

/// <summary>	A font. </summary>
class Font : public Resource
{
	friend class Text;

public:
	/// <summary>	Default constructor. </summary>
	Font();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="facePath">	Full pathname of the face file. </param>
	/// <param name="size">	   	The size. </param>
	/// <param name="atlas">   	[in,out] The atlas. </param>
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// <param name="spacing"> 	(Optional) The spacing. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Font(const std::string& facePath, std::uint8_t size, 
		std::shared_ptr<class ImageAtlas>& atlas, class Renderer& renderer, float spacing = 1.5f);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="facePath">	Full pathname of the face file. </param>
	/// <param name="size">	   	The size. </param>
	/// <param name="atlas">   	The atlas. </param>
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// <param name="spacing"> 	(Optional) The spacing. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(const std::string& facePath, std::uint8_t size, 
		std::shared_ptr<class ImageAtlas> atlas, class Renderer& renderer, float spacing = 1.5f);

	/// <summary>	Destructor. </summary>
	~Font();
	/// <summary>	Clears this object to its blank/initial state. </summary>
	void clear() override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the atlas. </summary>
	///
	/// <returns>	The atlas. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<const class ImageAtlas> getAtlas() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the size. </summary>
	///
	/// <returns>	The size. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getSize() const override;

private:
	/// <summary>	Information about the glyph. </summary>
	struct GlyphInfo
	{
		float ax, ay;
		float bw, bh;
		float bl, bt;
		uint32_t tx, ty;
	};

	/// <summary>	The ft library. </summary>
	FT_Library FTLib; 
	/// <summary>	The face. </summary>
	FT_Face mFace;
	/// <summary>	The atlas. </summary>
	std::shared_ptr<ImageAtlas> mAtlas;
	/// <summary>	The texture. </summary>
	std::shared_ptr<class Texture> mTexture;
	/// <summary>	True if this object is texture changed. </summary>
	bool mIsTextureChanged;

	/// <summary>	The size. </summary>
	std::uint8_t mSize;
	/// <summary>	Width of the tab. </summary>
	std::uint32_t mTabWidth;
	/// <summary>	The ascender. </summary>
	std::int32_t mAscender;
	/// <summary>	The descender. </summary>
	std::int32_t mDescender;
	/// <summary>	The height. </summary>
	std::uint16_t mHeight;
	/// <summary>	The spacing. </summary>
	float mSpacing;

	/// <summary>	The characters. </summary>
	std::unordered_map<std::uint32_t, GlyphInfo> mChars;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Cache character. </summary>
	///
	/// <param name="charCode">	The character code. </param>
	///
	/// <returns>	True if it succeeds, false if it fails. </returns>
	///--------------------------------------------------------------------------------------------
	bool cacheChar(std::uint32_t charCode);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Puts a character. </summary>
	///
	/// <param name="charCode">	The character code. </param>
	/// <param name="buffer">  	[in,out] The buffer. </param>
	/// <param name="penPos">  	[in,out] The pen position. </param>
	///--------------------------------------------------------------------------------------------
	void putChar(std::uint32_t charCode, std::vector<TextVertexLayout::Data>& buffer, 
		glm::vec2 &penPos);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets a texture. </summary>
	///
	/// <param name="renderer">	[in,out] The renderer. </param>
	///
	/// <returns>	The texture. </returns>
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<class Texture> getTexture(class Renderer& renderer);
};



