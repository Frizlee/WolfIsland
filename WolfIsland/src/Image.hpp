///-------------------------------------------------------------------------------------------------
// file:	src\Image.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include "Resource.hpp"


/// <summary>	An image. </summary>
class Image : public Resource
{
	friend class Texture;
	friend class ImageAtlas;

public:
	/// <summary>	Values that represent formats. </summary>
	enum class Format
	{
		UNKNOWN = 0,

		R8,
		RG8,
		RGB8,
		RGBA8,
		R3G3B2,
		R5G6B5,
		RGBA4,
		RGB5A1,
		RGB10A2,
		
		SRGB8,
		SRGB8A8,

		// Compressed formats.
		BC1_RGB,
		BC1_RGBA,
		BC2_RGBA,
		BC3_RGBA,
		BC4_R,
		BC4_SIGNED_R,
		BC5_RG,
		BC5_SIGNED_RG,

		// Aliases.
		R = R8,
		RG = RG8,
		RGB = RGB8,
		RGBA = RGBA8,
	};	
	
	/// <summary>	Default constructor. </summary>
	Image();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Copy/Move constructors and assignments. </summary>
	///
	/// <param name="lhs">	The left hand side. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Image(const Image &lhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Move constructor. </summary>
	///
	/// <param name="rhs">	[in,out] The right hand side. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Image(Image &&rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Assignment operator. </summary>
	///
	/// <param name="cas">	The cas. </param>
	///
	/// <returns>	A shallow copy of this object. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Image& operator=(Image cas);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Move assignment operator. </summary>
	///
	/// <param name="rhs">	[in,out] The right hand side. </param>
	///
	/// <returns>	A shallow copy of this object. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Image& operator=(Image &&rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Copy bytes. </summary>
	///
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>
	/// <param name="format">	Describes the format to use. </param>
	/// <param name="bytes"> 	The bytes. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Image(std::uint32_t width, std::uint32_t height, Format format, 
		const std::vector<std::uint8_t> &bytes);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>
	/// <param name="format">	Describes the format to use. </param>
	/// <param name="bytes"> 	The bytes. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::uint32_t width, std::uint32_t height, Format format,
		const std::vector<std::uint8_t> &bytes);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Move bytes. </summary>
	///
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>
	/// <param name="format">	Describes the format to use. </param>
	/// <param name="bytes"> 	[in,out] The bytes. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Image(std::uint32_t width, std::uint32_t height, Format format, 
		std::vector<std::uint8_t> &&bytes);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>
	/// <param name="format">	Describes the format to use. </param>
	/// <param name="bytes"> 	[in,out] The bytes. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::uint32_t width, std::uint32_t height, Format format,
		std::vector<std::uint8_t> &&bytes);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Without bytes. </summary>
	///
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>
	/// <param name="format">	Describes the format to use. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Image(std::uint32_t width, std::uint32_t height, Format format);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>
	/// <param name="format">	Describes the format to use. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::uint32_t width, std::uint32_t height, Format format);
	
	/// <summary>	Destructor. </summary>
	virtual ~Image();
	/// <summary>	Clears this object to its blank/initial state. </summary>
	void clear() override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the format. </summary>
	///
	/// <returns>	The format. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Format getFormat() const;

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
	/// <summary>	Query if this object is compressed. </summary>
	///
	/// <returns>	True if compressed, false if not. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool isCompressed() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Return block size if compressed. </summary>
	///
	/// <returns>	The bytes per pixel. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint8_t getBytesPerPixel() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Calculates the bytes per pixel. </summary>
	///
	/// <param name="format">	Describes the format to use. </param>
	///
	/// <returns>	The calculated bytes per pixel. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	static std::uint8_t CalculateBytesPerPixel(Format format);

	///--------------------------------------------------------------------------------------------
	/// <summary>	x and y must be in range [0, mWidth] and [0, mHeight]. </summary>
	///
	/// <param name="x">		The std::uint32_t to process. </param>
	/// <param name="y">		The std::uint32_t to process. </param>
	/// <param name="bytes">	The bytes. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setPixel(std::uint32_t x, std::uint32_t y, const std::vector<std::uint8_t> &bytes);
	/// <summary>	Flip verticaly. </summary>
	void flipVerticaly();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the size. </summary>
	///
	/// <returns>	The size. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getSize() const override;

protected:
	/// <summary>	The bytes. </summary>
	std::vector<std::uint8_t> mBytes;

private:
	/// <summary>	The width. </summary>
	std::uint32_t mWidth;
	/// <summary>	The height. </summary>
	std::uint32_t mHeight;
	/// <summary>	Describes the format to use. </summary>
	Format mFormat;
};

