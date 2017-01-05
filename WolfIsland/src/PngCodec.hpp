///-------------------------------------------------------------------------------------------------
// file:	src\PngCodec.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Codec.hpp"
#include <png.h>

/// <summary>	A PNG codec. </summary>
class PngCodec : public Codec
{
public:
	/// <summary>	Default constructor. </summary>
	PngCodec();
	/// <summary>	Destructor. </summary>
	~PngCodec();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Decodes. </summary>
	///
	/// <param name="input">	[in,out] The input. </param>
	/// <param name="res">  	[in,out] The resource. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void decode(std::istream &input, Resource &res);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Encodes. </summary>
	///
	/// <param name="output">	[in,out] The output. </param>
	/// <param name="res">   	[in,out] The resource. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void encode(std::ostream &output, Resource &res);
	
private:

	///--------------------------------------------------------------------------------------------
	/// <summary>	Callback, called when the PNG read. </summary>
	///
	/// <param name="pngPtr">		  	The PNG pointer. </param>
	/// <param name="outBytes">		  	The out in bytes. </param>
	/// <param name="byteCountToRead">	The byte count to read. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	static void PngReadCallback(png_structp pngPtr, png_bytep outBytes, png_size_t byteCountToRead);
};



