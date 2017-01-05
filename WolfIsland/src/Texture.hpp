///-------------------------------------------------------------------------------------------------
// file:	src\Texture.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include "Image.hpp"
#include "GpuResource.hpp"

/// <summary>	A texture. </summary>
class Texture : public GpuResource
{
public:
	/// <summary>	Values that represent types. </summary>
	enum class Type
	{
		UNCOMPRESSED_2D,
		COMPRESSED_2D,
		UNCOMPRESSED_2D_ARRAY,
		COMPRESSED_2D_ARRAY
	};

	/// <summary>	Default constructor. </summary>
	Texture();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Copy/Move constructors and assignments. </summary>
	///
	/// <param name="lhs">	The left hand side. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Texture(const Texture& lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Move constructor. </summary>
	///
	/// <param name="rhs">	[in,out] The right hand side. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Texture(Texture&& rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Assignment operator. </summary>
	///
	/// <param name="lhs">	The left hand side. </param>
	///
	/// <returns>	A shallow copy of this object. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Texture& operator=(const Texture& lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Move assignment operator. </summary>
	///
	/// <param name="rhs">	[in,out] The right hand side. </param>
	///
	/// <returns>	A shallow copy of this object. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Texture& operator=(Texture&& rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Create texture. </summary>
	///
	/// <param name="img">	   	The image. </param>
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Texture(const Image& img, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="img">	   	The image. </param>
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(const Image& img, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Create texture array This functions needs to be reimlemented differently. </summary>
	///
	/// <param name="imgs">	   	[in,out] The imgs. </param>
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Texture(std::vector<Image>& imgs, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="imgs">	   	[in,out] The imgs. </param>
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::vector<Image>& imgs, Renderer& renderer);
	
	/// <summary>	Destructor. </summary>
	~Texture();
	/// <summary>	Clears this object to its blank/initial state. </summary>
	void clear() override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Generates the mipmaps. </summary>
	///
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void generateMipmaps(class Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the format. </summary>
	///
	/// <returns>	The format. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Image::Format getFormat() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Query if this object has mipmap. </summary>
	///
	/// <returns>	True if mipmap, false if not. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool hasMipmap() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the type. </summary>
	///
	/// <returns>	The type. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Type getType() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the size. </summary>
	///
	/// <returns>	The size. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getSize() const override;

private:
	/// <summary>	Describes the format to use. </summary>
	Image::Format mFormat;
	/// <summary>	The type. </summary>
	Type mType;
	/// <summary>	The size. </summary>
	std::uint32_t mSize;
	/// <summary>	True if this object has mipmap. </summary>
	bool mHasMipmap;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Parse format. </summary>
	///
	/// <param name="imgFormat">			   	The image format. </param>
	/// <param name="format">				   	[in,out] Describes the format to use. </param>
	/// <param name="internalFormat">		   	[in,out] The internal format. </param>
	/// <param name="dataType">				   	[in,out] Type of the data. </param>
	/// <param name="compressedInternalFormat">	[in,out] The compressed internal format. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	static void ParseFormat(Image::Format imgFormat, GLint &format, 
		GLint &internalFormat, GLenum &dataType, GLenum &compressedInternalFormat);
};

