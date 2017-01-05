///-------------------------------------------------------------------------------------------------
// file:	src\VertexLayout.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include "gl_core_3_3.hpp"

/// <summary>	A vertex format. </summary>
struct VertexFormat
{
	/// <summary>	True to empty. </summary>
	bool empty;
	/// <summary>	The size. </summary>
	GLint size;
	/// <summary>	The type. </summary>
	GLenum type;
	/// <summary>	The normalized. </summary>
	GLboolean normalized;
	/// <summary>	The stride. </summary>
	GLsizei stride;
	/// <summary>	The pointer. </summary>
	std::uint32_t pointer;

	/// <summary>	Default constructor. </summary>
	VertexFormat();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="size">		 	The size. </param>
	/// <param name="type">		 	The type. </param>
	/// <param name="normalized">	The normalized. </param>
	/// <param name="stride">	 	The stride. </param>
	/// <param name="pointer">   	The pointer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexFormat(GLint size, GLenum type, GLboolean normalized, GLsizei stride, 
		std::uint32_t pointer);
};

/// <summary>	A vertex layout. </summary>
class VertexLayout
{
public:
	/// <summary>	Default constructor. </summary>
	VertexLayout();
	/// <summary>	Destructor. </summary>
	virtual ~VertexLayout() = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the formats. </summary>
	///
	/// <returns>	The formats. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const std::vector<VertexFormat>& getFormats();

protected:
	/// <summary>	The formats. </summary>
	std::vector<VertexFormat> mFormats;
};

/// <summary>	A text vertex layout. </summary>
class TextVertexLayout : public VertexLayout
{
public:
	/// <summary>	A data. </summary>
	struct Data
	{
		float x, y;
		float u, v;

		/// <summary>	Default constructor. </summary>
		Data();

		///----------------------------------------------------------------------------------------
		/// <summary>	Constructor. </summary>
		///
		/// <param name="x">	The x coordinate. </param>
		/// <param name="y">	The y coordinate. </param>
		/// <param name="u">	The float to process. </param>
		/// <param name="v">	The float to process. </param>
		/// 
		///----------------------------------------------------------------------------------------
		Data(float x, float y, float u, float v);
	};
	
	/// <summary>	Default constructor. </summary>
	TextVertexLayout();
	/// <summary>	Destructor. </summary>
	~TextVertexLayout();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the size. </summary>
	///
	/// <returns>	A std::uint32_t. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	static std::uint32_t Size();
};

/// <summary>	A texture vertex layout. </summary>
class TextureVertexLayout : public VertexLayout
{
public:
	/// <summary>	A data. </summary>
	struct Data
	{
		float x, y, z;
		float u, v;

		/// <summary>	Default constructor. </summary>
		Data();

		///----------------------------------------------------------------------------------------
		/// <summary>	Constructor. </summary>
		///
		/// <param name="x">	The x coordinate. </param>
		/// <param name="y">	The y coordinate. </param>
		/// <param name="z">	The z coordinate. </param>
		/// <param name="u">	The float to process. </param>
		/// <param name="v">	The float to process. </param>
		/// 
		///----------------------------------------------------------------------------------------
		Data(float x, float y, float z, float u, float v);
	};

	/// <summary>	Default constructor. </summary>
	TextureVertexLayout();
	/// <summary>	Destructor. </summary>
	~TextureVertexLayout();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the size. </summary>
	///
	/// <returns>	A std::uint32_t. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	static std::uint32_t Size();
};

/// <summary>	A color vertex layout. </summary>
class ColorVertexLayout : public VertexLayout
{
public:
	/// <summary>	A data. </summary>
	struct Data
	{
		float x, y, z;
		std::uint32_t color;

		/// <summary>	Default constructor. </summary>
		Data();

		///----------------------------------------------------------------------------------------
		/// <summary>	Constructor. </summary>
		///
		/// <param name="x">		The x coordinate. </param>
		/// <param name="y">		The y coordinate. </param>
		/// <param name="z">		The z coordinate. </param>
		/// <param name="color">	The color. </param>
		/// 
		///----------------------------------------------------------------------------------------
		Data(float x, float y, float z, std::uint32_t color);
	};

	/// <summary>	Default constructor. </summary>
	ColorVertexLayout();
	/// <summary>	Destructor. </summary>
	~ColorVertexLayout();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the size. </summary>
	///
	/// <returns>	A std::uint32_t. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	static std::uint32_t Size();
};

/// <summary>	A position vertex layout. </summary>
class PositionVertexLayout : public VertexLayout
{
public:
	/// <summary>	A data. </summary>
	struct Data
	{
		float x, y, z;

		/// <summary>	Default constructor. </summary>
		Data();

		///----------------------------------------------------------------------------------------
		/// <summary>	Constructor. </summary>
		///
		/// <param name="x">	The x coordinate. </param>
		/// <param name="y">	The y coordinate. </param>
		/// <param name="z">	The z coordinate. </param>
		/// 
		///----------------------------------------------------------------------------------------
		Data(float x, float y, float z);
	};

	/// <summary>	Default constructor. </summary>
	PositionVertexLayout();
	/// <summary>	Destructor. </summary>
	~PositionVertexLayout();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the size. </summary>
	///
	/// <returns>	A std::uint32_t. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	static std::uint32_t Size();
};

